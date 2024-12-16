#include "model.h"

#include <QString>
#include <QVector>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QProcess>
#include <QMap>
#include <QList>
#include <QFile>
#include <QDir>
#include "dirpaths.h"

Model::Model() {}

bool Model::checkModel(const QString &filePath, QSqlDatabase &db, MainWindow *mainWindow) {
    Utilities utilities;
    QFile inputFile(filePath);
    QFileInfo fileInfo(inputFile);
    QString subFilename = fileInfo.baseName() + ".sub";
    QList<QString> modelsList;

    if (!db.isOpen()) {
        Utilities::logMessage("Database is not open!", mainWindow);
        return false;
    }

    QSqlQuery query(db);
    if (!query.exec("SELECT Name FROM models")) {
        Utilities::logMessage("First query failed:" + query.lastError().text(), mainWindow);
        return false;
    }

    while (query.next()) {
        QString name = query.value(0).toString();
        modelsList.append(name);
    }

    if (!modelsList.contains(subFilename)) {
        Utilities::logMessage("Model name: " + subFilename + " needs to be added.\n", mainWindow);
        return false;;
    }

    return true;
}

bool Model::insertOrUpdate(ModelStruct& newDevice, QSqlDatabase& db, MainWindow* mainWindow) {
    Utilities utilities;
    if (!db.isOpen()) {
        Utilities::logMessage("Database is not open!", mainWindow);
        return false;
    }

    QList<QString> modelList;
    if (!fetchModelList(db, modelList, mainWindow)) {
        return false;
    }

    DirStruct dir = DirPaths().buildDirPaths(mainWindow);
    QString subFilePath = dir.subDirPath + newDevice.name;
    QFile subFile(subFilePath);

    if (!subFile.exists()) {
        Utilities::logMessage("Model file: " + subFilePath + " not found!", mainWindow);
        return false;
    }

    if (!subFile.open(QIODevice::ReadOnly)) {
        Utilities::logMessage("Could not open file for reading:" + subFile.errorString(), mainWindow);
        return false;
    }

    QByteArray binaryData = subFile.readAll();
    subFile.close();

    if (modelList.contains(newDevice.name)) {
        return updateModel(newDevice, binaryData, db, mainWindow);
    } else {
        return insertModel(newDevice, binaryData, db, mainWindow);
    }
}

bool Model::processModel(const QString& modFilePath, QSqlDatabase& db, MainWindow* mainWindow) {
    ModelStruct device;
    Utilities utilities;
    QFile modFile(modFilePath);

    if (!modFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        Utilities::logMessage("Error opening file: " + modFilePath, mainWindow);
        return false;
    }

    DirStruct dir = DirPaths().buildDirPaths(mainWindow);
    QFileInfo ascFileInfo(modFile);
    QString subFilename = ascFileInfo.baseName() + ".sub";
    QString generatedNetlistPath = ascFileInfo.absolutePath() + "/" + ascFileInfo.completeBaseName() + ".sub";

    if (QFile::exists(generatedNetlistPath)) {
        QFile::remove(generatedNetlistPath);
    }

    if (ascFileInfo.suffix() == "asc") {
        Utilities::generateNetlistFile(modFilePath, mainWindow);
    } else {
        if (!QFile::copy(modFilePath, generatedNetlistPath)) {
            Utilities::logMessage("Failed to copy file:" + modFilePath, mainWindow);
            return false;
        }
    }

    Utilities::encryptFile(generatedNetlistPath, mainWindow);
    Utilities::backupFile(dir.subDirPath + subFilename, mainWindow);
    Utilities::updateFile(generatedNetlistPath, dir.subDirPath + subFilename, mainWindow);
    Utilities::backupFile(dir.ecsDirPath + ascFileInfo.fileName(), mainWindow);
    Utilities::updateFile(modFilePath, dir.ecsDirPath + ascFileInfo.fileName(), mainWindow);

    device.encrypt = "encrypted";
    device.date = dir.dateString;
    device.name = subFilename;
    device.relPath = "/lib/sub/" + subFilename;

    return insertOrUpdate(device, db, mainWindow);
}

bool Model::updateSourceModel(const QString& filePath, MainWindow* mainWindow) {
    Utilities utilities;
    QFile ascFile(filePath);

    if (!ascFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        Utilities::logMessage("Error opening file: " + filePath, mainWindow);
        return false;
    }

    DirStruct dir = DirPaths().buildDirPaths(mainWindow);
    QFileInfo ascFileInfo(ascFile);
    QString subFilename = ascFileInfo.baseName() + ".sub";
    QString netlistFilePath = ascFileInfo.absolutePath() + "/" + subFilename;

    Utilities::updateFile(netlistFilePath, dir.sourceLibSubPath + "/" + subFilename, mainWindow);
    Utilities::updateFile(filePath, dir.sourceLibECSPath + "/" + ascFileInfo.fileName(), mainWindow);

    return true;
}

bool Model::fetchModelList(QSqlDatabase& db, QList<QString>& modelList, MainWindow* mainWindow) {
    Utilities utilities;
    QSqlQuery query(db);
    if (!query.exec("SELECT Name FROM models")) {
        Utilities::logMessage("Query failed:" + query.lastError().text(), mainWindow);
        return false;
    }

    while (query.next()) {
        modelList.append(query.value(0).toString());
    }

    return true;
}

bool Model::updateModel(ModelStruct& newDevice, const QByteArray& binaryData, QSqlDatabase& db, MainWindow* mainWindow) {
    QSqlQuery query(db);
    Utilities utilities;
    query.prepare("UPDATE models SET Encrypted = :encryption, Date = :date, RelPath = :relPath, BinFile = :binFile WHERE Name = :name");
    query.bindValue(":encryption", newDevice.encrypt);
    query.bindValue(":date", newDevice.date);
    query.bindValue(":relPath", newDevice.relPath);
    query.bindValue(":binFile", binaryData);
    query.bindValue(":name", newDevice.name);

    if (!query.exec()) {
        Utilities::logMessage("Error running update query:" + query.lastError().text(), mainWindow);
        return false;
    }

    return true;
}

bool Model::insertModel(ModelStruct& newDevice, const QByteArray& binaryData, QSqlDatabase& db, MainWindow* mainWindow) {
    QSqlQuery query(db);
    Utilities utilities;
    query.prepare("INSERT INTO models (Name, Encrypted, Date, RelPath, BinFile) VALUES (:name, :encryption, :date, :relPath, :binFile)");
    query.bindValue(":name", newDevice.name);
    query.bindValue(":encryption", newDevice.encrypt);
    query.bindValue(":date", newDevice.date);
    query.bindValue(":relPath", newDevice.relPath);
    query.bindValue(":binFile", binaryData);

    if (!query.exec()) {
        Utilities::logMessage("Error running insert query:" + query.lastError().text(), mainWindow);
        return false;
    }

    return true;
}

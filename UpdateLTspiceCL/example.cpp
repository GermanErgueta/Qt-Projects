// example.cpp

#include "example.h"
#include "dirpaths.h"
#include "utilities.h" // Assuming Utilities is defined in this header

#include <QString>
#include <QVector>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMap>
#include <QList>
#include <QFile>
#include <QDir>
#include <QFileInfo>

Example::Example() {}

bool Example::checkExample(const QString &filePath, QSqlDatabase &db, MainWindow *mainWindow) {
    Utilities utilities;
    ExampleStruct example;
    QFile inputFile(filePath);
    QFileInfo fileInfo(inputFile);
    QString ascFilename = fileInfo.fileName();
    QList<QString> examplesList;
    QString exampleFilename = ascFilename.replace("eg", "");
    QSqlQuery query(db);

    if (!query.exec("SELECT Name FROM examples")) {
        Utilities::logMessage("First query failed:" + query.lastError().text(), mainWindow);
        return false;
    }

    while (query.next()) {
        QString name = query.value(0).toString();
        examplesList.append(name);
    }

    if (!examplesList.contains(exampleFilename)) {
        Utilities::logMessage("Example name: " +  exampleFilename  + " needs to be added.", mainWindow);
        return false;
    }

    return true;
}

bool Example::insertOrUpdate(ExampleStruct& newDevice, QSqlDatabase& db, MainWindow* mainWindow) {
    QList<QString> examplesList;
    Utilities utilities;
    QSqlQuery query(db);
    DirPaths dirPaths;
    DirStruct dir = dirPaths.buildDirPaths(mainWindow);

    QString exFilePath = dir.applicationsDirPath + "/" + newDevice.name;
    QFile exFile(exFilePath);

    if (!exFile.exists()) {
        Utilities::logMessage("Model file: " + exFilePath + " not found!", mainWindow);
        return false;
    }

    if (!db.isOpen()) {
        Utilities::logMessage("Database is not open!", mainWindow);
        return false;
    }

    if (!exFile.open(QIODevice::ReadOnly)) {
        Utilities::logMessage("Could not open file for reading:" + exFile.errorString(), mainWindow);
        return false;
    }

    QByteArray binaryData = exFile.readAll();
    qDebug() << "Binary data size: " << binaryData.size();
    exFile.close();

    if (!query.exec("SELECT Name FROM examples")) {
        Utilities::logMessage("First query failed:" + query.lastError().text(), mainWindow);
        return false;
    }

    while (query.next()) {
        QString name = query.value(0).toString();
        examplesList.append(name);
    }

    if (examplesList.contains(newDevice.name)) {
        return updateExampleInDB(newDevice, binaryData, db, mainWindow);
    } else {
        return insertExampleInDB(newDevice, binaryData, db, mainWindow);
    }
}

bool Example::updateExampleInDB(ExampleStruct& newDevice, const QByteArray& binaryData, QSqlDatabase& db, MainWindow* mainWindow) {
    QSqlQuery query(db);
    Utilities utilities;
    query.prepare("UPDATE examples SET Date = :date, RelPath = :relPath, BinFile = :binFile WHERE Name = :name");
    query.bindValue(":date", newDevice.date);
    query.bindValue(":relPath", newDevice.relPath);
    query.bindValue(":binFile", binaryData);
    query.bindValue(":name", newDevice.name);

    if (!query.exec()) {
        Utilities::logMessage("Error running update query:" +  query.lastError().text(), mainWindow);
        return false;
    }

    return true;
}

bool Example::insertExampleInDB(ExampleStruct& newDevice, const QByteArray& binaryData, QSqlDatabase& db, MainWindow* mainWindow) {
    QSqlQuery query(db);
    Utilities utilities;
    query.prepare("INSERT INTO examples (Name, Date, RelPath, BinFile) VALUES (:name, :date, :relPath, :binFile)");
    query.bindValue(":name", newDevice.name);
    query.bindValue(":date", newDevice.date);
    query.bindValue(":relPath", newDevice.relPath);
    query.bindValue(":binFile", binaryData);

    if (!query.exec()) {
        Utilities::logMessage("Error running insert query:" + query.lastError().text(), mainWindow);
        return false;
    }

    return true;
}

bool Example::processExample(const QString& filePath, QSqlDatabase& db, MainWindow* mainWindow) {
    Example example;
    Utilities utilities;
    ExampleStruct device;

    DirPaths dirPaths;
    DirStruct dir = dirPaths.buildDirPaths(mainWindow);

    QFile exFile(filePath);
    if (!exFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        Utilities::logMessage("Error opening file: " +  filePath, mainWindow) ;
        return false;
    }

    QFileInfo exFileInfo(exFile);
    QString exFilename = exFileInfo.fileName().remove(0, 2);
    QString exFilenamePath = dir.applicationsDirPath + exFilename;

    Utilities::exBackupFile(exFilenamePath, mainWindow);
    Utilities::updateFile(filePath, exFilenamePath, mainWindow);

    device.date = dir.dateString;
    device.name = exFilename;
    device.relPath = "/examples/Applications/" + exFilename;

    return example.insertOrUpdate(device, db, mainWindow);
}

bool Example::updateSourceExample(const QString& filePath, MainWindow* mainWindow) {
    Utilities utilities;
    QFile exFile(filePath);
    if (!exFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        Utilities::logMessage("Error opening file: " +  filePath, mainWindow) ;
        return false;
    }

    DirPaths dirPaths;
    DirStruct dir = dirPaths.buildDirPaths(mainWindow);

    QFileInfo exFileInfo(exFile);
    QString exFilename = exFileInfo.fileName().remove(0, 2);
    QString remoteExFilenamePath = dir.sourceApplicationsPath + "/" + exFilename;

    Utilities::updateFile(filePath, remoteExFilenamePath, mainWindow);

    return true;
}

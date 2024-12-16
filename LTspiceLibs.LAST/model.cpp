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

Model::Model() {}

ModelStruct Model::checkModel(const QString &filePath, QSqlDatabase &db){
    ModelStruct model;
    QFile inputFile(filePath);
    QFileInfo fileInfo(inputFile);
    QString ascFilename = fileInfo.fileName();
    QString subFilename = fileInfo.baseName() + ".sub";
    QList<QString> modelsList;
    QString oldModelname;
    QSqlQuery query;
    if (!query.exec("SELECT Name FROM models")) {
        qWarning() << "First query failed:" << query.lastError().text();
    } else {
        while (query.next()) {
            QString name = query.value(0).toString();  // First column: name
            modelsList.append(name);                   // Insert value into the QList
        }
    }
    if(!modelsList.contains(subFilename)){
        qWarning() << "Model name: " << subFilename << " needs to be added.\n";
    }
    return model;
}

bool Model::insertOrUpdate(ModelStruct& newDevice, QSqlDatabase& db, MainWindow* mainWindow) {
    QList<QString> modelList;
    QSqlQuery query;
    QString LTspiceDevelopmentDirPath = mainWindow->getUi()->lineEditLTspiceDevelopment->text();
    QString modelsDirPath = LTspiceDevelopmentDirPath + "/" + "Models";
    QString libDirPath = modelsDirPath + "/" + "lib";
    QString subLibPath = libDirPath + "/" + "sub";
    QString subFilePath = subLibPath + "/" + newDevice.name;
    QFile subFile = QFile(subFilePath);
    if (!subFile.exists()) {
        qWarning() << "Model file: " << subFilePath << " not found!";
        return false;
    }
    if (!db.isOpen()) {
        qWarning() << "Database is not open!";
        return false;
    }
    if (!subFile.open(QIODevice::ReadOnly)) {
        qWarning() << "Could not open file for reading:" << subFile.errorString();
        return false;
    }

    QByteArray binaryData = subFile.readAll();
    qDebug() << "Binary data size: " << binaryData.size();
    subFile.close();

    if (!query.exec("SELECT Name FROM models")) {
        qWarning() << "First query failed:" << query.lastError().text();
    }
    else {
        while (query.next()) {
            QString name = query.value(0).toString();  // First column: name
            modelList.append(name);                   // Insert value into the QList
        }
    }
    if (modelList.contains(newDevice.name)) {
        if (db.isOpen()) {
            QSqlQuery query(db);
            query.prepare("UPDATE models "
                          "SET Encrypted = :encryption, "
                          "Date = :date, "
                          "RelPath = :relPath, "
                          "BinFile = :binFile "
                          "WHERE Name = :name");

            // Bind values to parameters
            query.bindValue(":encryption", newDevice.encrypt);
            query.bindValue(":date", newDevice.date);
            query.bindValue(":relPath", newDevice.relPath);
            query.bindValue(":binFile", binaryData);  // Bind the binary data
            query.bindValue(":name", newDevice.name);

            if (!query.exec()) {
                qWarning() << "Error running query:" << query.lastError();
            }
        }
    }
    else {
        // Device not found, insert a new record
        QSqlQuery insertQuery(db);
        insertQuery.prepare("INSERT INTO models (Name, Encrypted, Date, RelPath, BinFile) "
                            "VALUES (:name, :encryption, :date, :relPath, :binFile)");

        // Bind the insert values
        insertQuery.bindValue(":name", newDevice.name);
        insertQuery.bindValue(":encryption", newDevice.encrypt);
        insertQuery.bindValue(":date", newDevice.date);
        insertQuery.bindValue(":relPath", newDevice.relPath);
        insertQuery.bindValue(":binFile", binaryData);

        if (!insertQuery.exec()) {
            qWarning() << "Error running insert query:" << insertQuery.lastError();
            return false;
        }
    }
    return true;
}

ModelStruct Model::processModel(const QString& filePath, QSqlDatabase& db, MainWindow* mainWindow) {
    Model model;
    Utilities utilities;
    ModelStruct device;

    QFile ascFile = QFile(filePath);
    if (!ascFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Error opening file: " << filePath;
        return device;
    }
    QString LTspiceDevelopmentDirPath = mainWindow->getUi()->lineEditLTspiceDevelopment->text();
    QString remoteSourceDirPath = mainWindow->getUi()->comboBoxSharePoint->currentText() + "/" + "Source";
    QString remoteSourceLibDirPath = remoteSourceDirPath + "/" + "lib";
    QString remoteSourceSubDirPath = remoteSourceLibDirPath + "/" + "sub";
    QString remoteSourceECSDirPath = remoteSourceLibDirPath + "/" + "ECS";
    QString modelsDirPath = LTspiceDevelopmentDirPath + "/" + "Models";
    QString localEcsDirPath = modelsDirPath + "/" + "ECS";
    QString ltspiceExePath = modelsDirPath + "/" + "LTspice.exe";
    QString encryptExePath = modelsDirPath + "/" + "encrypt.exe";
    QString newModelsDirPath = modelsDirPath + "/" + "NewModels";
    QString srcDate = mainWindow->getUi()->dateProcessing->date().toString("yyyy-MM-dd");
    QString yearModelPath = newModelsDirPath + "/" + mainWindow->getUi()->dateProcessing->date().toString("yyyy");
    QString bakDirPath = modelsDirPath + "/" + "BAK" + "/" + srcDate.left(4);
    QString libDirPath = modelsDirPath + "/" + "lib";
    QString subLibPath = libDirPath + "/" + "sub";
    QFileInfo ascFileInfo = QFileInfo(ascFile);
    QString localAscInECSDirPath = localEcsDirPath + "/" + ascFileInfo.fileName();
    QString ascFilename = ascFileInfo.fileName();
    QString subFilename = ascFileInfo.baseName() + ".sub";
    QString localSubFilenamePath = subLibPath + "/" + subFilename;
    QString remoteSubFilenamePath = remoteSourceSubDirPath + "/" + subFilename;
    QString remoteAscSourceECSFilePath = remoteSourceECSDirPath + "/" + ascFilename;
    // Generate netlist file
    utilities.generateNetlistFile(filePath, mainWindow);
    // Encrypt netlist file
    QString netlistFilePath = ascFileInfo.absolutePath() + "/" + ascFileInfo.baseName() + ".sub";
    utilities.encryptFile(netlistFilePath, mainWindow);
    // Backup existing encrypted file
    utilities.backupFile(localSubFilenamePath, mainWindow);
    // Copy new encrypted file to local directory
    utilities.updateFile(netlistFilePath, localSubFilenamePath);
    utilities.updateFile(netlistFilePath, remoteSubFilenamePath);
    // Copy files ECS and source directories
    utilities.backupFile(localAscInECSDirPath, mainWindow);
    utilities.updateFile(filePath, localAscInECSDirPath);
    utilities.updateFile(filePath, remoteAscSourceECSFilePath);
    device.encrypt = "encrypted";
    device.date = srcDate;
    device.name = subFilename;
    device.relPath = "/lib/sub/" + subFilename;
    model.insertOrUpdate(device, db, mainWindow);
    return device;
}

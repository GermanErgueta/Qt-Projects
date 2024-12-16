#include "example.h"

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
#include "dirpaths.h"

Example::Example() {}


bool Example::checkExample(const QString &filePath, QSqlDatabase &db){
    ExampleStruct example;
    QFile inputFile(filePath);
    QFileInfo fileInfo(inputFile);
    QString ascFilename = fileInfo.fileName();
    QList<QString> examplesList;
    QString exampleFilename = ascFilename.replace("eg","");
    QSqlQuery query(db);
    if (!query.exec("SELECT Name FROM examples")) {
        qWarning() << "First query failed:" << query.lastError().text();
    } else {
        while (query.next()) {
            QString name = query.value(0).toString();  // First column: name
            examplesList.append(name);                   // Insert value into the QList
        }
    }
    if(!examplesList.contains(exampleFilename)){
        qWarning() << "Example name: " << exampleFilename << " needs to be added.\n";
    }
    return true;
}

bool Example::insertOrUpdate(ExampleStruct& newDevice, QSqlDatabase& db, MainWindow* mainWindow) {
    QList<QString> examplesList;
    QSqlQuery query(db);
    DirStruct dir;
    DirPaths dirPaths;
    dir = dirPaths.buildDirPaths(mainWindow);

    QString exFilePath = dir.applicationsDirPath + "/" + newDevice.name;
    QFile exFile = QFile(exFilePath);
    if (!exFile.exists()) {
        qWarning() << "Model file: " << exFilePath << " not found!";
        return false;
    }
    if (!db.isOpen()) {
        qWarning() << "Database is not open!";
        return false;
    }
    if (!exFile.open(QIODevice::ReadOnly)) {
        qWarning() << "Could not open file for reading:" << exFile.errorString();
        return false;
    }

    QByteArray binaryData = exFile.readAll();
    qDebug() << "Binary data size: " << binaryData.size();
    exFile.close();

    if (!query.exec("SELECT Name FROM examples")) {
        qWarning() << "First query failed:" << query.lastError().text();
    }
    else {
        while (query.next()) {
            QString name = query.value(0).toString();  // First column: name
            examplesList.append(name);                   // Insert value into the QList
        }
    }
    if (examplesList.contains(newDevice.name)) {
        if (db.isOpen()) {
            QSqlQuery query(db);
            query.prepare("UPDATE examples "
                          "SET Date = :date, "
                          "RelPath = :relPath, "
                          "BinFile = :binFile "
                          "WHERE Name = :name");

            // Bind values to parameters
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
        insertQuery.prepare("INSERT INTO examples (Name, Date, RelPath, BinFile) "
                            "VALUES (:name, :date, :relPath, :binFile)");

        // Bind the insert values
        insertQuery.bindValue(":name", newDevice.name);
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


bool Example::processExample(const QString& filePath, QSqlDatabase& db, MainWindow* mainWindow) {
    Example example;
    Utilities utilities;
    ExampleStruct device;

    DirStruct dir;
    DirPaths dirPaths;
    dir = dirPaths.buildDirPaths(mainWindow);

    QFile exFile = QFile(filePath);
    if (!exFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Error opening file: " << filePath;
        return false;
    }
    QFileInfo exFileInfo = QFileInfo(exFile);
    QString exFilename = exFileInfo.fileName().remove(0,2);
    QString exFilenamePath = dir.applicationsDirPath + exFilename;
    // Backup existing example file
    utilities.exBackupFile(exFilenamePath, mainWindow);
    utilities.updateFile(filePath, exFilenamePath);
    // Copy files to remote server
    device.date = dir.dateString;
    device.name = exFilename;
    device.relPath = "/examples/Applications/" + exFilename;
    example.insertOrUpdate(device, db, mainWindow);
    return true;
}


bool Example::updateSourceExample(const QString& filePath, MainWindow* mainWindow) {
    Utilities utilities;
    QFile exFile = QFile(filePath);
    if (!exFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Error opening file: " << filePath;
        return false;
    }
    DirStruct dir;
    DirPaths dirPaths;
    dir = dirPaths.buildDirPaths(mainWindow);

    QFileInfo exFileInfo = QFileInfo(exFile);
    QString exFilename = exFileInfo.fileName().remove(0,2);
    QString remoteExFilenamePath = dir.sourceApplicationsPath + "/" + exFilename;
    utilities.updateFile(filePath, remoteExFilenamePath);

    return true;
}


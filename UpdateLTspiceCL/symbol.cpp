#include "symbol.h"
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
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QFileInfo>
#include <QRegularExpression>
#include "utilities.h"
#include "dirpaths.h"

Symbol::Symbol() {}

SymbolStruct Symbol::extractParametersFromAsyFile(const QString& filePath, MainWindow *mainWindow) {
    Utilities utilities;
    SymbolStruct newDevice;
    QFile inputFile(filePath);
    if (!inputFile.open(QIODevice::ReadOnly)) {
        Utilities::logMessage("Failed to open file:" + filePath, mainWindow);
        return newDevice;
    }
    QTextStream in(&inputFile);
    in.setEncoding(QStringConverter::Encoding::Latin1);
    QString content = in.readAll();
    inputFile.close();
    newDevice.symbolType = extractAttribute(content, "SymbolType");

    if (newDevice.symbolType.isEmpty()) {
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly)) {  // Open the file
            qDebug() << "Failed to open file:" << file.errorString();
        }
        QTextStream in(&file);
        in.setEncoding(QStringConverter::Encoding::Utf8);
        content = in.readAll();
        newDevice.symbolType = extractAttribute(content, "SymbolType");
        file.close();
    }

    if (newDevice.symbolType.isEmpty()) {
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly)) {  // Open the file
            qDebug() << "Failed to open file:" << file.errorString();
        }
        QTextStream in(&file);
        in.setEncoding(QStringConverter::Encoding::Utf16);
        content = in.readAll();
        newDevice.symbolType = extractAttribute(content, "SymbolType");
        file.close();
    }

    if (newDevice.symbolType.isEmpty()) {
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly)) {  // Open the file
            qDebug() << "Failed to open file:" << file.errorString();
        }
        QTextStream in(&file);
        in.setEncoding(QStringConverter::Encoding::System);
        content = in.readAll();
        newDevice.symbolType = extractAttribute(content, "SymbolType");
        file.close();
    }

    if (newDevice.symbolType.isEmpty()) {
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly)) {  // Open the file
            qDebug() << "Failed to open file:" << file.errorString();
        }
        QTextStream in(&file);
        in.setEncoding(QStringConverter::Encoding::Utf16BE);
        content = in.readAll();
        newDevice.symbolType = extractAttribute(content, "SymbolType");
        file.close();
    }

    if (newDevice.symbolType.isEmpty()) {
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly)) {  // Open the file
            qDebug() << "Failed to open file:" << file.errorString();
        }
        QTextStream in(&file);
        in.setEncoding(QStringConverter::Encoding::Utf16LE);
        content = in.readAll();
        newDevice.symbolType = extractAttribute(content, "SymbolType");
        file.close();
    }

    if (newDevice.symbolType.isEmpty()) {
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly)) {  // Open the file
            qDebug() << "Failed to open file:" << file.errorString();
        }
        QTextStream in(&file);
        in.setEncoding(QStringConverter::Encoding::Utf32);
        content = in.readAll();
        newDevice.symbolType = extractAttribute(content, "SymbolType");
        file.close();
    }

    if (newDevice.symbolType.isEmpty()) {
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly)) {  // Open the file
            qDebug() << "Failed to open file:" << file.errorString();
        }
        QTextStream in(&file);
        in.setEncoding(QStringConverter::Encoding::Utf32BE);
        content = in.readAll();
        newDevice.symbolType = extractAttribute(content, "SymbolType");
        file.close();
    }

    if (newDevice.symbolType.isEmpty()) {
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly)) {  // Open the file
            qDebug() << "Failed to open file:" << file.errorString();
        }
        QTextStream in(&file);
        in.setEncoding(QStringConverter::Encoding::Utf32LE);
        content = in.readAll();
        newDevice.symbolType = extractAttribute(content, "SymbolType");
        file.close();
    }

    if (newDevice.symbolType.isEmpty()) {
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly)) {  // Open the file
            qDebug() << "Failed to open file:" << file.errorString();
        }
        QTextStream in(&file);
        in.setEncoding(QStringConverter::Encoding::LastEncoding);
        content = in.readAll();
        newDevice.symbolType = extractAttribute(content, "SymbolType");
        file.close();
    }


    newDevice.spiceModel = extractAttribute(content, "SYMATTR SpiceModel");
    newDevice.modelFile = extractAttribute(content, "SYMATTR ModelFile");
    newDevice.value = extractAttribute(content, "SYMATTR Value");
    newDevice.value2 = extractAttribute(content, "SYMATTR Value2");

    QFileInfo fileInfo(filePath);
    QStringList parts = filePath.split('/');
    int n = parts.size();
    newDevice.name = parts[n - 2];
    newDevice.category = parts[n - 3];
    newDevice.encryption = parts[n - 4];
    newDevice.fileName = fileInfo.fileName();
    newDevice.todayDirPath = filePath;
    newDevice.relPath = "/lib/sym/" + newDevice.category + "/" + newDevice.fileName;

    utilities.logMessage("Symbol: " + newDevice.name + " SpiceModel: " + newDevice.spiceModel, mainWindow);
    utilities.logMessage("Symbol: " + newDevice.name + " ModelFile: " + newDevice.modelFile, mainWindow);
    utilities.logMessage("Symbol: " + newDevice.name + " Value: " + newDevice.value, mainWindow);
    utilities.logMessage("Symbol: " + newDevice.name + " Value2: " + newDevice.value2, mainWindow);
    return newDevice;
}

QString Symbol::extractAttribute(const QString& data, const QString& attribute) {
    int index = data.indexOf(attribute);
    if (index == -1) {
        return "";
    }
    int start = index + attribute.length();
    // Use a regex to match the rest of the line without leading whitespace
    QRegularExpression regex("\\s+(\\S+)");  // Match one or more whitespace followed by non-whitespace characters
    QRegularExpressionMatch match = regex.match(data, start);

    // Check if the regex match is found and extract the captured group
    if (match.hasMatch()) {
        return match.captured(1).trimmed();  // Return the trimmed matched value
    }
    return "";
}

SymbolStruct Symbol::getNewSymbolData(const QString &filePath) {
    SymbolStruct newDevice = extractParametersFromAsyFile(filePath, {});
    QStringList parts = filePath.split('/');
    int n = parts.size();
    newDevice.newOrUpdate = parts[n - 5];
    newDevice.todayDirPath = filePath;
    newDevice.relPath = "/lib/sym/" + newDevice.category + "/" + newDevice.fileName;
    return newDevice;
}

bool Symbol::checkSymbol(const QString& filePath, QSqlDatabase& db, MainWindow *mainWindow) {
    Utilities utilities;
    SymbolStruct newDevice = extractParametersFromAsyFile(filePath, {});
    if (newDevice.name.isEmpty()) {
        Utilities::logMessage("Error processing symbol: " + filePath, mainWindow);
        return false;
    }

    if (!db.isOpen()) {
        Utilities::logMessage("Database is not open!", mainWindow);
        return false;
    }

    QList<QString> deviceList;
    QList<QString> modelsList;
    if (!fetchDeviceList(db, "symbols", deviceList, mainWindow) || !fetchDeviceList(db, "models", modelsList, mainWindow)) {
        return false;
    }

    if (deviceList.contains(newDevice.name)) {
        return updateSymbol(newDevice, db, mainWindow);
    } else {
        qInfo() << "Symbol name: " << newDevice.name << " symbol file needs to be added.";
        newDevice.newOrUpdate = "new";
        return true;
    }
}

bool Symbol::insertOrUpdateSymbolInDB(SymbolStruct& newDevice, QSqlDatabase& db, MainWindow* mainWindow) {
    Utilities utilities;
    if (!db.isOpen()) {
        Utilities::logMessage("Database is not open!", mainWindow);
        return false;
    }

    DirStruct dir = DirPaths().buildDirPaths(mainWindow);
    QString symbolFilePath = dir.symDirPath + "/" + newDevice.category + "/" + newDevice.fileName;
    QFile symbolFile(symbolFilePath);
    if (!symbolFile.exists()) {
        Utilities::logMessage("Symbol file: " + symbolFilePath + " not found!", mainWindow);
        return false;
    }

    if (!symbolFile.open(QIODevice::ReadOnly)) {
        Utilities::logMessage("Could not open file for reading:" + symbolFile.errorString(), mainWindow);
        return false;
    }

    QByteArray binaryData = symbolFile.readAll();
    symbolFile.close();

    QList<QString> deviceList;
    if (!fetchDeviceList(db, "symbols", deviceList, mainWindow)) {
        return false;
    }

    if (deviceList.contains(newDevice.name)) {
        return updateSymbolInDB(newDevice, binaryData, db, dir, mainWindow);
    } else {
        return insertSymbolInDB(newDevice, binaryData, db, dir, mainWindow);
    }
}

bool Symbol::processSymbol(const QString& filePath, QSqlDatabase& db, MainWindow* mainWindow) {
    Utilities utilities;
    SymbolStruct newDevice = getNewSymbolData(filePath);
    if (newDevice.name.isEmpty()) {
        Utilities::logMessage("Error processing symbol: " + filePath, mainWindow);
        return false;
    }

    DirStruct dir = DirPaths().buildDirPaths(mainWindow);
    QString dstSymbolFilePath = dir.symDirPath + "/" + newDevice.category + "/" + newDevice.fileName;

    if (QFile::exists(dstSymbolFilePath)) {
        Utilities::backupFile(dstSymbolFilePath, mainWindow);
    }

    Utilities::updateFile(filePath, dstSymbolFilePath, mainWindow);

    return insertOrUpdateSymbolInDB(newDevice, db, mainWindow);
}

bool Symbol::updateSourceSymbol(const QString& filePath, MainWindow* mainWindow) {
    DirStruct dir = DirPaths().buildDirPaths(mainWindow);
    QStringList parts = filePath.split('/');
    int n = parts.size();
    QString category = parts[n - 3];
    QString dstSourceFilePath = dir.sourceLibSymPath + "/" + category + "/" + QFileInfo(filePath).fileName();
    Utilities utilities;
    Utilities::updateFile(filePath, dstSourceFilePath, mainWindow);
    return true;
}

bool Symbol::fetchDeviceList(QSqlDatabase& db, const QString& tableName, QList<QString>& deviceList, MainWindow *mainWindow) {
    Utilities utilities;
    QSqlQuery query(db);
    if (!query.exec("SELECT Name FROM " + tableName)) {
        Utilities::logMessage("Query failed:" + query.lastError().text(), mainWindow);
        return false;
    }

    while (query.next()) {
        deviceList.append(query.value(0).toString());
    }

    return true;
}

bool Symbol::updateSymbol(SymbolStruct& newDevice, QSqlDatabase& db, MainWindow* mainWindow) {
    Utilities utilities;
    QSqlQuery query(db);
    QString queryString = QString("SELECT Encrypted, Name, Category, FileName, RelPath, SpiceModel, ModelFile, Value, Value2 "
                                  "FROM Symbols WHERE Name = '%1'").arg(newDevice.name);
    if (!query.exec(queryString)) {
        qFatal() << "Error running query:" << query.lastError();
        return false;
    }

    if (query.next()) {
        SymbolStruct oldDevice;
        oldDevice.encryption = query.value(0).toString();
        oldDevice.name = query.value(1).toString();
        oldDevice.category = query.value(2).toString();
        oldDevice.fileName = query.value(3).toString();
        oldDevice.relPath = query.value(4).toString();
        oldDevice.spiceModel = query.value(5).toString();
        oldDevice.modelFile = query.value(6).toString();
        oldDevice.value = query.value(7).toString();
        oldDevice.value2 = query.value(8).toString();

        if (newDevice.encryption != oldDevice.encryption) {
            Utilities::logMessage("Encrypt is different in: " + newDevice.name, mainWindow);;
        }
        if (newDevice.category != oldDevice.category) {
            qFatal() << "Category is different in: " << newDevice.name;
            return false;
        }
        if (newDevice.fileName != oldDevice.fileName) {
            Utilities::logMessage("FileName is different in: " + newDevice.name, mainWindow);    ;
        }
        if (newDevice.spiceModel != oldDevice.spiceModel) {
            Utilities::logMessage("SpiceModel is different in: " + newDevice.name, mainWindow)  ;
            Utilities::logMessage("SpiceModel modified from: " + oldDevice.spiceModel + " to " + newDevice.spiceModel, mainWindow)  ;
            Utilities().removeOldModel(oldDevice.spiceModel, db, mainWindow);
        }
        if (newDevice.modelFile != oldDevice.modelFile) {
            Utilities::logMessage("ModelFile is different in: " + newDevice.name, mainWindow);
            Utilities::logMessage("ModelFile modified from: " + oldDevice.modelFile + " to " + newDevice.modelFile, mainWindow);
            Utilities().removeOldModel(oldDevice.modelFile, db, mainWindow);
        }
        if (newDevice.value != oldDevice.value) {
            qInfo() << "Value is different in: " << newDevice.name;
        }
        if (newDevice.value2 != oldDevice.value2) {
            qInfo() << "Value2 is different in: " << newDevice.name;
        }
    }

    return true;
}

bool Symbol::updateSymbolInDB(SymbolStruct& newDevice, const QByteArray& binaryData, QSqlDatabase& db, const DirStruct& dir, MainWindow *mainWindow) {
    Utilities utilities;
    QSqlQuery query(db);
    query.prepare("UPDATE Symbols SET Encrypted = :encryption, Date = :date, ReadOnly = 1, Category = :category, "
                  "FileName = :fileName, RelPath = :relPath, SpiceModel = :spiceModel, ModelFile = :modelFile, "
                  "Value = :value, Value2 = :value2, BinFile = :binFile WHERE Name = :name");
    query.bindValue(":encryption", newDevice.encryption);
    query.bindValue(":date", dir.dateString);
    query.bindValue(":category", newDevice.category);
    query.bindValue(":fileName", newDevice.fileName);
    query.bindValue(":relPath", newDevice.relPath);
    query.bindValue(":spiceModel", newDevice.spiceModel);
    query.bindValue(":modelFile", newDevice.modelFile);
    query.bindValue(":value", newDevice.value);
    query.bindValue(":value2", newDevice.value2);
    query.bindValue(":binFile", binaryData);
    query.bindValue(":name", newDevice.name);

    if (!query.exec()) {
        Utilities::logMessage("Error running update query:" + query.lastError().text(), mainWindow);
        return false;
    }

    return true;
}

bool Symbol::insertSymbolInDB(SymbolStruct& newDevice, const QByteArray& binaryData, QSqlDatabase& db, const DirStruct& dir, MainWindow *mainWindow) {
    QSqlQuery query(db);
    query.prepare("INSERT INTO Symbols (Name, Encrypted, Date, ReadOnly, Category, FileName, RelPath, SpiceModel, ModelFile, "
                  "Value, Value2, BinFile) VALUES (:name, :encryption, :date, 1, :category, :fileName, :relPath, :spiceModel, "
                  ":modelFile, :value, :value2, :binFile)");
    query.bindValue(":name", newDevice.name);
    query.bindValue(":encryption", newDevice.encryption);
    query.bindValue(":date", dir.dateString);
    query.bindValue(":category", newDevice.category);
    query.bindValue(":fileName", newDevice.fileName);
    query.bindValue(":relPath", newDevice.relPath);
    query.bindValue(":spiceModel", newDevice.spiceModel);
    query.bindValue(":modelFile", newDevice.modelFile);
    query.bindValue(":value", newDevice.value);
    query.bindValue(":value2", newDevice.value2);
    query.bindValue(":binFile", binaryData);

    if (!query.exec()) {
        Utilities::logMessage("Error running insert query:" + query.lastError().text(), mainWindow);
        return false;
    }

    return true;
}

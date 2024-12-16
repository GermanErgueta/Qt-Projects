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
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QFileInfo>
#include "utilities.h"

Symbol::Symbol() {}

SymbolStruct Symbol::extractParametersFromAsyFile(const QString &filePath ){
    SymbolStruct newDevice;
    bool spiceModelFound = false;
    bool modelFileFound = false;
    QString deviceSpiceModel;
    QString deviceModelFile;
    QString deviceValue;
    QString deviceValue2;

    QFileInfo fileInfo(filePath);
    QString fileName = fileInfo.fileName();
    QStringList parts = filePath.split('/');
    int n = parts.size();
    const QString& deviceName = parts[n-2];
    const QString& category  = parts[n-3];
    const QString& encryption = parts[n-4];
    QFile inputFile(filePath);
    if (!inputFile.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open file:" << filePath;
    }
    QByteArray fileData = inputFile.readAll();
    inputFile.close();

    QString stringData;
    QStringDecoder decoder(QStringDecoder::Encoding::System);

    // Decode the file content using UTF-8
    stringData = decoder.decode(fileData);
    if (decoder.hasError()) {
        // qWarning() << "Failed to decode as UTF-8. Falling back to Utf16.";
        // Fall back to Latin-1 encoding
        QStringDecoder fallbackDecoder(QStringDecoder::Encoding::Utf16);
        stringData = fallbackDecoder.decode(fileData);
        if (fallbackDecoder.hasError()) {
            // qWarning() << "Failed to decode as Utf16. Falling back to Windows-1252.";
            // Fall back to Latin-1 encoding
            QStringDecoder windows1252Decoder(QStringDecoder::Encoding::Utf8);
            stringData = windows1252Decoder.decode(fileData);
            // Check if Windows-1252 decoding also failed
            if (windows1252Decoder.hasError()) {
                qWarning() << "Failed to decode as Windows-1252 (CP-1252), utf-16 and utf-8.";
                return newDevice;
            }
        }
    }
    // Get SpiceModel
    QByteArray targetString = "SYMATTR SpiceModel ";
    int index = stringData.indexOf(targetString);
    if (index == -1) {
        // qWarning() << "SYMATTR SpiceModel not found in file!";
        spiceModelFound = false;
        deviceSpiceModel = "";
    }
    else
    {
        // Find the location where the model name begins (after "SYMATTR SpiceModel ")
        spiceModelFound = true;
        int spiceModelStart = index + targetString.length();
        QString spiceModel;
        for (int i = spiceModelStart; i < stringData.size(); ++i) {
            // Assuming the model name is followed by a space, newline, or null character
            if (stringData[i] == ' ' || stringData[i] == '\n' || stringData[i] == nullptr || stringData[i] == '\r') {
                break;
            }
            spiceModel.append(stringData.at(i));
        }
        deviceSpiceModel = spiceModel;
    }
    targetString = "SYMATTR ModelFile ";
    index = stringData.indexOf(targetString);
    if (index == -1) {
        // qWarning() << "SYMATTR ModelFile not found in file!";
        modelFileFound = false;
        deviceModelFile = "";
    }
    else
    {
        // Find the location where the model name begins (after "SYMATTR ModelFile ")
        modelFileFound = true;
        int modelFileStart = index + targetString.length();
        QString modelFile;
        for (int i = modelFileStart; i < stringData.size(); ++i) {
            // Assuming the model name is followed by a space, newline, or null character
            if (stringData[i] == ' ' || stringData[i] == '\n' || stringData[i] == nullptr || stringData[i] == '\r') {
                break;
            }
            modelFile.append(stringData.at(i));
        }
        deviceModelFile = modelFile;
    }
    if (!spiceModelFound and !modelFileFound) {
        qWarning() << "No SpiceModel or ModelFile found in device! " << deviceName;
    }
    // Get Value
    targetString = "SYMATTR Value ";
    index = stringData.indexOf(targetString);
    if (index == -1) {
        // qInfo() << "SYMATTR Value not found in file!";
        deviceValue = "";
    }
    else
    {
        // Find the location where the model name begins (after "SYMATTR Value ")
        int ValueStart = index + targetString.length();
        QString Value;
        for (int i = ValueStart; i < stringData.size(); ++i) {
            // Assuming the model name is followed by a space, newline, or null character
            if (stringData[i] == '\n' || stringData[i] == nullptr || stringData[i] == '\r') {
                break;
            }
            Value.append(stringData.at(i));
        }
        deviceValue = Value;
    }
    //Get Value2
    targetString = "SYMATTR Value2 ";
    index = stringData.indexOf(targetString);
    if (index == -1) {
        // qInfo() << "SYMATTR Value2 not found in file!";
        deviceValue2 = "";
    }
    else
    {
        // Find the location where the model name begins (after "SYMATTR Value2 ")
        int Value2Start = index + targetString.length();
        QString Value2;
        for (int i = Value2Start; i < stringData.size(); ++i) {
            // Assuming the model name is followed by a space, newline, or null character
            //                if (stringData[i] == ' ' || stringData[i] == '\n' || stringData[i] == '\0' || stringData[i] == '\r') {
            if (stringData[i] == '\n' || stringData[i] == nullptr || stringData[i] == '\r') {
                break;
            }
            Value2.append(stringData.at(i));
        }
        deviceValue2 = Value2;
    }
    if (spiceModelFound or modelFileFound){
        newDevice.name = deviceName;
        newDevice.encryption = encryption;
        newDevice.category = category;
        newDevice.fileName = fileName;
        newDevice.todayDirPath = filePath;
        newDevice.relPath = "/lib/sym/" + category + "/" + fileName;
        newDevice.spiceModel = deviceSpiceModel;
        newDevice.modelFile = deviceModelFile;
        newDevice.value = deviceValue;
        newDevice.value2 = deviceValue2;
    }
    return newDevice;
}

SymbolStruct Symbol::checkSymbol(const QString &filePath, QSqlDatabase &db){
    SymbolStruct newDevice = extractParametersFromAsyFile(filePath);
    //device.newOrUpdate = newOrUpdate;
    QString devName = newDevice.name;
    QString newEncryption = newDevice.encryption;
    QString newCategory = newDevice.category;
    QString newFileName = newDevice.fileName;
    QString newRelPath = newDevice.relPath;
    QString newSpiceModel = newDevice.spiceModel;
    QString newModelFile = newDevice.modelFile;
    QString newValue = newDevice.value;
    QString newValue2 = newDevice.value2;
    QString oldName;
    QString oldEncryption;
    QString oldCategory;
    QString oldFileName;
    QString oldRelPath;
    QString oldSpiceModel;
    QString oldModelFile;
    QString oldValue;
    QString oldValue2;

    QList<QString> deviceList;
    QList<QString> modelsList;

    QSqlQuery query;
    if (!query.exec("SELECT Name FROM symbols")) {
        qWarning() << "First query failed:" << query.lastError().text();
    } else {
        while (query.next()) {
            QString name = query.value(0).toString();  // First column: name
            deviceList.append(name);                   // Insert value into the QList
        }
    }

    if (!query.exec("SELECT Name FROM models")) {
        qWarning() << "First query failed:" << query.lastError().text();
    } else {
        while (query.next()) {
            QString name = query.value(0).toString();  // First column: name
            modelsList.append(name);                   // Insert value into the QList
        }
    }
    if( deviceList.contains(devName)){
        if (db.isOpen()) {
            QSqlQuery query(db);
            QString queryString = QString("SELECT Encrypted, Name, Category, FileName, RelPath, SpiceModel, ModelFile, Value, Value2 "
                                          "FROM Symbols "
                                          "WHERE Name = '%1'").arg(devName);
            if (query.exec(queryString)) {
                // Existing symbol. Update
                newDevice.newOrUpdate = "update";
                while (query.next()) {
                    oldEncryption = query.value(0).toString();
                    oldName = query.value(1).toString();
                    oldCategory = query.value(2).toString();
                    oldFileName = query.value(3).toString();
                    oldRelPath = query.value(4).toString();
                    oldSpiceModel = query.value(5).toString();
                    oldModelFile = query.value(6).toString();
                    oldValue = query.value(7).toString();
                    oldValue2 = query.value(8).toString();
                }
                newDevice.name = devName;
                if (newEncryption != oldEncryption){
                    newDevice.encryption = newEncryption;
                    qWarning() << "Encrypt is different in: " << newDevice.name << "\r\n";
                }
                else {
                    newDevice.encryption = newEncryption;
                }
                if (newCategory != oldCategory){
                    newDevice.category = newCategory;
                    qWarning() << "Category is different in: " << newDevice.name << "\r\n";
                    //qFatal("A serious error occurred, category is changed.");
                }
                else {
                    newDevice.category = newCategory;
                }
                if (newFileName != oldFileName){
                    newDevice.fileName = newFileName;
                    qWarning() << "Category is different in: " << newDevice.name << "\r\n";
                }
                else {
                    newDevice.fileName = newFileName;
                }
                newDevice.todayDirPath = filePath;
                newDevice.relPath = newRelPath;
                if (newSpiceModel != oldSpiceModel){
                    newDevice.spiceModel = newSpiceModel;
                    qWarning() << "SpiceModel is different in: " << newDevice.name << "\r\n";
                }
                else{
                    newDevice.spiceModel = newSpiceModel;
                }
                if (newModelFile != oldModelFile){
                    newDevice.modelFile = newModelFile;
                    qWarning() << "ModelFile is different in: " << newDevice.name << "\r\n";
                }
                else{
                    newDevice.modelFile = newModelFile;
                }
                if (newValue != oldValue){
                    newDevice.value = newValue;
                    qInfo() << "Value is different in: " << newDevice.name << "\r\n";
                }
                else {
                    newDevice.value = newValue;
                }
                if (newDevice.value2 != oldValue2){
                    newDevice.value2 = newValue2;
                    qInfo() << "Value2 is different in: " << newDevice.name << "\r\n";
                }
                else {
                    newDevice.value2 = newValue2;
                }
            } else {
                // It must be a new device. Process new symbol then
                qWarning() << "Error running query:" << query.lastError();
            }
        }
    }
    else{
        // Add new device
        qInfo() << "This is a new device:  " << devName;

        newDevice.name = devName;
        newDevice.encryption = newEncryption;
        newDevice.category = newCategory;
        newDevice.fileName = newFileName;
        newDevice.newOrUpdate = "update";
        newDevice.todayDirPath = filePath;
        newDevice.relPath = newRelPath;
        newDevice.spiceModel = newSpiceModel;
        newDevice.modelFile = newModelFile;
        newDevice.value = newValue;
        newDevice.value2 = newValue2;
        newDevice.newOrUpdate = "new";
    }
    return newDevice;
}


bool Symbol::insertOrUpdateSymbolInDB(SymbolStruct& newDevice, QSqlDatabase& db, MainWindow *mainWindow) {
    QList<QString> deviceList;
    QSqlQuery query;
    QString srcDate = mainWindow->getUi()->dateProcessing->date().toString("yyyy-MM-dd");
    QString LTspiceDevelopmentDirPath = mainWindow->getUi()->lineEditLTspiceDevelopment->text();
    QString modelsDirPath = LTspiceDevelopmentDirPath + "/" + "Models";
    QString libDirPath = modelsDirPath + "/" + "lib";
    QString symLibPath = libDirPath + "/" + "sym";
    QString symbolFilePath = symLibPath + "/" + newDevice.category + "/" + newDevice.fileName;
    QFile symbolFile = QFile(symbolFilePath);
    if (!symbolFile.exists()) {
        qWarning() << "Symbol file: " << symbolFilePath << " not found!";
        return false;
    }
    if (!db.isOpen()) {
        qWarning() << "Database is not open!";
        return false;
    }
    if (!symbolFile.open(QIODevice::ReadOnly)) {
        qWarning() << "Could not open file for reading:" << symbolFile.errorString();
        return false;
    }

    QByteArray binaryData = symbolFile.readAll();
    qDebug() << "Binary data size: " << binaryData.size();
    symbolFile.close();

    if (!query.exec("SELECT Name FROM symbols")) {
        qWarning() << "First query failed:" << query.lastError().text();
    }
    else {
        while (query.next()) {
            QString name = query.value(0).toString();  // First column: name
            deviceList.append(name);                   // Insert value into the QList
        }
    }
    if (deviceList.contains(newDevice.name)) {
        if (db.isOpen()) {
            QSqlQuery query(db);
            query.prepare("UPDATE Symbols "
                          "SET Encrypted = :encryption, "
                          "Date = :date, "
                          "ReadOnly = 1, "
                          "Category = :category, "
                          "FileName = :fileName, "
                          "RelPath = :relPath, "
                          "SpiceModel = :spiceModel, "
                          "ModelFile = :modelFile, "
                          "Value = :value, "
                          "Value2 = :value2, "
                          "BinFile = :binFile "
                          "WHERE Name = :name");

            // Bind values to parameters
            query.bindValue(":encryption", newDevice.encryption);
            query.bindValue(":date", srcDate);
            query.bindValue(":category", newDevice.category);
            query.bindValue(":fileName", newDevice.fileName);
            query.bindValue(":relPath", newDevice.relPath);
            query.bindValue(":spiceModel", newDevice.spiceModel);
            query.bindValue(":modelFile", newDevice.modelFile);
            query.bindValue(":value", newDevice.value);
            query.bindValue(":value2", newDevice.value2);
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
        insertQuery.prepare("INSERT INTO Symbols (Name, Encrypted, Date, ReadOnly, Category, FileName, RelPath, SpiceModel, ModelFile, Value, Value2, BinFile) "
                            "VALUES (:name, :encryption, :date, 1, :category, :fileName, :relPath, :spiceModel, :modelFile, :value, :value2, :binFile)");

        // Bind the insert values
        insertQuery.bindValue(":name", newDevice.name);
        insertQuery.bindValue(":encryption", newDevice.encryption);
        insertQuery.bindValue(":date", srcDate);
        insertQuery.bindValue(":category", newDevice.category);
        insertQuery.bindValue(":fileName", newDevice.fileName);
        insertQuery.bindValue(":relPath", newDevice.relPath);
        insertQuery.bindValue(":spiceModel", newDevice.spiceModel);
        insertQuery.bindValue(":modelFile", newDevice.modelFile);
        insertQuery.bindValue(":value", newDevice.value);
        insertQuery.bindValue(":value2", newDevice.value2);
        insertQuery.bindValue(":binFile", binaryData);  // Bind the binary data

        if (!insertQuery.exec()) {
            qWarning() << "Error running insert query:" << insertQuery.lastError();
            return false;
        }
    }
    return true;
}


bool Symbol::processSymbol(const QString &filePath, QSqlDatabase &db, MainWindow *mainWindow){
    Utilities utilities;
    Symbol symbol;

    QString LTspiceDevelopmentDirPath = mainWindow->getUi()->lineEditLTspiceDevelopment->text();
    QString sourceDirPath = mainWindow->getUi()->comboBoxSharePoint->currentText() + "/" + "Source";
    QString sourceLibDirPath = sourceDirPath + "/" + "lib";
    QString sourceSymLibPath = sourceLibDirPath + "/" + "sym";
    QString modelsDirPath = LTspiceDevelopmentDirPath + "/" + "Models";
    QString newModelsDirPath = modelsDirPath + "/" + "NewModels";
    QString srcDate = mainWindow->getUi()->dateProcessing->date().toString("yyyy-MM-dd");
    QString yearModelPath = newModelsDirPath + "/" + mainWindow->getUi()->dateProcessing->date().toString("yyyy");
    QString bakDirPath = modelsDirPath + "/" + "BAK" + "/" + srcDate.left(4);
    QString libDirPath = modelsDirPath + "/" + "lib";
    QString symLibPath = libDirPath + "/" + "sym";
    QString toBeReleasedDirPath = modelsDirPath + "/" + "ToBeReleased";
    QStringList parts = filePath.split('/');
    int n = parts.size();
    QString category = parts[n - 3];
    QFile srcSymbolFile = QFile(filePath);
    QFileInfo srcSymbolFileInfo = QFileInfo(srcSymbolFile);
    QString srcSymbolFilename = srcSymbolFileInfo.fileName();
    QString dstSymbolFilePath = symLibPath + "/" + category + "/" + srcSymbolFilename;
    QString dstSourceFilePath = sourceSymLibPath + "/" + category + "/" + srcSymbolFilename;
    QString bckFilenamePath = bakDirPath + "/" + srcSymbolFilename + "-" + srcDate;
    QFile dstSymbolFile = QFile(dstSymbolFilePath);
    // Add or update the symbol in the database
    QFileInfo fileInfo(filePath);
    QString consistentFilePath = QDir::toNativeSeparators(fileInfo.filePath());
    SymbolStruct newDevice = checkSymbol(filePath, db);
    if (newDevice.name.isEmpty()) {
        qWarning() << "Error processing symbol: " << filePath;
        return false;
    }
    else {
        if (dstSymbolFile.exists()) {
            utilities.backupFile(dstSymbolFilePath, mainWindow);
            if(!QFile::copy(filePath, dstSymbolFilePath)){
                qWarning() << filePath << " not copied.\r\n";
            }
        }
        else {
            if(!QFile::copy(filePath, dstSymbolFilePath)){
                qWarning() << filePath << " not copied.\r\n";
            }
        }
        utilities.updateFile(filePath, dstSourceFilePath);
        symbol.insertOrUpdateSymbolInDB(newDevice, db, mainWindow);
        return true;
    }
}

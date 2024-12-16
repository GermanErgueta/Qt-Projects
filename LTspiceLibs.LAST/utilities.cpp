#include "utilities.h"
#ifdef Q_OS_MAC
#include "Mac/utilities_mac.h"
#endif
#ifdef Q_OS_WINDOWS
#include "Windows/utilities_windows.h"
#endif
#include "symbol.h"
#include "model.h"
#include "example.h"
#include "changes.h"

Utilities::Utilities() {}


void Utilities::createSharePointJsonFile(const QStringList& fileList, const QString& jsonFilePath) {
    // Create a JSON array and populate it with the file paths from the QStringList
    QJsonArray fileArray;
    for (const QString& filePath : fileList) {
        fileArray.append(filePath);
    }

    // Create a JSON document from the array
    QJsonDocument doc(fileArray);

    // Write JSON document to file
    QFile jsonFile(jsonFilePath);
    if (!jsonFile.open(QIODevice::WriteOnly)) {
        qWarning() << "Could not open JSON file for writing:" << jsonFile.errorString();
        return;
    }

    jsonFile.write(doc.toJson(QJsonDocument::Indented));
    jsonFile.close();

    qDebug() << "JSON file created successfully at" << jsonFilePath;
}


void Utilities::createEmptyJsonFile(const QString& filename) {
    QJsonObject root;
    QJsonArray devices;
    root["devices"] = devices;

    QJsonDocument doc(root);
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson(QJsonDocument::Indented));
        file.close();
    }
}

QList<QString> Utilities::findZipFiles(MainWindow* mainWindow) {
    // const QString &localPath,
    // QSqlDatabase &db,
    // const QString &jsonFilename,
    // const QString &todayDirPath) {
    QList<QString> listOfZipFiles;
    QString sharePointPath = mainWindow->getUi()->comboBoxSharePoint->currentText();
    QString dirToBeSearched = sharePointPath + "/" + "Encrypted_To_Be_Released";
    QDirIterator itEnc(dirToBeSearched, QStringList() << "*.zip", QDir::Files, QDirIterator::Subdirectories);
    while (itEnc.hasNext()) {
        QString filePath = itEnc.next();  // Get the next file or directory path
        QFileInfo fileInfo(filePath);
        if (fileInfo.isDir()) {
            QString dirName = fileInfo.fileName();
            if (dirName == "." || dirName == ".." ) {
                qDebug() << "Skipping directory:" << dirName;
                continue;
            }
        }
        listOfZipFiles.append(filePath);
    }
    return listOfZipFiles;
}

// Check if the file exists
bool Utilities::fileExists(const QString& filename) {
    QFileInfo checkFile(filename);
    return checkFile.exists() && checkFile.isFile();
}

bool Utilities::unzipFile(const QString &zipFilePath, const QString &zipFileDirPath){
#ifdef Q_OS_MAC
    Utilities_mac utility_mac;
    //TODO
#endif
#ifdef Q_OS_WINDOWS
    Utilities_windows utility_windows;
    bool success = utility_windows.unzipFile(zipFilePath, zipFileDirPath);
    return success;
#endif
}

void Utilities::unzipFiles(const QStringList &zipFilenames, MainWindow *mainWindow){
    Utilities utilities;
    QDate today = mainWindow->getUi()->dateProcessing->date();
    QString srcDate = today.toString("yyyy-MM-dd");
    QString yearString = today.toString("yyyy");
    QString LTspiceDevelopmentDirPath = mainWindow->getUi()->lineEditLTspiceDevelopment->text();
    QString SharePointDirPath = mainWindow->getUi()->comboBoxSharePoint->currentText();
    QString modelsDirPath = LTspiceDevelopmentDirPath + "/" + "Models";
    QString newModelsDir = modelsDirPath + "/" + "NewModels";
    QString todayDirPath = newModelsDir + "/" + yearString + "/" + srcDate;
    QString jsonFilePath = todayDirPath + "/" + "devices.json";

    foreach(const QString &zipFilePath, zipFilenames) {
        QFile zipFile = QFile(zipFilePath);
        if(zipFile.exists()){
            QFileInfo fileInfo(zipFilePath);
            QString zipFileDirPath = fileInfo.path();
            if (utilities.unzipFile(zipFilePath, zipFileDirPath)) {
                SymbolStruct newSymbol;
                ModelStruct newModel;
                ExampleStruct newExample;
                ChangesStruct newChanges;
                Symbol symbol;
                Model model;
                Example example;
                Changes changes;

                Model mode;
                // Remove the ".zip" extension
                QString withoutExtension = zipFilePath.left(zipFilePath.lastIndexOf('.'));
                // Extract the "update" part after the underscore
                QStringList parts = zipFilePath.split("/");
                int n = parts.size();
                const QString& deviceName = parts[n-2];
                const QString& newOrUpdate = parts[n-5];
                QString asyFilePath = zipFileDirPath + "/" + deviceName + ".asy";
                QFile asyFile(asyFilePath);
                QString modFilePath = zipFileDirPath + "/" + deviceName + ".asc";
                QFile modFile(modFilePath);
                QString exFilePath = zipFileDirPath + "/" + "eg" + deviceName + ".asc";
                QFile exFile(exFilePath);
                QString chFilePath = zipFileDirPath + "/" + "changes.txt";
                QFile chFile(chFilePath);
                if ((newOrUpdate == "new") && (!chFile.exists())) {
                    if (!chFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
                        qDebug() << "Unable to open file for writing";
                    }
                    QTextStream out(&chFile);
                    out << "New device";
                    chFile.close();
                }
                Utilities::addRecord(jsonFilePath, zipFilePath, deviceName, asyFilePath, modFilePath, exFilePath, chFilePath, todayDirPath);
            }
        }
    }
}

QList<QString> Utilities::copyFiles(const QStringList &sourceFiles, MainWindow *mainWindow)
{
    QString sourcePath = mainWindow->getUi()->comboBoxSharePoint->currentText();
    QString LTspiceDevelopmentPath = mainWindow->getUi()->lineEditLTspiceDevelopment->text();
    QString modelsDirPath = LTspiceDevelopmentPath + "/" + "Models";
    QString newModelsDirPath = modelsDirPath + "/" + "NewModels";
    QString yearModelPath = newModelsDirPath + "/" + mainWindow->getUi()->dateProcessing->date().toString("yyyy");
    QString todayDirPath = yearModelPath + "/" + mainWindow->getUi()->dateProcessing->date().toString("yyyy-MM-dd");
    QDate processingDate = mainWindow->getUi()->dateProcessing->date();
    QDir baseDir(sourcePath);
    QList<QString> listOfNewZipFilenames;

    foreach(const QString &zipFilePath, sourceFiles) {
        QFile zipFile = QFile(zipFilePath);
        if(zipFile.exists()){
            // Extract file information
            QFileInfo fileInfo(zipFilePath);

            // Extract base name (filename without extension)
            QString filename = fileInfo.completeBaseName();  // project_part1_part2_v1
            QStringList baseNameSplit = filename.split('_');
            const QString& deviceName = baseNameSplit[0];
            const QString& newOrUpdate = baseNameSplit[1];
            QString extension = fileInfo.suffix();  // txt
            QStringList parts = zipFilePath.split('/');
            int n = parts.size();
            const QString& zipFilename = parts[n-1];
            const QString& category = parts[n-2];
            QString encryption = parts[n-3];
            if( encryption == "Encrypted_To_Be_Released")
                encryption = "encrypted";
            else
                encryption = "unencrypted";
            QString destZipFileName = todayDirPath + "/" + newOrUpdate + "/" + encryption + "/" + category + "/" + deviceName + "/" + zipFilename;
            QFileInfo destFileInfo(destZipFileName);
            QString destDirPath = destFileInfo.absolutePath();
            QDir destDir = QDir(destDirPath);
            if (destDir.mkpath(destDirPath)) {
                if (QFile::exists(destZipFileName)) {
                    // Remove the existing file
                    if (!QFile::remove(destZipFileName)) {
                        qDebug() << "Failed to remove existing file at destination:" << todayDirPath;
                    }
                }
                if (zipFile.copy(destZipFileName)) {
                    listOfNewZipFilenames.append(destZipFileName);
                    qDebug() << "Copied file:" << zipFilename << " to " << destZipFileName;
                } else {
                    qDebug() << "Failed to copy file:" << zipFile.errorString();
                }
            } else {
                qDebug() << "Failed to create directory:" << destDirPath;
            }
        }
    }
    return listOfNewZipFilenames;
}

void Utilities::addRecord(const QString& filename,
                          const QString& zipFilename,
                          const QString& deviceName,
                          const QString& symbolFilename,
                          const QString& modelFilename,
                          const QString& exampleFilename,
                          const QString& changesFilename,
                          QString &todayDirPath) {
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        file.close();

        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonObject root = doc.object();
        QJsonArray devices = root["devices"].toArray();
        QDir baseDir(todayDirPath);

        // Create new device record
        QJsonObject newDevice;
        QJsonObject content;
        if (fileExists(zipFilename)){
            QJsonObject newZip;
            QString relZipFilename = baseDir.relativeFilePath(zipFilename);
            newZip["filename"] = relZipFilename;
            content["zipFile"] = newZip;
        }
        if (fileExists(symbolFilename)){
            QJsonObject newSymbol;
            QString relSymbolFilename = baseDir.relativeFilePath(symbolFilename);
            newSymbol["filename"] = relSymbolFilename;
            content["symbol"] = newSymbol;
        }
        if (fileExists(modelFilename)){
            QJsonObject newModel;
            QString relModelFilename = baseDir.relativeFilePath(modelFilename);
            newModel["filename"] = relModelFilename;
            content["model"] = newModel;
        }
        if (fileExists(exampleFilename)){
            QJsonObject newExample;
            QString relExampleFilename = baseDir.relativeFilePath(exampleFilename);
            newExample["filename"] = relExampleFilename;
            content["example"] = newExample;
        }
        if (fileExists(changesFilename)){
            QJsonObject newChanges;
            QString relChangesFilename = baseDir.relativeFilePath(changesFilename);
            newChanges["filename"] = relChangesFilename;
            content["changes"] = newChanges;
        }
        // Only add the device if it has at least one valid file
        if (!content.isEmpty()) {
            newDevice[deviceName] = content;
            devices.append(newDevice);
        }

        root["devices"] = devices;
        // Write back to the JSON file
        doc.setObject(root);
        if(file.open(QIODevice::WriteOnly)) {
            file.write(doc.toJson(QJsonDocument::Indented));
            file.close();
        }
    }
}

QVector<Device> Utilities::parseJsonFile(const QString &filePath) {
    QVector<Device> devices;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file" << filePath;
        return devices;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(fileData);
    QJsonObject jsonObj = doc.object();
    QJsonArray devicesArray = jsonObj["devices"].toArray();

    for (const QJsonValue &deviceVal : devicesArray) {
        QJsonObject deviceObj = deviceVal.toObject();
        for (const QString &deviceName : deviceObj.keys()) {  // Use reference here
            Device device;
            device.name = deviceName;
            QJsonObject subfieldsObj = deviceObj[deviceName].toObject();
            for (const QString &subfieldName : subfieldsObj.keys()) {  // Use reference here
                device.subfields.insert(subfieldName, subfieldsObj[subfieldName].toObject()["filename"].toString());
            }
            devices.append(device);
        }
    }

    return devices;
}

SymbolStruct Utilities::getInformationFromSymbolFile(const QString &symbolFilePath){
    SymbolStruct symbol;
    QFile symbolFile(symbolFilePath);
    if (symbolFile.exists()){
        QStringList parts = symbolFilePath.split('/');
        int n = parts.size();
        symbol.fileName = parts[n-1];
        symbol.name = parts[n-2];
        symbol.category = parts[n-3];
        symbol.encryption = parts[n-4];
        return symbol;
    }
    else
        return symbol;
}

bool Utilities::checkDevicesInJsonFile(const QString &filePath, const QString &localPath, QSqlDatabase &db) {
    QVector<Device> devices;
    SymbolStruct symbolStruct;

    Symbol symbol;
    Model model;
    Example example;
    Changes changes;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file" << filePath;
        return false;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(fileData);
    QJsonObject jsonObj = doc.object();
    QJsonArray devicesArray = jsonObj["devices"].toArray();
    QString zipFileName;
    for (const auto &deviceVal : devicesArray) {
        QJsonObject deviceObj = deviceVal.toObject();
        for (const QString &deviceName : deviceObj.keys()) {  // Use reference here
            Device device;
            device.name = deviceName;
            symbolStruct.name = deviceName;
            QJsonObject subfieldsObj = deviceObj[deviceName].toObject();
            for (const QString &subfieldName : subfieldsObj.keys()) {  // Use reference here
                device.subfields.insert(subfieldName, subfieldsObj[subfieldName].toObject()["filename"].toString());
                if (subfieldName == "zipfile"){
                    zipFileName = localPath + "/" + subfieldsObj[subfieldName].toObject()["filename"].toString();
                    qInfo() << "zipfile filename is: " << zipFileName;
                    if (!fileExists(zipFileName)) {
                        qWarning() << "Failed to open file" << zipFileName;
                        return false;
                    }
                }
                if (subfieldName == "changes"){
                    QString changesFileName = localPath + "/" + subfieldsObj[subfieldName].toObject()["filename"].toString();
                    ChangesStruct newChanges = changes.checkChanges(changesFileName, db);
                    // qInfo() << "changes.txt filename is: " << changesFileName;
                }
                if (subfieldName == "symbol"){
                    QString symbolFileName = localPath + "/" + subfieldsObj[subfieldName].toObject()["filename"].toString();
                    SymbolStruct newSymbol = symbol.checkSymbol(symbolFileName, db);
                    // qInfo() << "symbol filename is: " << symbolFileName;
                }
                if (subfieldName == "model"){
                    QString modelFileName = localPath + "/" + subfieldsObj[subfieldName].toObject()["filename"].toString();
                    ModelStruct newModel = model.checkModel(modelFileName, db);
                    // qInfo() << "model filename is: " << modelFileName;
                }
                if (subfieldName == "example"){
                    QString exampleFileName = localPath + "/" + subfieldsObj[subfieldName].toObject()["filename"].toString();
                    ExampleStruct newExample = example.checkExample(exampleFileName, db);
                    // qInfo() << "example filename is: " << exampleFileName;
                }
            }
            devices.append(device);
        }
    }
    return true;
}

bool Utilities::updateFile(const QString& sourcePath, const QString& dstPath) {
    QFile srcFile = QFile(sourcePath);
    QFile dstFile = QFile(dstPath);
    if (srcFile.exists()) {
        if (dstFile.exists()) {
            dstFile.remove();
        }
        if(!QFile::copy(sourcePath, dstPath)){
            qWarning() << sourcePath << " not copied.\r\n";
        }
    }
    return true;
}

bool Utilities::exBackupFile(const QString& sourcePath, MainWindow* mainWindow) {
    QString LTspiceDevelopmentDirPath = mainWindow->getUi()->lineEditLTspiceDevelopment->text();
    QString modelsDirPath = LTspiceDevelopmentDirPath + "/" + "Models";
    QString srcDate = mainWindow->getUi()->dateProcessing->date().toString("yyyy-MM-dd");
    QString exBakDirPath = modelsDirPath + "/" + "examples" + "/" + "Applications" + "/" + "BAK" + "/" + srcDate.left(4);
    QDir exBakDir = QDir(exBakDirPath);
    if (!exBakDir.exists()) {
        exBakDir.mkpath(exBakDirPath);
    }
    QFile exFile = QFile(sourcePath);
    QFileInfo exFileInfo = QFileInfo(exFile);
    QString exFilename = exFileInfo.fileName();
    QString bckFilenamePath = exBakDirPath + "/" + exFilename + "-" + srcDate;
    QFile bckFile = QFile(bckFilenamePath);
    if (!bckFile.exists()) {
        exFile.rename(bckFilenamePath);
    }
    return true;
}


bool Utilities::backupFile(const QString &sourcePath, MainWindow *mainWindow) {
    QString LTspiceDevelopmentDirPath = mainWindow->getUi()->lineEditLTspiceDevelopment->text();
    QString modelsDirPath = LTspiceDevelopmentDirPath + "/" + "Models";
    QString srcDate = mainWindow->getUi()->dateProcessing->date().toString("yyyy-MM-dd");
    QString bakDirPath = modelsDirPath + "/" + "BAK" + "/" + srcDate.left(4);

    QFile srcFile = QFile(sourcePath);
    QFileInfo srcFileInfo = QFileInfo(srcFile);
    QString srcFilename = srcFileInfo.fileName();
    QString bckFilenamePath = bakDirPath + "/" + srcFilename + "-" + srcDate;
    QFile bckFile = QFile(bckFilenamePath);
    if (!bckFile.exists()) {
        srcFile.rename(bckFilenamePath);
    }
    return true;
}

bool Utilities::processDevicesInJsonFile(QSqlDatabase &db, MainWindow * mainWindow) {
    QVector<Device> devices;
    SymbolStruct symbolStruct;

    Symbol symbol;
    Model model;
    Example example;
    Changes changes;

    QDate today = mainWindow->getUi()->dateProcessing->date();
    QString srcDate = today.toString("yyyy-MM-dd");
    QString yearString = today.toString("yyyy");
    QString LTspiceDevelopmentDirPath = mainWindow->getUi()->lineEditLTspiceDevelopment->text();
    QString SharePointDirPath = mainWindow->getUi()->comboBoxSharePoint->currentText();
    QString modelsDirPath = LTspiceDevelopmentDirPath + "/" + "Models";
    QString newModelsDir = modelsDirPath + "/" + "NewModels";
    QString todayDirPath = newModelsDir + "/" + yearString + "/" + srcDate;
    QString jsonFilePath = todayDirPath + "/" + "devices.json";
    QString toBeReleasedDirPath = modelsDirPath + "/" + "ToBeReleased";
    QFile file(jsonFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file" << jsonFilePath;
        return false;
    }
    QDir ToBeReleasedDir = QDir(toBeReleasedDirPath);
    if (ToBeReleasedDir.exists()) {
        ToBeReleasedDir.removeRecursively();
        ToBeReleasedDir.mkpath(toBeReleasedDirPath);
    }
    if (!ToBeReleasedDir.exists()) {
        ToBeReleasedDir.mkpath(toBeReleasedDirPath);
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(fileData);
    QJsonObject jsonObj = doc.object();
    QJsonArray devicesArray = jsonObj["devices"].toArray();
    for (const auto &deviceVal : devicesArray) {
        QJsonObject deviceObj = deviceVal.toObject();
        for (const QString &deviceName : deviceObj.keys()) {  // Use reference here
            Device device;
            device.name = deviceName;
            symbolStruct.name = deviceName;
            QJsonObject subfieldsObj = deviceObj[deviceName].toObject();
            for (const QString &subfieldName : subfieldsObj.keys()) {  // Use reference here
                device.subfields.insert(subfieldName, subfieldsObj[subfieldName].toObject()["filename"].toString());
                if (subfieldName == "changes"){
                    QString changesFileName = todayDirPath + "/" + subfieldsObj[subfieldName].toObject()["filename"].toString();
                    ChangesStruct newChanges = changes.processChanges(changesFileName, db, mainWindow);
                }
                if (subfieldName == "symbol"){
                    QString symbolFileName = todayDirPath + "/" + subfieldsObj[subfieldName].toObject()["filename"].toString();
                    bool success = symbol.processSymbol(symbolFileName, db, mainWindow);
                }
                if (subfieldName == "model"){
                    QString modelFileName = todayDirPath + "/" + subfieldsObj[subfieldName].toObject()["filename"].toString();
                    ModelStruct newModel = model.processModel(modelFileName, db, mainWindow);
                }
                if (subfieldName == "example"){
                    QString exampleFileName = todayDirPath + "/" + subfieldsObj[subfieldName].toObject()["filename"].toString();
                    ExampleStruct newExample = example.processExample(exampleFileName, db, mainWindow);
                }
            }
            devices.append(device);
        }
    }
    return true;
}

bool Utilities::generateNetlistFile(const QString& filePath, MainWindow *mainWindow) {
    QString LTspiceDevelopmentDirPath = mainWindow->getUi()->lineEditLTspiceDevelopment->text();
    QString modelsDirPath = LTspiceDevelopmentDirPath + "/" + "Models";
    QString LTspiceExePath = modelsDirPath + "/" + "LTspice.exe";
    QFileInfo fileInfo(filePath);
    QString targetDirPath = fileInfo.absolutePath();
    QStringList arguments;
    QDir currentDir = QDir::current();
    // Change to the target directory
    if (!QDir::setCurrent(targetDirPath)) {
        qDebug() << "Failed to change directory to" << targetDirPath;
        return false;
    }
    // Generate the netlist
    QProcess process;
    QFileInfo fileinfo(filePath);
    arguments << "-sub" << fileInfo.fileName();
    process.start(LTspiceExePath, arguments);

    // Wait for the process to start
    if (!process.waitForStarted()) {
        qDebug() << "Failed to start process:" << process.errorString();
        return false;
    }
    process.waitForFinished();
    qDebug() << "Process output:" << process.readAllStandardOutput();
    qDebug() << "Process finished with exit code:" << process.exitCode();

    // Restore the original directory
    QDir::setCurrent(currentDir.absolutePath());

    return true;
}

bool Utilities::encryptFile( QString &filePath, MainWindow* mainWindow) {
    QString LTspiceDevelopmentDirPath = mainWindow->getUi()->lineEditLTspiceDevelopment->text();
    QString modelsDirPath = LTspiceDevelopmentDirPath + "/" + "Models";
    QString encryptExePath = modelsDirPath + "/" + "encrypt.exe";
    QFileInfo fileInfo(filePath);
    QString targetDirPath = fileInfo.absolutePath();
    QStringList arguments;
    QDir currentDir = QDir::current();
    // Change to the target directory
    if (!QDir::setCurrent(targetDirPath)) {
        qDebug() << "Failed to change directory to" << targetDirPath;
        return false;
    }
    // Start the external application
    QProcess process;
    QFileInfo fileinfo(filePath);
    arguments << fileInfo.fileName();
    process.start(encryptExePath, arguments);

    // Wait for the process to start
    if (!process.waitForStarted()) {
        qDebug() << "Failed to start process:" << process.errorString();
        return false;
    }
    process.waitForFinished();
    qDebug() << "Process output:" << process.readAllStandardOutput();
    qDebug() << "Process finished with exit code:" << process.exitCode();

    // Restore the original directory
    QDir::setCurrent(currentDir.absolutePath());

    return true;
}
bool Utilities::backupChangeLogTxtFile(MainWindow *mainWindow) {
    qInfo() << "Backup ChangeLog.txt file.\r\n";
    QString LTspiceDevelopmentDirPath = mainWindow->getUi()->lineEditLTspiceDevelopment->text();
    QString modelsDirPath = LTspiceDevelopmentDirPath + "/" + "Models";
    QString mainChangesLogTxtFilePath = modelsDirPath + "/" + "ChangeLog.txt";
    QFile mainChangesLogTxtFile(mainChangesLogTxtFilePath);
    QString srcDate = mainWindow->getUi()->dateProcessing->date().toString("yyyy-MM-dd");
    QString srcYear = mainWindow->getUi()->dateProcessing->date().toString("yyyy");
    QString mainChangesLogTxtFileBackupPath = modelsDirPath + "/" + "BAK" + "/" + srcYear + "/" + "ChangeLog.txt" + "-" + srcDate;
    QFile mainChangesLogTxtBackupFile(mainChangesLogTxtFileBackupPath);
    if (mainChangesLogTxtBackupFile.exists()) {
        if (mainChangesLogTxtFile.exists()) {
            mainChangesLogTxtFile.remove();
            if(!QFile::copy(mainChangesLogTxtFileBackupPath, mainChangesLogTxtFilePath)){
                qWarning() << mainChangesLogTxtFileBackupPath << " not copied.\r\n";
            }
        }
        else {
            if(!QFile::copy(mainChangesLogTxtFileBackupPath, mainChangesLogTxtFilePath)){
                qWarning() << mainChangesLogTxtFileBackupPath << " not copied.\r\n";
            }
        }
    }
    else {
        if(!QFile::copy(mainChangesLogTxtFileBackupPath, mainChangesLogTxtFilePath)){
            qWarning() << mainChangesLogTxtFileBackupPath << " not copied.\r\n";
        }
    }
    qInfo() << "Finished backup ChangeLog.txt file.\r\n";
    return true;
}


QSet<QString> Utilities::findDuplicates(const QList<QString>& list){
    QSet<QString> seen;
    QSet<QString> duplicates;

    for (const QString& str : list) {
        if (seen.contains(str)) {
            duplicates.insert(str);
        } else {
            seen.insert(str);
        }
    }

    return duplicates;
}

void Utilities::removeBadRecords(QSqlDatabase& db){
    if (!db.isOpen()) {
        qWarning() << "Database is not open!";
        return;
    }

    // Prepare the query to select records
    QSqlQuery selectQuery(db);
    if (!selectQuery.exec("SELECT id, Name, RelPath FROM symbols")) {
        qWarning() << "Failed to retrieve records:" << selectQuery.lastError();
        return;
    }

    // Iterate over each record to check the condition
    QSqlQuery deleteQuery(db);
    while (selectQuery.next()) {
        QString name = selectQuery.value("Name").toString();
        QString relPath = selectQuery.value("RelPath").toString();
        int id = selectQuery.value("id").toInt(); // Assuming there's a unique ID column
        QString nameToMatch = relPath.section('/', -1).section(".asy", 0, 0);
        // Check if Name matches and is found within RelPath
        if (name != nameToMatch) {
            // Prepare and execute delete statement for the non-matching record
            deleteQuery.prepare("DELETE FROM symbols WHERE id = :id");
            deleteQuery.bindValue(":id", id);
            if (!deleteQuery.exec()) {
                qWarning() << "Failed to delete record with id" << id << ":" << deleteQuery.lastError();
            } else {
                qDebug() << "Deleted record with id" << id;
            }
        }
    }
    qDebug() << "Finished removing non-matching records.";
}


bool Utilities::generateFilesToProcess(QSqlDatabase &db,MainWindow* mainWindow){
    QList<QString> symbolsFileList;
    QList<QString> modelFilesList;
    QList<QString> examplesFilesList;

    QString filesToProcessedDirPath = mainWindow->getUi()->lineEditFilesToProcess->text();
    QDir filesToProcessDir(filesToProcessedDirPath);
    QString LTspiceDevelopmentDirPath = mainWindow->getUi()->lineEditLTspiceDevelopment->text();
    QString modelsDirPath = LTspiceDevelopmentDirPath + "/" + "Models";

    if (db.isOpen()) {
        QSqlQuery querySymbols(db);
        if (filesToProcessDir.exists()){
            filesToProcessDir.removeRecursively();
            filesToProcessDir.mkpath(filesToProcessedDirPath);
        }
        if (!querySymbols.exec("SELECT RelPath FROM symbols")) {
            qWarning() << "First query failed:" << querySymbols.lastError().text();
        } else {
            while (querySymbols.next()) {
                QString name = querySymbols.value(0).toString();  // First column: name
                symbolsFileList.append(name);                   // Insert value into the QList
            }
        }
        QSet<QString> duplicates = findDuplicates(symbolsFileList);
        for (QString& file : symbolsFileList){
            QString src = modelsDirPath + file;
            QString dst = filesToProcessedDirPath + file;
            QFile dstFile = QFile(dst);
            QString dstDirPath = QFileInfo(dstFile).path();
            QDir dstDir = QDir(dstDirPath);
            if( !dstDir.exists()){
                dstDir.mkpath(dstDirPath);
            }
            if(!QFile::copy(src, dst)){
                qWarning() << src << " file was not copied.\r\n";
            }
        }
        QSqlQuery queryModels(db);
        if (!queryModels.exec("SELECT RelPath FROM models")) {
            qWarning() << "First query failed:" << queryModels.lastError().text();
        } else {
            while (queryModels.next()) {
                QString name = queryModels.value(0).toString();  // First column: name
                modelFilesList.append(name);                   // Insert value into the QList
            }
        }
        for (QString& file : modelFilesList){
            QString src = modelsDirPath + file;
            QString dst = filesToProcessedDirPath + file;
            QFile dstFile = QFile(dst);
            QString dstDirPath = QFileInfo(dstFile).path();
            QDir dstDir = QDir(dstDirPath);
            if( !dstDir.exists()){
                dstDir.mkpath(dstDirPath);
            }
            if (!QFile::copy(src, dst)){
                qWarning() << src << " file was not copied.\r\n";
            }
        }
        QSqlQuery queryExamples(db);
        if (!queryExamples.exec("SELECT RelPath FROM examples")) {
            qWarning() << "First query failed:" << queryExamples.lastError().text();
        } else {
            while (queryExamples.next()) {
                QString name = queryExamples.value(0).toString();  // First column: name
                examplesFilesList.append(name);                   // Insert value into the QList
            }
        }
        for (QString& file : examplesFilesList){
            QString src = modelsDirPath + file;
            QString dst = filesToProcessedDirPath + file;
            QFile dstFile = QFile(dst);
            QString dstDirPath = QFileInfo(dstFile).path();
            QDir dstDir = QDir(dstDirPath);
            if( !dstDir.exists()){
                dstDir.mkpath(dstDirPath);
            }
            if (!QFile::copy(src, dst)){
                qWarning() << src << " file was not copied.\r\n";
            }
        }
    }
    return true;
}


void Utilities::compressDir(const QString &directoryPath, const QString &outputZipPath, const QString &comment) {
    // Create a Chilkat Zip object
    CkZip zip;

    // Unlock the Chilkat Zip library
    if (!zip.UnlockComponent("CB4092026_RqTt5hNQ4Snb")) {
        qDebug() << "Failed to unlock Chilkat library";
        return;
    }

    // Set comment for the entire zip file
    zip.put_Comment(comment.toStdString().c_str());

    // Initialize the zip file
    if (!zip.NewZip(outputZipPath.toStdString().c_str())) {
        qDebug() << "Failed to create the zip file";
        return;
    }

    // Add the directory to the zip as a root folder
    bool recurse = true; // Recursively add subdirectories
    bool saveExtraPath = true; // Save the directory structure in the zip
    bool archiveOnly = false;
    bool includeHiden = false;
    bool includeSystem = false;
    if (!zip.AppendFilesEx(directoryPath.toStdString().c_str(), recurse, saveExtraPath, archiveOnly, includeHiden, includeSystem)) {
        qDebug() << "Failed to add directory to zip";
        return;
    }
    // Extract the name of the target directory (one level above)
    QDir tmpBaseDir(directoryPath);
    QString baseDirPath = tmpBaseDir.absolutePath() + "/..";
    QDir baseDir = QDir(baseDirPath);


    // Loop through entries to set limited path depth and add comments
    for (int i = 0; i < zip.get_NumEntries(); i++) {
        CkZipEntry *entry = zip.GetEntryByIndex(i);
        if (entry == nullptr) continue;

        // Get the original full path of the entry
        QString originalPath = entry->fileName();
        QString modifiedPath = "/" + originalPath;

        // Modify entry name to include only the relative path directory name
        QString relativePath = baseDir.relativeFilePath(modifiedPath);
        // QString adjustedPath = baseDirPath + "/" + QFileInfo(originalPath).fileName();
        // entry->put_FileName(adjustedPath.toStdString().c_str());
        entry->put_FileName(relativePath.toStdString().c_str());

        // Set a comment for the entry
        //QString comment = QString("Comment for %1").arg(adjustedPath);
        QString comment = QString("Comment for %1").arg(relativePath);
        entry->put_Comment(comment.toStdString().c_str());

        delete entry;  // Clean up
    }

    // Write the zip file to disk
    if (!zip.WriteZipAndClose()) {
        qDebug() << "Failed to write and close the zip file";
        return;
    }

    qDebug() << "Directory successfully encrypted and zipped.";
}



void Utilities::generateLTspiceUpdate(MainWindow* mainWindow) {
    QString LTspiceDevelopmentDirPath = mainWindow->getUi()->lineEditLTspiceDevelopment->text();
    QString modelsDirPath = LTspiceDevelopmentDirPath + "/" + "Models";
    QString newModelsDirPath = modelsDirPath + "/" + "NewModels";
    QDate today = mainWindow->getUi()->dateProcessing->date();
    QString srcDate = today.toString("yyyy-MM-dd");
    QString yearString = today.toString("yyyy");
    QString yearDirPath = newModelsDirPath + "/" + yearString;
    QString dayYearDirPath = yearDirPath + "/" + srcDate;

    QString toSendDirPath = modelsDirPath + "/" + "ToSend";
    QString LTspiceExePath = "LTspice.exe";
    QString toSendFilesPath = toSendDirPath + "/" + "files";
    QDir currentDir = QDir::current();
    // OBjective:     cmd = ".\\LTspice.exe -genweb update -local"
    QStringList arguments;
    //    arguments.append("-genweb update -local");
    arguments << "-genweb" << "update" << "-local";
    if (!QDir::setCurrent(toSendDirPath)) {
        qDebug() << "Failed to change directory to" << toSendDirPath;
        return;
    }
    QProcess process;
    process.start(LTspiceExePath, arguments);
    if (!process.waitForStarted()) {
        qDebug() << "Failed to start process:" << process.errorString();
        return;
    }
    process.waitForFinished();
    qDebug() << "Process output:" << process.readAllStandardOutput();
    qDebug() << "Process finished with exit code:" << process.exitCode();
    process.close();
    QDir::setCurrent(currentDir.absolutePath());
    QString srcPath = toSendDirPath + "/" + "release.log";
    QString dstPath = dayYearDirPath + "/" + "release.log";
    if (QFile(dstPath).exists()){
        QFile(dstPath).remove();
    }
    if(!QFile(srcPath).copy(dstPath)){
        qWarning() << srcPath << " could not be copied";
    }
    srcPath = toSendFilesPath + "/" + "lib.zip";
    dstPath = dayYearDirPath + "/" + "lib.zip";
    if (QFile(dstPath).exists()){
        QFile(dstPath).remove();
    }
    if(!QFile(srcPath).copy(dstPath)){
        qWarning() << srcPath << " could not be copied";
    }
    srcPath = toSendFilesPath + "/" + "examples.zip";
    dstPath = dayYearDirPath + "/" + "examples.zip";
    if (QFile(dstPath).exists()){
        QFile(dstPath).remove();
    }
    if (!QFile::copy(srcPath, dstPath)) {
        qWarning() << srcPath << " could not be copied";
    }
}


void Utilities::removeZipFromSharepoint(MainWindow *mainWindow) {
    QDate today = mainWindow->getUi()->dateProcessing->date();
    QString srcDate = today.toString("yyyy-MM-dd");
    QString yearString = today.toString("yyyy");
    QString LTspiceDevelopmentDirPath = mainWindow->getUi()->lineEditLTspiceDevelopment->text();
    QString modelsDirPath = LTspiceDevelopmentDirPath + "/" + "Models";
    QString newModelsDir = modelsDirPath + "/" + "NewModels";
    QString todayDirPath = newModelsDir + "/" + yearString + "/" + srcDate;
    QString jsonFilePath = todayDirPath + "/" + "sharePoint.json";

    QFile jsonFile(jsonFilePath);
    if (!jsonFile.open(QIODevice::ReadOnly)) {
        qWarning() << "Could not open JSON file for reading:" << jsonFile.errorString();
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(jsonFile.readAll());
    jsonFile.close();

    if (!doc.isArray()) {
        qWarning() << "Invalid JSON format. Expected an array.";
        return;
    }

    QJsonArray fileArray = doc.array();

    for (const QJsonValue& value : fileArray) {
        QString filePath = value.toString();
        QFile file(filePath);

        if (file.exists()) {
            if (file.remove()) {
                qDebug() << "Removed:" << filePath;
            }
            else {
                qWarning() << "Failed to remove:" << filePath;
            }
        }
        else {
            qWarning() << "File not found:" << filePath;
        }
    }
}


void Utilities::buildLTspiceJsonFile(MainWindow *mainWindow)
{
    QDate today = mainWindow->getUi()->dateProcessing->date();
    QString logDate = today.toString("MM-dd-yy");
    QString LTspiceDevelopmentDirPath = mainWindow->getUi()->lineEditLTspiceDevelopment->text();
    QString modelsDirPath = LTspiceDevelopmentDirPath + "/" + "Models";
    QString LTspice17 = "";
    QString LTspiceMac = mainWindow->getUi()->lineEditMacVersion->text();
    QString LTspice24 = mainWindow->getUi()->lineEditWindowsVersion->text();
    QString update = logDate;
    QString LTspiceJsonPath = modelsDirPath + "/" + "LTspice.json";
    QJsonObject rootObject;
    QJsonObject downloadsObject;
    QJsonObject download1;
    download1["Filename"] = "LTspice64.exe";
    download1["Version"] = "";
    QJsonObject download2;
    download2["Filename"] = "LTspice.pkg";
    download2["Version"] = LTspiceMac;
    QJsonObject download3;
    download3["Filename"] = "LTspice64.msi";
    download3["Version"] = LTspice24;
    downloadsObject["Download LTspice XVII (End of Support)"] = download1;
    downloadsObject["Download for MacOS 10.15 and forward"] = download2;
    downloadsObject["Download for Windows 10 64-bit and forward"] = download3;
    rootObject["Downloads"] = downloadsObject;
    rootObject["Installation"] = logDate;
    rootObject["LTspice_Mac"] = LTspiceMac;
    rootObject["Models"] = logDate;
    QJsonDocument jsonDoc(rootObject);
    QFile file(LTspiceJsonPath);
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(jsonDoc.toJson());
        file.close();
    }
}

bool Utilities::runWebPush(MainWindow* mainWindow) {
    QString LTspiceDevelopmentDirPath = mainWindow->getUi()->lineEditLTspiceDevelopment->text();
    QString modelsDirPath = LTspiceDevelopmentDirPath + "/" + "Models";
    QString webPushExePath = modelsDirPath + "/" + "WebPush.exe";
    QStringList arguments;
    QDir currentDir = QDir::current();
    // Change to the target directory
    if (!QDir::setCurrent(modelsDirPath)) {
        qDebug() << "Failed to change directory to" << modelsDirPath;
        return false;
    }
    QProcess process;
    arguments << "-connect";
    process.start(webPushExePath, arguments);

    // Wait for the process to start
    if (!process.waitForStarted()) {
        qDebug() << "Failed to start process:" << process.errorString();
        return false;
    }
    process.waitForFinished();
    qDebug() << "Process output:" << process.readAllStandardOutput();
    qDebug() << "Process finished with exit code:" << process.exitCode();

    // Restore the original directory
    QDir::setCurrent(currentDir.absolutePath());

    return true;
}

#include "utilities.h"
#include "Windows/utilities_windows.h"
#include "symbol.h"
#include "model.h"
#include "example.h"
#include "changes.h"
#include "dirpaths.h"
#include "ui_mainwindow.h"

Utilities::Utilities() {}

void Utilities::logMessage(const QString& message, MainWindow* mainWindow, bool isWarning)
{
    if (isWarning) {
        qWarning() << message;
        mainWindow->getUi()->textEditMessages->append("Warning: " + message);
    } else {
        qInfo() << message;
        mainWindow->getUi()->textEditMessages->append("Info: " + message);
    }
}

void Utilities::createSharePointJsonFile(const QStringList& fileList, const QString& jsonFilePath, MainWindow* mainWindow) {
    // Create a JSON array and populate it with the file paths from the QStringList
    QJsonArray fileArray;
    for (const QString& filePath : fileList) {
        fileArray.append(filePath);
    }
    // Create a JSON document from the array
    QJsonDocument doc(fileArray);
    // Write JSON document to file
    QFile jsonFile = QFile(jsonFilePath);
    QFileInfo jsonFileInfo(jsonFile);
    QString jsonFileName = jsonFileInfo.fileName();
    QString jsonFileDirPath = jsonFileInfo.path();
    QDir jsonFileDir = QDir(jsonFileDirPath);
    if (!jsonFileDir.exists()) {
        jsonFileDir.mkpath(jsonFileDirPath);
    }
    if (jsonFileInfo.exists()) {
        jsonFile.remove();
    }
    if (!jsonFile.open(QIODevice::WriteOnly)) {
        logMessage("Could not open JSON file for writing:" + jsonFile.errorString(), mainWindow);
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
    DirStruct dir;
    DirPaths dirPaths;
    dir = dirPaths.buildDirPaths(mainWindow);

    QList<QString> listOfZipFiles;

    QString dirToBeSearched = dir.sharePointPath + "Encrypted_To_Be_Released";
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

bool Utilities::unzipFile(const QString &zipFilePath, const QString &zipFileDirPath, MainWindow *mainWindow){
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
    DirStruct dir;
    DirPaths dirPaths;
    dir = dirPaths.buildDirPaths(mainWindow);

    foreach(const QString &zipFilePath, zipFilenames) {
        QFile zipFile = QFile(zipFilePath);
        if(zipFile.exists()){
            QFileInfo fileInfo(zipFilePath);
            QString zipFileDirPath = fileInfo.path();
            if (Utilities::unzipFile(zipFilePath, zipFileDirPath, mainWindow)) {
                SymbolStruct newSymbol;
                ModelStruct newModel;
                ExampleStruct newExample;
                ChangesStruct newChanges;
                Symbol symbol;
                Model model;
                Example example;
                Changes changes;

                Model mode;
                QString withoutExtension = zipFilePath.left(zipFilePath.lastIndexOf('.'));
                QStringList parts = zipFilePath.split("/");
                int n = parts.size();
                const QString& deviceName = parts[n-2];
                const QString& newOrUpdate = parts[n-5];
                QString asyFilePath = zipFileDirPath + "/" + deviceName + ".asy";
                QString modFilePath = zipFileDirPath + "/" + deviceName + ".asc";
                QFile modFile(modFilePath);
                if(!modFile.exists())
                    modFilePath = zipFileDirPath + "/" + deviceName + ".net";
                QString exFilePath = zipFileDirPath + "/" + "eg" + deviceName + ".asc";
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
                Utilities::addRecord(dir.jsonFilePath, zipFilePath, deviceName, asyFilePath, modFilePath, exFilePath, chFilePath, dir.todayDirPath);
            }
        }
    }
}

QList<QString> Utilities::copyFiles(const QStringList &sourceFiles, MainWindow *mainWindow)
{
    DirStruct dir;
    DirPaths dirPaths;
    dir = dirPaths.buildDirPaths(mainWindow);

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
            QString destZipFileName = dir.todayDirPath + newOrUpdate + "/" + encryption + "/" + category + "/" + deviceName + "/" + zipFilename;
            QFileInfo destFileInfo(destZipFileName);
            QString destDirPath = destFileInfo.absolutePath();
            QDir destDir = QDir(destDirPath);
            if (destDir.mkpath(destDirPath)) {
                if (QFile::exists(destZipFileName)) {
                    // Remove the existing file
                    if (!QFile::remove(destZipFileName)) {
                        qDebug() << "Failed to remove existing file at destination:" << dir.todayDirPath;
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

bool Utilities::checkDevicesInJsonFile(const QString &filePath, const QString &localPath, QSqlDatabase &db, MainWindow *mainWindow) {
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
                        logMessage("Failed to open file" + zipFileName, mainWindow);
                        return false;
                    }
                }
                if (subfieldName == "changes"){
                    QString changesFileName = localPath + subfieldsObj[subfieldName].toObject()["filename"].toString();
                    if(!changes.checkChanges(changesFileName, mainWindow)){
                        logMessage("changes.txt could not be checked for: " + device.name + "\r", mainWindow);
                    }
                }
                if (subfieldName == "symbol"){
                    QString symbolFileName = localPath + subfieldsObj[subfieldName].toObject()["filename"].toString();
                    if (!symbol.checkSymbol(symbolFileName, db, mainWindow)){
                        logMessage("symbol could not be checked for: " + device.name + "\r", mainWindow);
                    }
                }
                if (subfieldName == "model"){
                    QString modelFileName = localPath + subfieldsObj[subfieldName].toObject()["filename"].toString();
                    if (!model.checkModel(modelFileName, db, mainWindow)){
                        logMessage("model could not be checked for: " + device.name +"\r", mainWindow);
                    }
                }
                if (subfieldName == "example"){
                    QString exampleFileName = localPath + "/" + subfieldsObj[subfieldName].toObject()["filename"].toString();
                    if (!example.checkExample(exampleFileName, db, mainWindow)){
                        logMessage("example could not be checked for: " + device.name + "\r", mainWindow);
                    }
                }
            }
            devices.append(device);
        }
    }
    return true;
}

bool Utilities::updateFile(const QString& sourcePath, const QString& dstPath, MainWindow* mainWindow) {
    QFile srcFile = QFile(sourcePath);
    QFile dstFile = QFile(dstPath);
    if (srcFile.exists()) {
        if (dstFile.exists()) {
            dstFile.remove();
        }
        if(!QFile::copy(sourcePath, dstPath)){
            logMessage("Failed to copy file: " + sourcePath, mainWindow);
        }
    }
    return true;
}

bool Utilities::exBackupFile(const QString& sourcePath, MainWindow* mainWindow) {
    DirStruct dir;
    DirPaths dirPaths;
    dir = dirPaths.buildDirPaths(mainWindow);

    QDir exBakDir = QDir(dir.applicationsBckDirPath);
    if (!exBakDir.exists()) {
        exBakDir.mkpath(dir.applicationsBckDirPath);
    }
    QFile exFile = QFile(sourcePath);
    QFileInfo exFileInfo = QFileInfo(exFile);
    QString exFilename = exFileInfo.fileName();
    QString bckFilenamePath = dir.applicationsBckDirPath + exFilename + "-" + dir.dateString;
    QFile bckFile = QFile(bckFilenamePath);
    if (!bckFile.exists()) {
        exFile.rename(bckFilenamePath);
    }
    return true;
}


bool Utilities::backupFile(const QString &sourcePath, MainWindow *mainWindow) {
    DirStruct dir;
    DirPaths dirPaths;
    dir = dirPaths.buildDirPaths(mainWindow);

    QFile srcFile = QFile(sourcePath);
    QFileInfo srcFileInfo = QFileInfo(srcFile);
    QString srcFilename = srcFileInfo.fileName();
    QString bckFilenamePath = dir.bckDirPath + srcFilename + "-" + dir.dateString;
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
    DirStruct dir;
    DirPaths dirPaths;
    dir = dirPaths.buildDirPaths(mainWindow);

    QFile file(dir.jsonFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        logMessage("Failed to open file" + dir.jsonFilePath, mainWindow);
        return false;
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
                    QString changesFileName = dir.todayDirPath + subfieldsObj[subfieldName].toObject()["filename"].toString();
                    if (!changes.processChanges(changesFileName, mainWindow)){
                        logMessage("changes.txt could not be processed for: " + device.name, mainWindow);
                    }
                    else
                    {
                        logMessage("changes.txt processed for: " + device.name, mainWindow);
                    }
                }
                if (subfieldName == "symbol"){
                    QString symbolFileName = dir.todayDirPath + subfieldsObj[subfieldName].toObject()["filename"].toString();
                    if (!symbol.processSymbol(symbolFileName, db, mainWindow)){
                        logMessage("symbol could not be processed for: " + device.name, mainWindow);
                    }
                    else
                    {
                        logMessage("symbol processed for: " + device.name, mainWindow);
                    }
                }
                if (subfieldName == "model"){
                    QString modelFileName = dir.todayDirPath + subfieldsObj[subfieldName].toObject()["filename"].toString();
                    if (!model.processModel(modelFileName, db, mainWindow))
                    {
                        logMessage("model could not be processed for: " + device.name, mainWindow);
                    }
                    else
                    {
                        logMessage("model processed for: " + device.name, mainWindow);
                    }
                }
                if (subfieldName == "example"){
                    QString exampleFileName = dir.todayDirPath + subfieldsObj[subfieldName].toObject()["filename"].toString();
                    if (!example.processExample(exampleFileName, db, mainWindow))
                    {
                        logMessage("example could not be processed for: " + device.name, mainWindow);
                    }
                    else
                    {
                        logMessage("example processed for: " + device.name, mainWindow);
                    }
                }
            }
            devices.append(device);
        }
    }
    return true;
}

bool Utilities::generateNetlistFile(const QString& filePath, MainWindow *mainWindow) {
    DirStruct dir;
    DirPaths dirPaths;
    dir = dirPaths.buildDirPaths(mainWindow);

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
    process.start(dir.LTspiceExeFilePath, arguments);

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
    DirStruct dir;
    DirPaths dirPaths;
    dir = dirPaths.buildDirPaths(mainWindow);
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
    process.start(dir.encryptExeFilePath, arguments);

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
    logMessage("Started backup ChangeLog.txt file.", mainWindow);
    DirStruct dir;
    DirPaths dirPaths;
    dir = dirPaths.buildDirPaths(mainWindow);
    QFile changesLogFile(dir.changeLogPath);
    QFile changesLogBckFile(dir.changeLogBckPath);
    if (!changesLogBckFile.exists()) {
        if (!QFile::copy(dir.changeLogPath, dir.changeLogBckPath)){
            logMessage("ChangeLog.txt backup file could not be copied to backup despite not being available.", mainWindow);
            return false;
        }
    }
    else {
        if (changesLogFile.exists()) {
            if (!QFile::remove(dir.changeLogPath)) {
                logMessage("ChangeLog.txt could not be removed.", mainWindow);
                return false;
            }
            if (!QFile::copy(dir.changeLogBckPath, dir.changeLogPath)) {
                logMessage("ChangeLog.txt could not be created from the backup already done.", mainWindow);
                return false;
            }
        }
    }
    logMessage("Finished backup ChangeLog.txt file.", mainWindow);
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

void Utilities::removeBadRecords(QSqlDatabase& db, MainWindow* mainWindow){
    if (!db.isOpen()) {
        logMessage("Database is not open!", mainWindow);
        return;
    }
    // Prepare the query to select records
    QSqlQuery selectQuery(db);
    if (!selectQuery.exec("SELECT id, Name, RelPath FROM symbols")) {
        logMessage("Failed to retrieve records:" + selectQuery.lastError().text(), mainWindow);
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
                logMessage("Failed to delete record with id" + QString::number(id) + ":" + deleteQuery.lastError().text(), mainWindow);;
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
    DirStruct dir;
    DirPaths dirPaths;
    dir = dirPaths.buildDirPaths(mainWindow);
    QDir filesToProcessDir(dir.toProcessDirPath);

    if (db.isOpen()) {
        QSqlQuery querySymbols(db);
        if (filesToProcessDir.exists()){
            filesToProcessDir.removeRecursively();
            filesToProcessDir.mkpath(dir.toProcessDirPath);
        }
        if (!querySymbols.exec("SELECT RelPath FROM symbols")) {
            logMessage("First query failed:" + querySymbols.lastError().text(), mainWindow);
            return false;
        } else {
            while (querySymbols.next()) {
                QString name = querySymbols.value(0).toString();  // First column: name
                symbolsFileList.append(name);                   // Insert value into the QList
            }
        }
        QSet<QString> duplicates = findDuplicates(symbolsFileList);
        for (QString& file : symbolsFileList){
            QString src = dir.modelsDirPath + file;
            QString dst = dir.toProcessDirPath + file;
            QFile dstFile = QFile(dst);
            QString dstDirPath = QFileInfo(dstFile).path();
            QDir dstDir = QDir(dstDirPath);
            if( !dstDir.exists()){
                dstDir.mkpath(dstDirPath);
            }
            if(!QFile::copy(src, dst)){
                logMessage("Failed to copy file: " + src, mainWindow);
            }
        }
        QSqlQuery queryModels(db);
        if (!queryModels.exec("SELECT RelPath FROM models")) {
            logMessage("First query failed:" + queryModels.lastError().text(), mainWindow);
        } else {
            while (queryModels.next()) {
                QString name = queryModels.value(0).toString();  // First column: name
                modelFilesList.append(name);                   // Insert value into the QList
            }
        }
        for (QString& file : modelFilesList){
            QString src = dir.modelsDirPath + file;
            QString dst = dir.toProcessDirPath + file;
            QFile dstFile = QFile(dst);
            QString dstDirPath = QFileInfo(dstFile).path();
            QDir dstDir = QDir(dstDirPath);
            if( !dstDir.exists()){
                dstDir.mkpath(dstDirPath);
            }
            if (!QFile::copy(src, dst)){
                logMessage("Failed to copy file: " + src, mainWindow);
            }
        }
        QSqlQuery queryExamples(db);
        if (!queryExamples.exec("SELECT RelPath FROM examples")) {
            logMessage("First query failed:" + queryExamples.lastError().text(), mainWindow);
        } else {
            while (queryExamples.next()) {
                QString name = queryExamples.value(0).toString();  // First column: name
                examplesFilesList.append(name);                   // Insert value into the QList
            }
        }
        for (QString& file : examplesFilesList){
            QString src = dir.modelsDirPath + file;
            QString dst = dir.toProcessDirPath + file;
            QFile dstFile = QFile(dst);
            QString dstDirPath = QFileInfo(dstFile).path();
            QDir dstDir = QDir(dstDirPath);
            if( !dstDir.exists()){
                dstDir.mkpath(dstDirPath);
            }
            if (!QFile::copy(src, dst)){
                logMessage( src + " file was not copied.", mainWindow);
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
    DirStruct dir;
    DirPaths dirPaths;
    dir = dirPaths.buildDirPaths(mainWindow);
    QDir currentDir = QDir::current();
    // OBjective:     cmd = ".\\LTspice.exe -genweb update -local"
    QStringList arguments;
    arguments << "-genweb" << "update" << "-local";
    if (!QDir::setCurrent(dir.toSendFilesDirPath)) {
        qDebug() << "Failed to change directory to" << dir.toSendDirPath;
        return;
    }
    QProcess process;
    process.start(dir.LTspiceExeToSendPath, arguments);
    if (!process.waitForStarted()) {
        qDebug() << "Failed to start process:" << process.errorString();
        return;
    }
    process.waitForFinished();
    qDebug() << "Process output:" << process.readAllStandardOutput();
    qDebug() << "Process finished with exit code:" << process.exitCode();
    process.close();
    QDir::setCurrent(currentDir.absolutePath());
    QString srcPath = dir.toSendDirPath + "/" + "release.log";
    QString dstPath = dir.todayDirPath + "/" + "release.log";
    if (QFile(dstPath).exists()){
        QFile(dstPath).remove();
    }
    if(!QFile(srcPath).copy(dstPath)){
        qWarning() << srcPath << " could not be copied";
    }
    srcPath = dir.toSendFilesDirPath + "/" + "lib.zip";
    dstPath = dir.todayDirPath + "/" + "lib.zip";
    if (QFile(dstPath).exists()){
        QFile(dstPath).remove();
    }
    if(!QFile(srcPath).copy(dstPath)){
        qWarning() << srcPath << " could not be copied";
    }
    srcPath = dir.toSendFilesDirPath + "/" + "examples.zip";
    dstPath = dir.todayDirPath + "/" + "examples.zip";
    if (QFile(dstPath).exists()){
        QFile(dstPath).remove();
    }
    if (!QFile::copy(srcPath, dstPath)) {
        qWarning() << srcPath << " could not be copied";
    }
}


void Utilities::removeZipFromSharepoint(MainWindow *mainWindow) {
    DirStruct dir;
    DirPaths dirPaths;
    dir = dirPaths.buildDirPaths(mainWindow);
    QFile jsonFile(dir.jsonSharePointFilePath);
    if (!jsonFile.open(QIODevice::ReadOnly)) {
        logMessage("Could not open JSON file for reading:" + jsonFile.errorString(), mainWindow);
        return;
    }
    QJsonDocument doc = QJsonDocument::fromJson(jsonFile.readAll());
    jsonFile.close();
    if (!doc.isArray()) {
        logMessage("Invalid JSON format. Expected an array.", mainWindow);
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
                logMessage("Failed to remove:" + filePath, mainWindow);
            }
        }
        else {
            logMessage("File not found:" + filePath, mainWindow);
        }
    }
}


void Utilities::buildLTspiceJsonFile(MainWindow *mainWindow)
{
    DirStruct dir;
    DirPaths dirPaths;
    dir = dirPaths.buildDirPaths(mainWindow);
    QString LTspice17 = "";
    QString LTspiceMac = mainWindow->getUi()->lineEditMacVersion->text();
    QString LTspice24 = mainWindow->getUi()->lineEditWindowsVersion->text();
    QString update = dir.logDate;
    QString LTspiceJsonPath = dir.modelsDirPath + "LTspice.json";
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
    rootObject["Installation"] = dir.logDate;
    rootObject["LTspice_Mac"] = LTspiceMac;
    rootObject["Models"] = dir.logDate;
    QJsonDocument jsonDoc(rootObject);
    QFile file(LTspiceJsonPath);
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(jsonDoc.toJson());
        file.close();
    }
}

bool Utilities::runWebPush(MainWindow* mainWindow) {
    DirStruct dir;
    DirPaths dirPaths;
    dir = dirPaths.buildDirPaths(mainWindow);
    QString webPushExePath = dir.modelsDirPath + "WebPush.exe";
    QStringList arguments;
    QDir currentDir = QDir::current();
    // Change to the target directory
    if (!QDir::setCurrent(dir.modelsDirPath)) {
        qDebug() << "Failed to change directory to" << dir.modelsDirPath;
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



bool Utilities::updateSource(MainWindow *mainWindow) {
    Symbol symbol;
    Model model;
    Example example;
    Device device;
    DirStruct dir;
    DirPaths dirPaths;
    dir = dirPaths.buildDirPaths(mainWindow);
    QFile file(dir.jsonFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file" << dir.jsonFilePath;
        return false;
    }
    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(fileData);
    QJsonObject jsonObj = doc.object();
    QJsonArray devicesArray = jsonObj["devices"].toArray();
    for (const auto &deviceVal : devicesArray) {
        QJsonObject deviceObj = deviceVal.toObject();
        for (const QString &deviceName : deviceObj.keys()) {  // Use reference here
            QJsonObject subfieldsObj = deviceObj[deviceName].toObject();
            for (const QString &subfieldName : subfieldsObj.keys()) {  // Use reference here
                device.subfields.insert(subfieldName, subfieldsObj[subfieldName].toObject()["filename"].toString());
                if (subfieldName == "symbol"){
                    QString symbolFileName = dir.todayDirPath + "/" + subfieldsObj[subfieldName].toObject()["filename"].toString();
                    symbol.updateSourceSymbol(symbolFileName, mainWindow);
                }
                if (subfieldName == "model"){
                    QString modelFileName = dir.todayDirPath + "/" + subfieldsObj[subfieldName].toObject()["filename"].toString();
                    model.updateSourceModel(modelFileName, mainWindow);
                }
                if (subfieldName == "example"){
                    QString exampleFileName = dir.todayDirPath + "/" + subfieldsObj[subfieldName].toObject()["filename"].toString();
                    example.updateSourceExample(exampleFileName, mainWindow);
                }
            }
        }
    }
    return true;
}

void Utilities::removeOldModel(QString &filename, QSqlDatabase& db, MainWindow *mainWindow) {
    DirStruct dir;
    DirPaths dirPaths;
    dir = dirPaths.buildDirPaths(mainWindow);
    QList protectedLibs = {"LTC.lib",
                           "LTC1.lib",
                           "LTC2.lib",
                           "LTC3.lib",
                           "LTC4.lib",
                           "LTC5.lib",
                           "LTC6.lib",
                           "LTC7.lib",
                           "ADI.lib",
                           "ADI1.lib",
                           "ADI2.lib",
                           "ADG.lib",
                           "ADR.lib"};
    if (protectedLibs.contains(filename)) {
        qInfo() << "Library: " << filename << " should not be removed.\r";
        return;
    }
    // Remove from lib
    QString fileInLibPath = dir.subDirPath + filename;
    QFile fileInLib = QFile(fileInLibPath);
    if (fileInLib.exists())
        fileInLib.remove();
    // Remove from db
    removeRecord(filename, db);
    // Remove from Source
    QString fileInSourcePath = dir.sourceLibSubPath + filename;
    QFile fileInSource = QFile(fileInSourcePath);
    if (fileInSource.exists())
        fileInSource.remove();
    // Add to Remove.txt
    QString removePath = dir.modelsDirPath + "Remove.txt";
    QFile removeFile = QFile(removePath);
    if (!removeFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        logMessage("Remove.txt file: " + removePath + " could not be opened.\n", mainWindow);
        return;
    }
    QTextStream in(&removeFile);
    QString existingContent = in.readAll();
    removeFile.close();

    if (!removeFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        logMessage("Remove.txt file: " + removePath + " could not be opened.\n", mainWindow);
        return;
    }
    QTextStream out(&removeFile);
    QString lineToAdd = "\\lib\\sub\\" + filename;
    out << existingContent << lineToAdd << '\n';
    removeFile.close();
}

void Utilities::removeRecord(QString record, QSqlDatabase &db) {
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return;
    }

    QSqlQuery query;
    query.prepare("DELETE FROM models WHERE Name = :name");
    query.bindValue(":name", record);

    if (!query.exec()) {
        qDebug() << "Failed to delete record:" << query.lastError().text();
    }
    else {
        qDebug() << "Record with ID" << record << "deleted successfully!";
    }
}
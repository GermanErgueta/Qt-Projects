#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QRegularExpression>
#include <QVector>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMap>
#include <QList>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QTextStream>
//#include "ftpclient.h"
#include "utilities.h"
#include "dirpaths.h"
//#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->dateProcessing->setDate(QDate::currentDate());
    ui->lineEditWindowsVersion->setText("24.0.12");
    ui->lineEditMacVersion->setText("17.2.4");
}

Ui::MainWindow* MainWindow::getUi() const
{
    return ui;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_getAndZip_triggered()
{
    qInfo() << "Collecting Zip files.\r\n";
    DirStruct dir;
    DirPaths dirPaths;
    dir = dirPaths.buildDirPaths(this);


    QList<QString> listOfZipFiles;
    QList<QString> zipFilenamesToProcess;
    Utilities utilities;
    QString operatingSystem;
    if (QSysInfo::productType() == "windows") {
        operatingSystem = "Windows";
    } else if (QSysInfo::productType() == "osx") {
        operatingSystem = "macOS";
    } else {
        operatingSystem = "Unknown OS";
    }

    listOfZipFiles = Utilities::findZipFiles(this);
    if(!listOfZipFiles.empty()) {
        utilities.createSharePointJsonFile(listOfZipFiles, dir.jsonSharePointFilePath);
        zipFilenamesToProcess = Utilities::copyFiles(listOfZipFiles, this);
        utilities.createEmptyJsonFile(dir.jsonFilePath);
        utilities.unzipFiles(zipFilenamesToProcess, this);
        qInfo() << "Finished transferring Zip files.\r\n";
        QMainWindow::statusBar()->showMessage("Finished transferring Zip files.", 5000);
    }
    else {
        qWarning() << "No Zip files found.\r\n";
        QMainWindow::statusBar()->showMessage("No Zip files found.", 5000);
    }
    QString zipFilePath = dir.todayYearPath + dir.dateString + ".zip";
    QString comment = dir.dateString;
    utilities.compressDir(dir.todayDirPath, zipFilePath, comment);
    QMainWindow::statusBar()->showMessage("Finished creating the zip file.", 5000);

}


void MainWindow::on_check_triggered()
{
    DirStruct dir;
    DirPaths dirPaths;
    dir = dirPaths.buildDirPaths(this);
    
    qInfo() << "Started checking for devices.\r\n";

    QString operatingSystem;
    if (QSysInfo::productType() == "windows") {
        operatingSystem = "Windows";
    } else if (QSysInfo::productType() == "osx") {
        operatingSystem = "macOS";
    } else {
        operatingSystem = "Unknown OS";
    }

    Utilities utilities;
    QString removeTxtPath = dir.modelsDirPath + "Remove.txt";
    QString removeTxtBckPath = dir.bckDirPath + "Remove.txt" + "-" + dir.dateString;
    utilities.backupFile(removeTxtPath, this);
    // bring a copy of backup
    QFile removeFile = QFile(removeTxtPath);
    if (removeFile.exists()) {
        removeFile.remove();
        QFile::copy(removeTxtBckPath, removeTxtPath);
    }
    else {
        QFile::copy(removeTxtBckPath, removeTxtPath);
    }

    QFile dbFile = QFile(dir.dbPath);
    if (!dbFile.exists()) {
        qWarning() << "LTspice.db not available.\r";
        return;
    }
    QSqlDatabase  db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dir.modelsDirPath + "LTspice.db");
    if (!db.open()) {
        qWarning() << "Error: connection with database failed";
        return;
    } else {
        qInfo() << "Database: connection successful";
    }
    QFile jsonFile(dir.jsonFilePath);
    if(!jsonFile.exists()){
        qWarning() << "Error: Json file not available" << dir.jsonFilePath;
        return;
    }
    QVector<Device> devices;
    devices = Utilities::parseJsonFile(dir.jsonFilePath);
    bool success = Utilities::checkDevicesInJsonFile(dir.jsonFilePath, dir.todayDirPath, db, this);
    if (success) {
        qInfo() << "Checked all files in: " << dir.jsonFilePath;
    }
    qInfo() << "Finished checking for devices.\r\n";
    QMainWindow::statusBar()->showMessage("Finished checking for devices.", 5000);
}


void MainWindow::on_process_triggered()
{
    qInfo() << "Started processing devices.\r\n";
    Utilities utilities;
    DirStruct dir;
    DirPaths dirPaths;
    dir = dirPaths.buildDirPaths(this);

    QFile dbFile = QFile(dir.dbPath);
    if (!dbFile.exists()) {
        qWarning() << "LTspice.db not available.\r";
        return;
    }

    QSqlDatabase  db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dir.modelsDirPath + "/" "LTspice.db");
    if (!db.open()) {
        qWarning() << "Error: connection with database failed";
        return;
    } else {
        qInfo() << "Database: connection successful";
    }
    QFile jsonFile(dir.jsonFilePath);
    if(!jsonFile.exists()){
        qWarning() << "Error: Json file not available" << dir.jsonFilePath;
        return;
    }

    QString changeLogPath = dir.modelsDirPath + "ChangeLog.txt";
    QString changeLogBckPath = dir.bckDirPath + "ChangeLog.txt" + "-" + dir.dateString;
    utilities.backupFile(changeLogPath, this);
    // bring a copy of backup
    QFile changeLogFile = QFile(changeLogPath);
    if (changeLogFile.exists()) {
        changeLogFile.remove();
        QFile::copy(changeLogBckPath, changeLogPath);
    }
    else {
        QFile::copy(changeLogBckPath, changeLogPath);
    }

    QVector<Device> devices;
    devices = Utilities::parseJsonFile(dir.jsonFilePath);
    bool success = utilities.processDevicesInJsonFile(db, this);
    if (success) {
        qInfo() << "Processed all files in: " << dir.jsonFilePath;
    }
    qInfo() << "Finished processing devices.\r\n";
    QMainWindow::statusBar()->showMessage("Finished processing devices.");
}


void MainWindow::on_generateToProcess_triggered()
{
    Utilities utilities;
    DirStruct dir;
    DirPaths dirPaths;
    dir = dirPaths.buildDirPaths(this);

    QFile dbFile = QFile(dir.dbPath);
    if (!dbFile.exists()) {
        qWarning() << "LTspice.db not available.\r";
        return;
    }

    QSqlDatabase  db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dir.modelsDirPath + "/" "LTspice.db");
    if (!db.open()) {
        qWarning() << "Error: connection with database failed";
        return;
    } else {
        qInfo() << "Database: connection successful";
    }
    utilities.removeBadRecords(db);
    utilities.generateFilesToProcess(db, this);
}


void MainWindow::on_generateToSend_triggered()
{
    Utilities utilities;
    DirStruct dir;
    DirPaths dirPaths;
    dir = dirPaths.buildDirPaths(this);
    QDir toSendFilesDir = QDir(dir.toSendFilesDirPath);
    if (!toSendFilesDir.exists()){
        toSendFilesDir.mkpath(dir.toSendFilesDirPath);
    }
    QString libZipPath = dir.toSendFilesDirPath + "lib.zip";
    QFile libZipFile = QFile(libZipPath);
    if (libZipFile.exists()){
        libZipFile.remove();
    }
    QString examplesZipPath = dir.toSendFilesDirPath + "examples.zip";
    QFile examplesZipFile = QFile(examplesZipPath);
    if( examplesZipFile.exists()){
        examplesZipFile.remove();
    }
    QString comment = dir.dateString;

    QMainWindow::statusBar()->showMessage("Compressing lib.");
    utilities.compressDir(dir.toProcessLibPath, libZipPath, comment);
    QMainWindow::statusBar()->showMessage("Compressed lib.", 5000);
    QMainWindow::statusBar()->showMessage("Compressing examples.");
    utilities.compressDir(dir.toProcessExamplesPath, examplesZipPath, comment);
    QMainWindow::statusBar()->showMessage("Compressed examples.", 5000);


    QFile LTspiceFile = QFile(dir.toSendLTspiceExeFilePath);
    if (LTspiceFile.exists()){
        LTspiceFile.remove();
    }
    if (!QFile::copy(dir.LTspiceExeFilePath, dir.toSendLTspiceExeFilePath)){
        qWarning() << dir.LTspiceExeFilePath << " file was not copied.\r\n";
    }
    QMainWindow::statusBar()->showMessage("Copied LTspice.", 5000);
    QString changesLogPath = dir.modelsDirPath + "/" + "ChangeLog.txt";
    QString tsChangesLogPath = dir.toSendFilesDirPath + "/" + "ChangeLog.txt";
    QFile tsChangesLogFile = QFile(tsChangesLogPath);
    if ( tsChangesLogFile.exists()){
        tsChangesLogFile.remove();
    }
    if (!QFile::copy(changesLogPath, tsChangesLogPath)){
        qWarning() << changesLogPath << " file was not copied.\r\n";
    }
    QMainWindow::statusBar()->showMessage("Copied ChangeLog.txt.", 5000);
    QString removePath = dir.modelsDirPath + "/" + "Remove.txt";
    QString tsRemovePath = dir.toSendFilesDirPath + "/" + "Remove.txt";
    QFile tsRemoveFile = QFile(tsRemovePath);
    if ( tsRemoveFile.exists()){
        tsRemoveFile.remove();
    }
    if (!QFile::copy(removePath, tsRemovePath)){
        qWarning() << removePath << " file was not copied.\r\n";
    }
    QMainWindow::statusBar()->showMessage("Copied Remove.txt.", 5000);
    utilities.generateLTspiceUpdate(this);
    QMainWindow::statusBar()->showMessage("Removed files from SharePoint.", 5000);
    QMainWindow::statusBar()->showMessage("Files processed successfully.", 5000);

    utilities.buildLTspiceJsonFile(this);
}


void MainWindow::on_transferToAkamai_triggered()
{
    Utilities utilities;
    utilities.runWebPush(this);

    DirStruct dir;
    DirPaths dirPaths;
    dir = dirPaths.buildDirPaths(this);
    QString changesLogTxtFilename = "ChangeLog.txt.gz";
    QString examplesZipFilename = "examples.zip.gz";
    QString libZipFilename = "lib.zip.gz";
    QString removeTxtFilename = "Remove.txt.gz";
    QString releaseLogFilename = "release.log.gz";

    QList<QString> filesToUploadToSoftware;
    filesToUploadToSoftware.append(dir.LTspiceJsonForAkamai);

    QList<QString> filesToUploadToFieldsync_24;
    filesToUploadToFieldsync_24.append(changesLogTxtFilename);
    filesToUploadToFieldsync_24.append(examplesZipFilename);
    filesToUploadToFieldsync_24.append(libZipFilename);
    filesToUploadToFieldsync_24.append(removeTxtFilename);
    filesToUploadToFieldsync_24.append(releaseLogFilename);

    QString ftpUrlBaseTest = "ftp://Ltspice1.upload.akamai.com/669812/test";
    QString username = "LTS_aka";
    QString password = "MM$up1@f";
}


void MainWindow::on_exit_triggered()
{
    QCoreApplication::quit();
}


void MainWindow::on_actionRemoveZipFiles_triggered()
{
    Utilities utilities;
    utilities.removeZipFromSharepoint(this);
    QMainWindow::statusBar()->showMessage("Removed SharePoint files successfully.");

}


void MainWindow::on_actionUpdateSharePoint_triggered()
{
    Utilities utilities;
    utilities.updateSource(this);
}


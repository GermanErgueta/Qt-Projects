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
#include "ftpclient.h"
#include "utilities.h"
#include "logger.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->dateProcessing->setDate(QDate::currentDate());
    ui->lineEditWindowsVersion->setText("24.0.12");
    ui->lineEditMacVersion->setText("17.2.4");
    //Logger::initialize("LTspiceLibs.log");
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
    QDate today;
    today = ui->dateProcessing->date();

    QString dateString = today.toString("yyyy-MM-dd");
    QString yearString = today.toString("yyyy");
    QString LTspiceDevelopmentDirPath = ui->lineEditLTspiceDevelopment->text();
    QString modelsDirPath = LTspiceDevelopmentDirPath + "/" + "Models";
    QString newModelsDir = modelsDirPath + "/" + "NewModels";
    QString todayDirPath = newModelsDir + "/" + yearString + "/" + dateString;
    QString jsonFilename = todayDirPath + "/" + "devices.json";
    QString jsonSharePointFilePath = todayDirPath + "/" + "sharePoint.json";

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
        utilities.createSharePointJsonFile(listOfZipFiles, jsonSharePointFilePath);
        zipFilenamesToProcess = Utilities::copyFiles(listOfZipFiles, this);
        utilities.createEmptyJsonFile(jsonFilename);
        utilities.unzipFiles(zipFilenamesToProcess, this);
        qInfo() << "Finished transferring Zip files.\r\n";
        QMainWindow::statusBar()->showMessage("Finished transferring Zip files.", 5000);
    }
    else {
        qWarning() << "No Zip files found.\r\n";
        QMainWindow::statusBar()->showMessage("No Zip files found.", 5000);
    }
}


void MainWindow::on_check_triggered()
{
    qInfo() << "Started checking for devices.\r\n";

    QString operatingSystem;
    if (QSysInfo::productType() == "windows") {
        operatingSystem = "Windows";
    } else if (QSysInfo::productType() == "osx") {
        operatingSystem = "macOS";
    } else {
        operatingSystem = "Unknown OS";
    }

    QDate today;
    today = ui->dateProcessing->date();
    // QDate today = QDate::currentDate();
    QString dateString = today.toString("yyyy-MM-dd");
    QString yearString = today.toString("yyyy");
    QString LTspiceDevelopmentDirPath = ui->lineEditLTspiceDevelopment->text();
    QString modelsDirPath = LTspiceDevelopmentDirPath + "/" + "Models";
    QString newModelsDir = modelsDirPath + "/" + "NewModels";
    QString todayDirPath = newModelsDir + "/" + yearString + "/" + dateString;
    QString jsonFilename = todayDirPath + "/" + "devices.json";

    Utilities utilities;
    QSqlDatabase  db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(modelsDirPath + "/" "LTspice.db");
    if (!db.open()) {
        qWarning() << "Error: connection with database failed";
        return;
    } else {
        qInfo() << "Database: connection successful";
    }
    QFile jsonFile(jsonFilename);
    if(!jsonFile.exists()){
        qWarning() << "Error: Json file not available" << jsonFilename;
        return;
    }
    QVector<Device> devices;
    devices = Utilities::parseJsonFile(jsonFilename);
    bool success = Utilities::checkDevicesInJsonFile(jsonFilename, todayDirPath, db);
    if (success) {
        qInfo() << "Checked all files in: " << jsonFilename;
    }
    qInfo() << "Finished checking for devices.\r\n";
    QMainWindow::statusBar()->showMessage("Finished checking for devices.", 5000);
}


void MainWindow::on_process_triggered()
{
    qInfo() << "Started processing devices.\r\n";

    Utilities utilities;
    QDate today;
    today = ui->dateProcessing->date();
    QString srcDate = today.toString("yyyy-MM-dd");
    QString yearString = today.toString("yyyy");
    QString LTspiceDevelopmentDirPath = ui->lineEditLTspiceDevelopment->text();
    QString modelsDirPath = LTspiceDevelopmentDirPath + "/" + "Models";
    QString newModelsDir = modelsDirPath + "/" + "NewModels";
    QString todayDirPath = newModelsDir + "/" + yearString + "/" + srcDate;
    QString jsonFilePath = todayDirPath + "/" + "devices.json";

    QSqlDatabase  db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(modelsDirPath + "/" "LTspice.db");
    if (!db.open()) {
        qWarning() << "Error: connection with database failed";
        return;
    } else {
        qInfo() << "Database: connection successful";
    }
    QFile jsonFile(jsonFilePath);
    if(!jsonFile.exists()){
        qWarning() << "Error: Json file not available" << jsonFilePath;
        return;
    }
    utilities.backupChangeLogTxtFile(this);
    QVector<Device> devices;
    devices = Utilities::parseJsonFile(jsonFilePath);
    bool success = utilities.processDevicesInJsonFile(db, this);
    if (success) {
        qInfo() << "Processed all files in: " << jsonFilePath;
    }
    qInfo() << "Finished processing devices.\r\n";
    QMainWindow::statusBar()->showMessage("Finished processing devices.", 5000);
}


void MainWindow::on_generateToProcess_triggered()
{
    Utilities utilities;
    QSqlDatabase  db = QSqlDatabase::addDatabase("QSQLITE");
    QString LTspiceDevelopmentDirPath = ui->lineEditLTspiceDevelopment->text();
    QString modelsDirPath = LTspiceDevelopmentDirPath + "/" + "Models";
    db.setDatabaseName(modelsDirPath + "/" "LTspice.db");
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
    QString LTspiceDevelopmentDirPath = ui->lineEditLTspiceDevelopment->text();
    QString modelsDirPath = LTspiceDevelopmentDirPath + "/" + "Models";
    QString toProcessDirPath = modelsDirPath + "/" + "ToProcess";
    QString libPath = toProcessDirPath + "/" + "lib";
    QString examplesPath = toProcessDirPath + "/" + "examples";
    QString toSendDirPath = modelsDirPath + "/" + "ToSend";
    QString toSendFilesDirPath = toSendDirPath + "/" + "files";
    QDir toSendFilesDir = QDir(toSendFilesDirPath);
    if (!toSendFilesDir.exists()){
        toSendFilesDir.mkpath(toSendFilesDirPath);
    }
    QString libZipPath = toSendFilesDirPath + "/" + "lib.zip";
    QFile libZipFile = QFile(libZipPath);
    if (libZipFile.exists()){
        libZipFile.remove();
    }
    QString examplesZipPath = toSendFilesDirPath + "/" + "examples.zip";
    QFile examplesZipFile = QFile(examplesZipPath);
    if( examplesZipFile.exists()){
        examplesZipFile.remove();
    }
    QDate today;
    today = ui->dateProcessing->date();
    QString comment = today.toString("yyyy-MM-dd");

    QMainWindow::statusBar()->showMessage("Compressing lib.");
    utilities.compressDir(libPath, libZipPath, comment);
    QMainWindow::statusBar()->showMessage("Compressed lib.", 5000);
    QMainWindow::statusBar()->showMessage("Compressing examples.");
    utilities.compressDir(examplesPath, examplesZipPath, comment);
    QMainWindow::statusBar()->showMessage("Compressed examples.", 5000);


    QString LTspiceExeFilePath = modelsDirPath + "/" + "LTspice.exe";
    QString toSendLTspiceExeFilePath = toSendDirPath + "/" + "LTspice.exe";
    QFile LTspiceFile = QFile(toSendLTspiceExeFilePath);
    if (LTspiceFile.exists()){
        LTspiceFile.remove();
    }
    if (!QFile::copy(LTspiceExeFilePath, toSendLTspiceExeFilePath)){
        qWarning() << LTspiceExeFilePath << " file was not copied.\r\n";
    }
    QMainWindow::statusBar()->showMessage("Copied LTspice.", 5000);
    QString changesLogPath = modelsDirPath + "/" + "ChangeLog.txt";
    QString tsChangesLogPath = toSendFilesDirPath + "/" + "ChangeLog.txt";
    QFile tsChangesLogFile = QFile(tsChangesLogPath);
    if ( tsChangesLogFile.exists()){
        tsChangesLogFile.remove();
    }
    if (!QFile::copy(changesLogPath, tsChangesLogPath)){
        qWarning() << changesLogPath << " file was not copied.\r\n";
    }
    QMainWindow::statusBar()->showMessage("Copied ChangeLog.txt.", 5000);
    QString removePath = modelsDirPath + "/" + "Remove.txt";
    QString tsRemovePath = toSendFilesDirPath + "/" + "Remove.txt";
    QFile tsRemoveFile = QFile(tsRemovePath);
    if ( tsRemoveFile.exists()){
        tsRemoveFile.remove();
    }
    if (!QFile::copy(removePath, tsRemovePath)){
        qWarning() << removePath << " file was not copied.\r\n";
    }
    QMainWindow::statusBar()->showMessage("Copied Remove.txt.", 5000);
    utilities.generateLTspiceUpdate(this); //TODO
    // utilities.removeZipFromSharepoint(this);
    QMainWindow::statusBar()->showMessage("Removed files from SharePoint.", 5000);
    QMainWindow::statusBar()->showMessage("Files processed successfully.", 5000);

    utilities.buildLTspiceJsonFile(this);
}


void MainWindow::on_transferToAkamai_triggered()
{
    Utilities utilities;
    utilities.runWebPush(this);

    QDate today = this->getUi()->dateProcessing->date();
    QString logDate = today.toString("MM-dd-yy");
    QString LTspiceDevelopmentDirPath = this->getUi()->lineEditLTspiceDevelopment->text() + "/";
    QString modelsDirPath = LTspiceDevelopmentDirPath + "Models" + "/";
    QString toSendDirPath = modelsDirPath + "ToSend" + "/";
    QString toSendFilesDirPath = toSendDirPath + "files" + "/";
    QString ltspiceJsonFilename = "LTspice.json";
    QString ltspiceJsonFilePath = modelsDirPath + ltspiceJsonFilename;
    QString changesLogTxtFilename = "ChangeLog.txt.gz";
    QString examplesZipFilename = "examples.zip.gz";
    QString libZipFilename = "lib.zip.gz";
    QString removeTxtFilename = "Remove.txt.gz";
    QString releaseLogFilename = "release.log.gz";

    QList<QString> filesToUploadToSoftware;
    filesToUploadToSoftware.append(ltspiceJsonFilePath);

    QList<QString> filesToUploadToFieldsync_24;
    filesToUploadToFieldsync_24.append(changesLogTxtFilename);
    filesToUploadToFieldsync_24.append(examplesZipFilename);
    filesToUploadToFieldsync_24.append(libZipFilename);
    filesToUploadToFieldsync_24.append(removeTxtFilename);
    filesToUploadToFieldsync_24.append(releaseLogFilename);

    QString ftpUrlBaseTest = "ftp://Ltspice1.upload.akamai.com/669812/test";
    QString username = "LTS_aka";
    QString password = "MM$up1@f";

    boost::asio::io_context io_context;

    FTPClient client(io_context, "ftp.example.com", "username", "password");
    if (client.connect()) {
        client.uploadFile("local_file.txt", "remote_file.txt");
        client.downloadFile("remote_file.txt", "local_downloaded_file.txt");
    } else {
        std::cerr << "Failed to connect to the FTP server." << std::endl;
    }

}


void MainWindow::on_exit_triggered()
{
    Logger::shutdown();
    QCoreApplication::quit();
}


void MainWindow::on_actionRemoveZipFiles_triggered()
{
    Utilities utilities;
    utilities.removeZipFromSharepoint(this);
}


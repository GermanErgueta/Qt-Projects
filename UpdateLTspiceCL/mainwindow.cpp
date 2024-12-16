// mainwindow.cpp

#include "mainwindow.h"
#include "./ui_mainwindow.h"

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
#include "utilities.h"
#include "dirpaths.h"

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

void MainWindow::updateStatusBar(const QString &message, int timeout)
{
   QMainWindow::statusBar()->showMessage(message, timeout);
}

void MainWindow::on_getAndZip_triggered()
{
    Utilities utilities;
    Utilities::logMessage("Collecting Zip files.", this);
    DirPaths dirPaths;
    DirStruct dir = dirPaths.buildDirPaths(this);

    QString operatingSystem = QSysInfo::productType() == "windows" ? "Windows" :
                              QSysInfo::productType() == "osx" ? "macOS" : "Unknown OS";

    QList<QString> listOfZipFiles = Utilities::findZipFiles(this);
    if (!listOfZipFiles.empty()) {
        Utilities::createSharePointJsonFile(listOfZipFiles, dir.jsonSharePointFilePath, this);
        QList<QString> zipFilenamesToProcess = Utilities::copyFiles(listOfZipFiles, this);
        Utilities::createEmptyJsonFile(dir.jsonFilePath);
        Utilities::unzipFiles(zipFilenamesToProcess, this);
        Utilities::logMessage("Finished transferring Zip files.", this);
        updateStatusBar("Finished transferring Zip files.");
    } else {
        Utilities::logMessage("No Zip files found.", this, true);
        Utilities::logMessage("No Zip files found.", this, true);
        updateStatusBar("No Zip files found.");
    }

    QString zipFilePath = dir.todayYearPath + dir.dateString + ".zip";
    QString comment = dir.dateString;
    Utilities::compressDir(dir.todayDirPath, zipFilePath, comment);
    updateStatusBar("Finished creating the zip file.");
}

void MainWindow::on_actionRemoveZipFiles_triggered()
{
    Utilities utilities;
    Utilities::removeZipFromSharepoint(this);
    updateStatusBar("Removed SharePoint files successfully.");
}

void MainWindow::on_check_triggered()
{
    Utilities utilities;
    Utilities::logMessage("Started checking for devices.", this);
    DirPaths dirPaths;
    DirStruct dir = dirPaths.buildDirPaths(this);

    QString removeTxtPath = dir.modelsDirPath + "Remove.txt";
    QString removeTxtBckPath = dir.bckDirPath + "Remove.txt" + "-" + dir.dateString;
    Utilities::backupFile(removeTxtPath, this);

    QFile removeFile(removeTxtPath);
    if (removeFile.exists()) {
        removeFile.remove();
    }
    QFile::copy(removeTxtBckPath, removeTxtPath);

    QFile dbFile(dir.dbPath);
    if (!dbFile.exists()) {
        Utilities::logMessage("LTspice.db not available.", this, true);
        return;
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dir.modelsDirPath + "LTspice.db");
    if (!db.open()) {
        Utilities::logMessage("Error: connection with database failed", this, true);
        return;
    } else {
        Utilities::logMessage("Database: connection successful", this);
    }

    QFile jsonFile(dir.jsonFilePath);
    if (!jsonFile.exists()) {
        qWarning() << "Error: Json file not available" << dir.jsonFilePath;
        Utilities::logMessage("Error: Json file not available" + dir.jsonFilePath, this, true);
        return;
    }

    QVector<Device> devices = Utilities::parseJsonFile(dir.jsonFilePath);
    bool success = Utilities::checkDevicesInJsonFile(dir.jsonFilePath, dir.todayDirPath, db, this);
    if (success) {
        Utilities::logMessage("Checked all files in: " + dir.jsonFilePath, this);
    }
    Utilities::logMessage("Finished checking for devices.", this);
    updateStatusBar("Finished checking for devices.");
}

void MainWindow::on_process_triggered()
{
    Utilities utilities;
    Utilities::logMessage("Started processing devices.", this);
    DirPaths dirPaths;
    DirStruct dir = dirPaths.buildDirPaths(this);

    QFile dbFile(dir.dbPath);
    if (!dbFile.exists()) {
        Utilities::logMessage("LTspice.db not available.", this, true);
        return;
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dir.modelsDirPath + "/" "LTspice.db");
    if (!db.open()) {
        Utilities::logMessage("Error: connection with database failed", this, true);
        return;
    } else {
        Utilities::logMessage("Database: connection successful", this);
    }

    QFile jsonFile(dir.jsonFilePath);
    if (!jsonFile.exists()) {
        Utilities::logMessage("Error: Json file not available" + dir.jsonFilePath, this, true);
        return;
    }

    QString changeLogPath = dir.modelsDirPath + "ChangeLog.txt";
    QString changeLogBckPath = dir.bckDirPath + "ChangeLog.txt" + "-" + dir.dateString;
    Utilities::backupFile(changeLogPath, this);

    QFile changeLogFile(changeLogPath);
    if (changeLogFile.exists()) {
        changeLogFile.remove();
    }
    QFile::copy(changeLogBckPath, changeLogPath);

    QVector<Device> devices = Utilities::parseJsonFile(dir.jsonFilePath);
    bool success = Utilities::processDevicesInJsonFile(db, this);
    if (success) {
        Utilities::logMessage("Processed all files in: " + dir.jsonFilePath, this);
    }
    Utilities::logMessage("Finished processing devices.", this);
    updateStatusBar("Finished processing devices.");
}

void MainWindow::on_generateToProcess_triggered()
{
    Utilities utilities;
    DirPaths dirPaths;
    DirStruct dir = dirPaths.buildDirPaths(this);
    Utilities::logMessage("Generating ToProcess data", this);

    QFile dbFile(dir.dbPath);
    if (!dbFile.exists()) {
        Utilities::logMessage("LTspice.db not available.", this, true);
        return;
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dir.modelsDirPath + "/" "LTspice.db");
    if (!db.open()) {
        Utilities::logMessage("Error: connection with database failed", this, true);
        return;
    } else {
        Utilities::logMessage("Database: connection successful", this);
    }

    Utilities::removeBadRecords(db, this);
    Utilities::generateFilesToProcess(db, this);
    Utilities::logMessage("Finished generating ToProcess data", this);
}

void MainWindow::on_generateToSend_triggered()
{
    Utilities utilities;
    DirPaths dirPaths;
    DirStruct dir = dirPaths.buildDirPaths(this);
    Utilities::logMessage("Generating ToSend data", this);

    QDir toSendFilesDir(dir.toSendFilesDirPath);
    if (toSendFilesDir.exists()){
        toSendFilesDir.removeRecursively();
    }
    toSendFilesDir.mkpath(dir.toSendFilesDirPath);


    QString libZipPath = dir.toSendFilesDirPath + "lib.zip";
    QFile libZipFile(libZipPath);
    if (libZipFile.exists()) {
        libZipFile.remove();
    }

    QString examplesZipPath = dir.toSendFilesDirPath + "examples.zip";
    QFile examplesZipFile(examplesZipPath);
    if (examplesZipFile.exists()) {
        examplesZipFile.remove();
    }

    QString comment = dir.dateString;

    updateStatusBar("Compressing lib.");
    Utilities::compressDir(dir.toProcessLibPath, libZipPath, comment);
    updateStatusBar("Compressed lib.");

    updateStatusBar("Compressing examples.");
    Utilities::compressDir(dir.toProcessExamplesPath, examplesZipPath, comment);
    updateStatusBar("Compressed examples.");

    QFile LTspiceFile(dir.toSendLTspiceExeFilePath);
    if (LTspiceFile.exists()) {
        LTspiceFile.remove();
    }
    if (!QFile::copy(dir.LTspiceExeFilePath, dir.toSendLTspiceExeFilePath)) {
        Utilities::logMessage("Error: LTspice.exe file was not copied.", this, true);
    }
    updateStatusBar("Copied LTspice.");

    QString changesLogPath = dir.modelsDirPath + "/" + "ChangeLog.txt";
    QString tsChangesLogPath = dir.toSendFilesDirPath + "/" + "ChangeLog.txt";
    QFile tsChangesLogFile(tsChangesLogPath);
    if (tsChangesLogFile.exists()) {
        tsChangesLogFile.remove();
    }
    if (!QFile::copy(changesLogPath, tsChangesLogPath)) {
        Utilities::logMessage("Error: ChangeLog.txt file was not copied.", this, true);
    }
    updateStatusBar("Copied ChangeLog.txt.");

    QString removePath = dir.modelsDirPath + "/" + "Remove.txt";
    QString tsRemovePath = dir.toSendFilesDirPath + "/" + "Remove.txt";
    QFile tsRemoveFile(tsRemovePath);
    if (tsRemoveFile.exists()) {
        tsRemoveFile.remove();
    }
    if (!QFile::copy(removePath, tsRemovePath)) {
        Utilities::logMessage("Error: Remove.txt file was not copied.", this, true);
    }
    updateStatusBar("Copied Remove.txt.");

    Utilities::generateLTspiceUpdate(this);
    updateStatusBar("Removed files from SharePoint.");
    updateStatusBar("Files processed successfully.");

    Utilities::buildLTspiceJsonFile(this);
    Utilities::logMessage("Finished generating ToSend data", this);

}

void MainWindow::on_actionUpdateSharePoint_triggered()
{
    Utilities utilities;
    Utilities::logMessage("Starting to update data in SharePoint", this);
    Utilities::updateSource(this);
    Utilities::logMessage("Finished updating data in SharePoint", this);

}

void MainWindow::on_exit_triggered()
{
    QCoreApplication::quit();
}


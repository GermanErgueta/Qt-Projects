#ifndef UTILITIES_H
#define UTILITIES_H

#include "mainwindow.h"
#include <qglobal.h>
#include <QString>
#include <QStringList>
#include <QList>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QProcess>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QFile>
#include <QDir>
#include <QDirIterator>
#include <QDebug>
#include "CkZip.h"
#include <CkZipEntry.h>
#include "symbol.h"
#include "symbol.h"

struct Device {
    QString name;
    QMap<QString, QString> subfields; // Subfield name and filename
};

class Utilities
{
public:
    Utilities();
    static void createEmptyJsonFile(const QString& filename);
    static bool fileExists(const QString& filename);
    static bool unzipFile(const QString& zipFilePath, const QString& zipFileDirPath, MainWindow* mainWindow);
    static void unzipFiles(const QStringList &zipFilenames, MainWindow *mainWindow);
    static void addRecord(const QString &filename,
                          const QString &zipFilename,
                          const QString &deviceName,
                          const QString &symbolFilename,
                          const QString &modelFilename,
                          const QString &exampleFilename,
                          const QString &changesFilename,
                          QString &todayDirPath);
    static QList<QString> copyFiles(const QStringList &sourceFiles, MainWindow *mainWindow);
    static QList<QString> findZipFiles(MainWindow* mainWindow);
    static QVector<Device> parseJsonFile(const QString &filePath);
    static bool checkDevicesInJsonFile(const QString &filePath, const QString &localPath, QSqlDatabase &db, MainWindow *mainWindow);
    static bool processDevicesInJsonFile(QSqlDatabase &db, MainWindow *mainWindow);
    static SymbolStruct getInformationFromSymbolFile(const QString &symbolFilePath);
    static bool backupFile(const QString &sourcePath, MainWindow *mainWindow);
    static bool exBackupFile(const QString& sourcePath, MainWindow* mainWindow);
    static bool updateFile(const QString& sourcePath, const QString& dstPath, MainWindow* mainWindow);
    static bool generateNetlistFile(const QString &filePath, MainWindow *mainWindowstatic );
    static bool encryptFile(QString& filePath, MainWindow* mainWindow);
    static bool backupChangeLogTxtFile(MainWindow* mainWindow);
    static bool generateFilesToProcess(QSqlDatabase &db, MainWindow* mainWindow);
    static void compressDir(const QString &directoryPath, const QString &outputZipPath, const QString &comment);
    static void generateLTspiceUpdate(MainWindow* mainWindow);
    static void removeZipFromSharepoint(MainWindow* mainWindow);
    static void createSharePointJsonFile(const QList<QString>& fileList, const QString& jsonFilePath, MainWindow* mainWindow);
    static void buildLTspiceJsonFile(MainWindow *mainWindow);
    static bool runWebPush(MainWindow* mainWindowstatic );
    static QSet<QString> findDuplicates(const QList<QString>& list);
    static void removeBadRecords(QSqlDatabase& db, MainWindow* mainWindow);
    static bool updateSource(MainWindow *mainWindow);
    static void removeOldModel(QString &filename, QSqlDatabase& db, MainWindow *mainWindow);
    static void removeRecord(QString record, QSqlDatabase& db);
    static void logMessage(const QString& message, MainWindow *mainWindow, bool isWarning = false);
};


#endif // UTILITIES_H

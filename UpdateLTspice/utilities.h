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
    static bool unzipFile(const QString &zipFilePath, const QString &zipFileDirPath);
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
    bool processDevicesInJsonFile(QSqlDatabase &db, MainWindow *mainWindow);
    static SymbolStruct getInformationFromSymbolFile(const QString &symbolFilePath);
    bool backupFile(const QString &sourcePath, MainWindow *mainWindow);
    bool exBackupFile(const QString& sourcePath, MainWindow* mainWindow);
    bool updateFile(const QString& sourcePath, const QString& dstPath);
    bool generateNetlistFile(const QString &filePath, MainWindow *mainWindow);
    bool encryptFile(QString& filePath, MainWindow* mainWindow);
    bool backupChangeLogTxtFile(MainWindow* mainWindow);
    bool generateFilesToProcess(QSqlDatabase &db, MainWindow* mainWindow);
    static void compressDir(const QString &directoryPath, const QString &outputZipPath, const QString &comment);
    void generateLTspiceUpdate(MainWindow* mainWindow);
    void removeZipFromSharepoint(MainWindow* mainWindow);
    static void createSharePointJsonFile(const QList<QString>& list, const QString& filePath);
    static void buildLTspiceJsonFile(MainWindow *mainWindow);
    bool runWebPush(MainWindow* mainWindow);
    QSet<QString> findDuplicates(const QList<QString>& list);
    void removeBadRecords(QSqlDatabase& db);
    bool updateSource(MainWindow *mainWindow);
    void removeOldModel(QString &filename, MainWindow *mainWindow);
};

#endif // UTILITIES_H

#ifndef DIRPATHS_H
#define DIRPATHS_H

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

struct DirStruct
{
    QDate today;
    QString dateString;
    QString logDate;
    QString yearString;
    QString homeDirPath;
    QString LTspiceDevelopmentDirPath;
    QString modelsDirPath;
    QString ecsDirPath;
    QString newModelsDir;
    QString todayYearPath;
    QString todayDirPath;
    QString sharePointPath;
    QString jsonFilePath;
    QString jsonSharePointFilePath;
    QString toProcessDirPath;
    QString toProcessLibPath;
    QString toProcessExamplesPath;
    QString toSendDirPath;
    QString toSendLibDirPath;
    QString toSendExamplesPath;
    QString toSendFilesDirPath;
    QString LTspiceExeFilePath;
    QString encryptExeFilePath;
    QString toSendLTspiceExeFilePath;
    QString bckDirPath;
    QString yearBckDirPath;
    QString sourceDirPath;
    QString sourceLibDirPath;
    QString sourceLibSymPath;
    QString sourceLibSubPath;
    QString sourceLibECSPath;
    QString sourceExamplesLibPath;
    QString sourceApplicationsPath;
    QString libDirPath;
    QString subDirPath;
    QString symDirPath;
    QString examplesDirPath;
    QString applicationsDirPath;
    QString applicationsBckDirPath;
    QString LTspiceJsonForAkamai;
    QString changeLogPath;
    QString changeLogBckPath;
    QString LTspiceExeToSendPath;
    QString dbPath;
};

class DirPaths
{
public:
    DirPaths();
    DirStruct buildDirPaths(MainWindow* mainWindow);
};

#endif // DIRPATHS_H
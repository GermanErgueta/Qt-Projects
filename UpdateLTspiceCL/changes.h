#ifndef CHANGES_H
#define CHANGES_H

#include <qglobal.h>
#include <QString>
#include <QString>
#include <QVector>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "mainwindow.h"
#include "utilities.h"
#include "dirpaths.h"

struct ChangesStruct
{
    QString date;
    QString devName;
    QString text;
};

class Changes
{
public:
    Changes();
    bool checkChanges(const QString& filePath, MainWindow* mainWindow);
    bool processChanges(const QString& filePath, MainWindow* mainWindow);
    bool readFirstLine(const QString& filePath, const QString& logDate, QString& lineToPrepend, MainWindow* mainWindow);
    bool readFileContent(const QString& filePath, QString& content, MainWindow* mainWindow);
    bool prependToFile(const QString& filePath, const QString& lineToPrepend, const QString& existingContent, MainWindow* mainWindow);
};

#endif // CHANGES_H

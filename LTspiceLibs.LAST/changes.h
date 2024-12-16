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
    ChangesStruct checkChanges(const QString &filePath, QSqlDatabase &db);
    ChangesStruct processChanges(const QString &filePath, QSqlDatabase &db, MainWindow *mainWindow);
};

#endif // CHANGES_H

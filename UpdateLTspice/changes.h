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
    static bool checkChanges(const QString &filePath);
    static bool processChanges(const QString &filePath, MainWindow *mainWindow);
};

#endif // CHANGES_H

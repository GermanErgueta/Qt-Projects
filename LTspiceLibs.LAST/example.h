#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <qglobal.h>
#include <QString>
#include <QString>
#include <QVector>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "mainwindow.h"
#include "utilities.h"

struct ExampleStruct
{
    QString date;
    QString name;
    QString relPath;
};

class Example
{
public:
    Example();
    ExampleStruct checkExample(const QString &filePath, QSqlDatabase &db);
    ExampleStruct processExample(const QString& filePath, QSqlDatabase& db, MainWindow* mainWindow);
    bool insertOrUpdate(ExampleStruct& example, QSqlDatabase& db, MainWindow* mainWindow);
};

#endif // EXAMPLE_H

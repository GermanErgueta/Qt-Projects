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
#include "dirpaths.h"

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
    bool checkExample(const QString& filePath, QSqlDatabase& db, MainWindow* mainWindow);
    bool insertOrUpdate(ExampleStruct& newDevice, QSqlDatabase& db, MainWindow* mainWindow);
    bool updateExampleInDB(ExampleStruct& newDevice, const QByteArray& binaryData, QSqlDatabase& db, MainWindow* mainWindow);
    bool insertExampleInDB(ExampleStruct& newDevice, const QByteArray& binaryData, QSqlDatabase& db, MainWindow* mainWindow);
    bool processExample(const QString& filePath, QSqlDatabase& db, MainWindow* mainWindow);
    bool updateSourceExample(const QString& filePath, MainWindow* mainWindow);
};

#endif // EXAMPLE_H

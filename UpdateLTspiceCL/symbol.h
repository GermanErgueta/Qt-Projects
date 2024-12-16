#ifndef SYMBOL_H
#define SYMBOL_H

#include <qglobal.h>
#include <QString>
#include <QVector>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "mainwindow.h"
#include "dirpaths.h"

struct SymbolStruct
{
    QString name;
    QString encryption;
    QString category;
    QString fileName;
    QString newOrUpdate;
    QString todayDirPath;
    QString relPath;
    QString spiceModel;
    QString modelFile;
    QString value;
    QString value2;
    QString symbolType;
    QString prefix;
};

class Symbol
{
public:
    Symbol();
    SymbolStruct extractParametersFromAsyFile(const QString& filePath, MainWindow* mainWindow);
    QString extractAttribute(const QString& data, const QString& attribute);
    SymbolStruct getNewSymbolData(const QString& filePath);
    bool checkSymbol(const QString& filePath, QSqlDatabase& db, MainWindow* mainWindow);
    bool insertOrUpdateSymbolInDB(SymbolStruct& newDevice, QSqlDatabase& db, MainWindow* mainWindow);
    bool processSymbol(const QString& filePath, QSqlDatabase& db, MainWindow* mainWindow);
    bool updateSourceSymbol(const QString& filePath, MainWindow* mainWindow);
    bool fetchDeviceList(QSqlDatabase& db, const QString& tableName, QList<QString>& deviceList, MainWindow* mainWindow);
    bool updateSymbol(SymbolStruct& newDevice, QSqlDatabase& db, MainWindow* mainWindow);
    bool updateSymbolInDB(SymbolStruct& newDevice, const QByteArray& binaryData, QSqlDatabase& db, const DirStruct& dir, MainWindow* mainWindow);
    bool insertSymbolInDB(SymbolStruct& newDevice, const QByteArray& binaryData, QSqlDatabase& db, const DirStruct& dir, MainWindow* mainWindow);
};

#endif // SYMBOL_H


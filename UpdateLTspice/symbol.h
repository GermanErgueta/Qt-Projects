#ifndef SYMBOL_H
#define SYMBOL_H

#include <qglobal.h>
#include <QString>
#include <QVector>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "mainwindow.h"

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
};

class Symbol
{
public:
    Symbol();
    static SymbolStruct extractParametersFromAsyFile(const QString &filePath );
    static bool checkSymbol(const QString &filePath, QSqlDatabase &db, MainWindow *mainWindow);
    static bool processSymbol(const QString &filePath, QSqlDatabase &db, MainWindow *mainWindow);
    bool insertOrUpdateSymbolInDB(SymbolStruct& newDevice, QSqlDatabase& db, MainWindow *mainWindow);
    bool updateSourceSymbol(const QString& filePath, MainWindow* mainWindow);
    static SymbolStruct getNewSymbolData(const QString &filePath);
};

#endif // SYMBOL_H

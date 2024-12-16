#ifndef MODEL_H
#define MODEL_H


#include <qglobal.h>
#include <QString>
#include <QVector>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "mainwindow.h"
#include "utilities.h"

struct ModelStruct
{
    QString encrypt;
    QString date;
    QString name;
    QString relPath;
};

class Model
{
public:
    Model();
    static bool checkModel(const QString &filePath,QSqlDatabase &db);
    static bool processModel(const QString &filePath, QSqlDatabase &db, MainWindow *mainWindow);
    bool insertOrUpdate(ModelStruct& model, QSqlDatabase& db, MainWindow* mainWindow);
    bool updateSourceModel(const QString& filePath, MainWindow* mainWindow);
};

#endif // MODEL_H

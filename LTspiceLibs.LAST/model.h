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
    ModelStruct checkModel(const QString &filePath,QSqlDatabase &db);
    ModelStruct processModel(const QString &filePath, QSqlDatabase &db, MainWindow *mainWindow);
    bool insertOrUpdate(ModelStruct& model, QSqlDatabase& db, MainWindow* mainWindow);
};

#endif // MODEL_H

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
    bool checkModel(const QString& filePath, QSqlDatabase& db, MainWindow* mainWindow);
    bool fetchModelList(QSqlDatabase& db, QList<QString>& modelList, MainWindow* mainWindow);
    bool insertModel(ModelStruct& newDevice, const QByteArray& binaryData, QSqlDatabase& db, MainWindow* mainWindow);
    bool insertOrUpdate(ModelStruct& newDevice, QSqlDatabase& db, MainWindow* mainWindow);
    bool processModel(const QString& modFilePath, QSqlDatabase& db, MainWindow* mainWindow);
    bool updateSourceModel(const QString& filePath, MainWindow* mainWindow);
    bool updateModel(ModelStruct& newDevice, const QByteArray& binaryData, QSqlDatabase& db, MainWindow* mainWindow);
};

#endif // MODEL_H

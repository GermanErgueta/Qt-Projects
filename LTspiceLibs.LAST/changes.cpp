#include "changes.h"
#include <QString>
#include <QVector>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMap>
#include <QList>
#include <QFile>
#include <QDir>

Changes::Changes() {}


ChangesStruct Changes::checkChanges(const QString &filePath, QSqlDatabase &db){
    ChangesStruct changes;
    QFile inputFile(filePath);
    if (!inputFile.exists()){
        qWarning() << "Changes file: " << filePath << " not available.\n";
    }
    return changes;
}

ChangesStruct Changes::processChanges(const QString &filePath, QSqlDatabase &db, MainWindow *mainWindow){
    ChangesStruct changes;
    Utilities utilities;
    QString srcDate = mainWindow->getUi()->dateProcessing->date().toString("yyyy-MM-dd");
    QString logDate = mainWindow->getUi()->dateProcessing->date().toString("MM/dd/yy");
    QString LTspiceDevelopmentDirPath = mainWindow->getUi()->lineEditLTspiceDevelopment->text();
    QString modelsDirPath = LTspiceDevelopmentDirPath + "/" + "Models";
    QString mainChangesLogTxtFilePath = modelsDirPath + "/" + "ChangeLog.txt";
    QFile mainChangesLogTxtFile(mainChangesLogTxtFilePath);
    QFile inputFile(filePath);
    QList<QString> parts;
    parts = filePath.split("/");
    QString deviceName = parts[parts.size() - 2];
    QString lineToPrepend;
    if (!inputFile.exists()) {
        qWarning() << "Changes file: " << filePath << " not available.\n";
        return changes;
    }
    else {
        if (!inputFile.open(QIODevice::ReadOnly)) {
            qWarning() << "Changes file: " << filePath << " could not be opened.\n";
            return changes;
        }
        QTextStream in(&inputFile);
        lineToPrepend = logDate + " " + deviceName + " " + in.readLine();
    }
    if (!mainChangesLogTxtFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Could not open backup ChangeLog.txt file for reading.");
    }
    else {
        QTextStream in(&mainChangesLogTxtFile);
        QString content = in.readAll();
        mainChangesLogTxtFile.close();

        if (!mainChangesLogTxtFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qWarning("Could not open file for writing.");
            return changes;
        }
        else {
            QTextStream out(&mainChangesLogTxtFile);
            out << lineToPrepend << '\n' << content;
            mainChangesLogTxtFile.close();
        }
    }
    return changes;
}

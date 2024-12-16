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
#include "dirpaths.h"

Changes::Changes() {}


bool Changes::checkChanges(const QString &filePath){
    ChangesStruct changes;
    QFile inputFile(filePath);
    if (!inputFile.exists()){
        qWarning() << "Changes file: " << filePath << " not available.\n";
        return false;
    }
    return true;
}

bool Changes::processChanges(const QString &filePath, MainWindow *mainWindow){
    ChangesStruct changes;
    Utilities utilities;
    DirStruct dir;
    DirPaths dirPaths;
    dir = dirPaths.buildDirPaths(mainWindow);

    QFile changeLogFile(dir.changeLogPath);
    QFile inputFile(filePath);
    QList<QString> parts;
    parts = filePath.split("/");
    QString deviceName = parts[parts.size() - 2];
    QString lineToPrepend;
    if (!inputFile.exists()) {
        qWarning() << "Changes file: " << filePath << " not available.\n";
        return false;
    }
    if (!inputFile.open(QIODevice::ReadOnly)) {
        qWarning() << "Changes file: " << filePath << " could not be opened.\n";
        return false;
    }
    QTextStream inDevice(&inputFile);
    lineToPrepend = dir.logDate + " " + deviceName + " " + inDevice.readLine();
    inputFile.close();

    if (!changeLogFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Changes backup file: " << dir.changeLogPath << " could not be opened.\n";
        return false;
    }
    QTextStream in(&changeLogFile);
    QString existingContent = in.readAll();
    changeLogFile.close();

    if (!changeLogFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Changes log file: " << dir.changeLogPath << " could not be opened.\n";
        return false;
    }
    QTextStream out(&changeLogFile);
    out << lineToPrepend << '\n' << existingContent;
    changeLogFile.close();
    return true;
}

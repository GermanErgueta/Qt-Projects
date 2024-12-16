// changes.cpp

#include "changes.h"
#include "dirpaths.h"
#include "utilities.h" // Assuming Utilities is defined in this header

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
#include <QTextStream>

Changes::Changes() {}

bool Changes::checkChanges(const QString &filePath, MainWindow *mainWindow) {
    Utilities utilities;
    QFile inputFile(filePath);
    if (!inputFile.exists()) {
        Utilities::logMessage("Changes file: " + filePath + " not available.\n", mainWindow);
        return false;
    }
    return true;
}

bool Changes::processChanges(const QString &filePath, MainWindow *mainWindow) {
    DirPaths dirPaths;
    DirStruct dir = dirPaths.buildDirPaths(mainWindow);

    QString lineToPrepend;
    if (!readFirstLine(filePath, dir.logDate, lineToPrepend, mainWindow)) {
        return false;
    }

    QString existingContent;
    if (!readFileContent(dir.changeLogPath, existingContent, mainWindow)) {
        return false;
    }

    if (!prependToFile(dir.changeLogPath, lineToPrepend, existingContent, mainWindow)) {
        return false;
    }

    return true;
}

bool Changes::readFirstLine(const QString &filePath, const QString &logDate, QString &lineToPrepend, MainWindow *mainWindow) {
    QFile inputFile(filePath);
    Utilities utilities;
    if (!inputFile.exists()) {
        Utilities::logMessage("Changes file: " + filePath + " not available.", mainWindow);
        return false;
    }
    if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        Utilities::logMessage("Changes file: " + filePath + " could not be opened.", mainWindow);
        return false;
    }

    QTextStream inDevice(&inputFile);
    QString deviceName = QFileInfo(filePath).dir().dirName();
    lineToPrepend = logDate + " " + deviceName + " " + inDevice.readLine();
    inputFile.close();

    return true;
}

bool Changes::readFileContent(const QString &filePath, QString &content, MainWindow *mainWindow) {
    QFile file(filePath);
    Utilities utilities;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        Utilities::logMessage("File: " + filePath + " could not be opened.", mainWindow);
        return false;
    }

    QTextStream in(&file);
    content = in.readAll();
    file.close();

    return true;
}

bool Changes::prependToFile(const QString &filePath, const QString &lineToPrepend, const QString &existingContent, MainWindow *mainWindow) {
    QFile file(filePath);
    Utilities utilities;
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        Utilities::logMessage("File: " + filePath + " could not be opened.", mainWindow);
        return false;
    }

    QTextStream out(&file);
    out << lineToPrepend << '\n' << existingContent;
    file.close();

    return true;
}


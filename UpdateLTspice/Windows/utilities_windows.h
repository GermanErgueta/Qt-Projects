#ifndef UTILITIES_WINDOWS_H
#define UTILITIES_WINDOWS_H

#include <qglobal.h>

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QDir>
#include <CkZip.h>
#include <CkZipEntry.h>

class Utilities_windows
{
public:
    Utilities_windows();
    bool unzipFile(const QString &zipFilePath, const QString &destinationPath);
    void zipFolder(const QString &folderPath);
};

#endif // UTILITIES_WINDOWS_H
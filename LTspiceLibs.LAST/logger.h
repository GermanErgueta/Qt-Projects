#ifndef LOGGER_H
#define LOGGER_H

#include <QFile>
#include <QTextStream>
#include <QMutex>
#include <QDateTime>
#include <QDebug>

class Logger
{
public:
    Logger();
    static void initialize(const QString &filePath = "log.txt"); // Initialize logger with a specified file path
    static void shutdown();  // Shutdown logger and close file
private:
    static void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);
    static QFile logFile;
    static QTextStream logStream;
    static QMutex mutex;
};

#endif // LOGGER_H

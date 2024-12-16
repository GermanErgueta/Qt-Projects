#include "logger.h"

QFile Logger::logFile;
QTextStream Logger::logStream;
QMutex Logger::mutex;

Logger::Logger() {}

void Logger::initialize(const QString &filePath) {
    if (logFile.isOpen())
        return; // Prevent reinitialization if already open

    logFile.setFileName(filePath);
    if (logFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        logStream.setDevice(&logFile);
        logStream << "Logging started: " << QDateTime::currentDateTime().toString() << Qt::endl;
        qInstallMessageHandler(Logger::messageHandler);  // Install the custom message handler
    }
}

void Logger::shutdown() {
    if (logFile.isOpen()) {
        logStream << "Logging ended: " << QDateTime::currentDateTime().toString() << Qt::endl;
        logFile.close();
        qInstallMessageHandler(nullptr);  // Reset to default handler
    }
}

void Logger::messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    QMutexLocker locker(&mutex);  // Lock mutex to protect logStream in multi-threaded scenarios

    switch (type) {
    case QtDebugMsg:
        logStream << "[DEBUG] ";
        break;
    case QtWarningMsg:
        logStream << "[WARNING] ";
        break;
    case QtCriticalMsg:
        logStream << "[CRITICAL] ";
        break;
    case QtFatalMsg:
        logStream << "[FATAL] ";
        break;
    case QtInfoMsg:
        break;
    }

    logStream << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") << ": " << msg << Qt::endl;
    logStream.flush();  // Ensure message is immediately written to file

    if (type == QtFatalMsg)
        abort();  // End application on fatal error
}

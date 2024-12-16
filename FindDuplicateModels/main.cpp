#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QMap>
#include <QDebug>

void findDuplicateModels(const QString &filePath) {
    QFile file(filePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCritical() << "Cannot open file:" << filePath;
        return;
    }

    QTextStream in(&file);
    QMap<QString, int> modelCounts;

    // Use a static QRegularExpression object for efficiency
    static const QRegularExpression regex("^\\.model\\s+(\\S+)");

    // Read file line by line
    while (!in.atEnd()) {
        QString line = in.readLine();
        QRegularExpressionMatch match = regex.match(line);

        // If line starts with .model, extract the model name
        if (match.hasMatch()) {
            QString modelName = match.captured(1); // Capture the model name
            modelCounts[modelName]++; // Increment count of the model
        }
    }

    // Display models used more than once
    bool hasDuplicates = false;
    for (auto it = modelCounts.cbegin(); it != modelCounts.cend(); ++it) {
        if (it.value() > 1) {
            hasDuplicates = true;
            qDebug() << "Model" << it.key() << "is used" << it.value() << "times";
        }
    }

    if (!hasDuplicates) {
        qDebug() << "No duplicate models found.";
    }

    file.close();
}

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);

    // Retrieve the command-line arguments
    QStringList arguments = QCoreApplication::arguments();

    // Ensure that a file path is passed
    if (arguments.size() < 2) {
        qCritical() << "Usage: " << arguments.at(0) << " <file_path>";
        return -1;
    }

    // The file path is the second argument (first is the program name)
    QString filePath = arguments.at(1);

    // Call the function to find duplicate models
    findDuplicateModels(filePath);

    return a.exec();
}



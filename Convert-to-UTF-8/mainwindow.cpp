#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QDirIterator>
#include <QFile>
#include <QTextStream>
#include <QByteArray>
#include <QString>
#include <QDebug>
#include <QStringDecoder>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Convert to UTF-8");  // Replace with your desired title
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool convertFileToUtf8(const QString &filePath, const QString &outputPath) {
    QFile inputFile(filePath);

    // Try to open the file for reading
    if (!inputFile.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open file:" << filePath;
        return false;
    }

    // Read the file content as raw bytes
    QByteArray fileData = inputFile.readAll();
    inputFile.close();

    QString stringData;
    QStringDecoder decoder(QStringDecoder::Utf8);

    // Decode the file content using UTF-8
    stringData = decoder.decode(fileData);

    // If UTF-8 decoding fails, fall back to system encoding or Latin-1
    if (decoder.hasError()) {
        qWarning() << "Failed to decode as UTF-8. Falling back to Latin-1.";

        // Fall back to Latin-1 encoding
        QStringDecoder fallbackDecoder(QStringDecoder::Latin1);
        stringData = fallbackDecoder.decode(fileData);

        if (fallbackDecoder.hasError()) {
            qWarning() << "Failed to decode as Latin1. Falling back to Windows-1252.";

            // Fall back to Latin-1 encoding
            QStringDecoder windows1252Decoder(QStringDecoder::System);
            stringData = windows1252Decoder.decode(fileData);

            // Check if Windows-1252 decoding also failed
            if (windows1252Decoder.hasError()) {
                qWarning() << "Failed to decode as Windows-1252 (CP-1252) as well.";
                return false; // Stop if both decodings fail
            }
        }
    }


    // Normalize the line endings: Convert CR LF (\r\n) to LF (\n)
    stringData.replace("\r\n", "\n");

    // Open the output file for writing (UTF-8 is the default in Qt 6)
    QFile outputFile(outputPath);
    if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Failed to open output file:" << outputPath;
        return false;
    }

    // Write the content to the output file
    QTextStream out(&outputFile);


    // Optionally write BOM for UTF-8 (to help some applications recognize the encoding)
    // outputFile.write("\xEF\xBB\xBF"); // Write BOM for UTF-8

    // Write the string data, converting any line endings as necessary
    out << stringData;
    outputFile.close();

    qDebug() << "File successfully converted to UTF-8:" << outputPath;
    return true;
}


void traverseDirectory(const QString &inputDirPath, const QString &outputDirPath, const QStringList &fileExtensions) {
    // Use QDirIterator to traverse the directory tree recursively with specific file extensions
    QDirIterator it(inputDirPath, fileExtensions, QDir::Files, QDirIterator::Subdirectories);

    while (it.hasNext()) {
        QString filePath = it.next();
        QFileInfo fileInfo(filePath);

        // Create corresponding output file path
        QString relativePath = fileInfo.absoluteFilePath().mid(inputDirPath.length() + 1);
        QString outputFilePath = QDir(outputDirPath).filePath(relativePath);

        // Ensure the output directory exists
        QDir outputDir = QFileInfo(outputFilePath).dir();
        if (!outputDir.exists()) {
            QDir().mkpath(outputDir.path());
        }

        // Convert the file to UTF-8
        if (!convertFileToUtf8(filePath, outputFilePath)) {
            qWarning() << "Failed to convert file:" << filePath;
        }
    }
}

void MainWindow::on_inputDirButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Select Directory 1"));
    if (!dir.isEmpty()) {
        inputDirPath = dir;
        ui->lineEditDir1->setText(dir);
    }
}


void MainWindow::on_outputDirButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Select Directory 2"));
    if (!dir.isEmpty()) {
        outputDirPath = dir;
        ui->lineEditDir2->setText(dir);
    }
}


void MainWindow::on_convertButton_clicked()
{
    if (inputDirPath.isEmpty() || outputDirPath.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select both input and output directories.");
        return;
    }

    // Set the list of file extensions to filter (e.g., .txt, .log)
    QStringList fileExtensions;
    fileExtensions << "*.asy" << "*.lib" << "*.asc";  // Add the extensions you want to filter by

    traverseDirectory(inputDirPath, outputDirPath, fileExtensions);
    QMessageBox::information(this, "Success", "Files converted to UTF-8 successfully.");

}


#include "utilities_windows.h"

Utilities_windows::Utilities_windows() {}

bool Utilities_windows::unzipFile(const QString &zipFilePath, const QString &destDir) {
    // Ensure the destination directory exists
    QFile file(zipFilePath);
    QDir dir(destDir);
    if (!dir.exists()) {
        // Create the directory if it doesn't exist
        dir.mkpath(destDir);
    }

    // Initialize the Chilkat ZIP object
    CkZip zip;
    if (!zip.OpenZip(zipFilePath.toStdString().c_str())) {
        qWarning() << "Failed to open zip file: " << "\r\n";
        return false;
    }

    // Start iterating over the entries in the ZIP file
    CkZipEntry *entry = zip.FirstEntry();
    if (!entry) {
        qWarning() << "No entries found in the zip file." << "\r\n";
        return false;
    }

    while (entry != nullptr) {
        // Get the filename of the current entry
        std::string entryFileName = entry->fileName();
        std::string fullDestPath = destDir.toStdString() + "/" + entryFileName;

        // Extract the file to the destination directory
        if (!entry->Extract(destDir.toStdString().c_str())) {
            qWarning() << "Failed to extract file: " << entryFileName << "\r\n";
            return false;
        } else {
            qDebug() << "Extracted: " << entryFileName << " to " << fullDestPath << "\r\n";
        }

        // Move to the next entry in the ZIP file
        entry = entry->NextEntry();
    }

    return true;
}

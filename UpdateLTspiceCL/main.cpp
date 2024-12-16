// main.cpp

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    // Create the application object
    QApplication app(argc, argv);

    // Check if the application object is created successfully
    if (!QApplication::instance()) {
        qCritical() << "Failed to create QApplication instance.";
        return -1;
    }

    // Create and show the main window
    MainWindow mainWindow;
    mainWindow.show();

    // Enter the main event loop
    return app.exec();
}


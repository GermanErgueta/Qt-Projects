/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *getAndZip;
    QAction *check;
    QAction *process;
    QAction *generateToProcess;
    QAction *generateToSend;
    QAction *transferToAkamai;
    QAction *exit;
    QAction *actionRemoveZipFiles;
    QAction *actionUpdateSharePoint;
    QWidget *centralwidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_7;
    QDateEdit *dateProcessing;
    QLabel *label;
    QLabel *label_4;
    QLineEdit *lineEditWindowsVersion;
    QLineEdit *lineEditLTspiceDevelopment;
    QLabel *label_3;
    QLabel *label_5;
    QSpacerItem *verticalSpacer;
    QComboBox *comboBoxSharePoint;
    QLabel *label_2;
    QLabel *label_6;
    QLineEdit *lineEditMacVersion;
    QLineEdit *lineEditFilesToProcess;
    QLineEdit *lineEditFilesToSend;
    QMenuBar *menubar;
    QMenu *menuDevices;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(673, 278);
        getAndZip = new QAction(MainWindow);
        getAndZip->setObjectName("getAndZip");
        check = new QAction(MainWindow);
        check->setObjectName("check");
        process = new QAction(MainWindow);
        process->setObjectName("process");
        generateToProcess = new QAction(MainWindow);
        generateToProcess->setObjectName("generateToProcess");
        generateToSend = new QAction(MainWindow);
        generateToSend->setObjectName("generateToSend");
        transferToAkamai = new QAction(MainWindow);
        transferToAkamai->setObjectName("transferToAkamai");
        exit = new QAction(MainWindow);
        exit->setObjectName("exit");
        actionRemoveZipFiles = new QAction(MainWindow);
        actionRemoveZipFiles->setObjectName("actionRemoveZipFiles");
        actionUpdateSharePoint = new QAction(MainWindow);
        actionUpdateSharePoint->setObjectName("actionUpdateSharePoint");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(10, 10, 641, 221));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_7 = new QLabel(gridLayoutWidget);
        label_7->setObjectName("label_7");

        gridLayout->addWidget(label_7, 6, 0, 1, 1);

        dateProcessing = new QDateEdit(gridLayoutWidget);
        dateProcessing->setObjectName("dateProcessing");

        gridLayout->addWidget(dateProcessing, 0, 1, 1, 1);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName("label");

        gridLayout->addWidget(label, 1, 0, 1, 1);

        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName("label_4");

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        lineEditWindowsVersion = new QLineEdit(gridLayoutWidget);
        lineEditWindowsVersion->setObjectName("lineEditWindowsVersion");

        gridLayout->addWidget(lineEditWindowsVersion, 1, 1, 1, 1);

        lineEditLTspiceDevelopment = new QLineEdit(gridLayoutWidget);
        lineEditLTspiceDevelopment->setObjectName("lineEditLTspiceDevelopment");

        gridLayout->addWidget(lineEditLTspiceDevelopment, 4, 1, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        label_5 = new QLabel(gridLayoutWidget);
        label_5->setObjectName("label_5");

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer, 7, 1, 1, 1);

        comboBoxSharePoint = new QComboBox(gridLayoutWidget);
        comboBoxSharePoint->setObjectName("comboBoxSharePoint");
        comboBoxSharePoint->setEditable(true);

        gridLayout->addWidget(comboBoxSharePoint, 3, 1, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        label_6 = new QLabel(gridLayoutWidget);
        label_6->setObjectName("label_6");

        gridLayout->addWidget(label_6, 5, 0, 1, 1);

        lineEditMacVersion = new QLineEdit(gridLayoutWidget);
        lineEditMacVersion->setObjectName("lineEditMacVersion");

        gridLayout->addWidget(lineEditMacVersion, 2, 1, 1, 1);

        lineEditFilesToProcess = new QLineEdit(gridLayoutWidget);
        lineEditFilesToProcess->setObjectName("lineEditFilesToProcess");

        gridLayout->addWidget(lineEditFilesToProcess, 5, 1, 1, 1);

        lineEditFilesToSend = new QLineEdit(gridLayoutWidget);
        lineEditFilesToSend->setObjectName("lineEditFilesToSend");

        gridLayout->addWidget(lineEditFilesToSend, 6, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 673, 21));
        menuDevices = new QMenu(menubar);
        menuDevices->setObjectName("menuDevices");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuDevices->menuAction());
        menuDevices->addSeparator();
        menuDevices->addAction(getAndZip);
        menuDevices->addSeparator();
        menuDevices->addAction(actionRemoveZipFiles);
        menuDevices->addSeparator();
        menuDevices->addAction(check);
        menuDevices->addSeparator();
        menuDevices->addSeparator();
        menuDevices->addAction(process);
        menuDevices->addSeparator();
        menuDevices->addSeparator();
        menuDevices->addAction(generateToProcess);
        menuDevices->addSeparator();
        menuDevices->addSeparator();
        menuDevices->addAction(generateToSend);
        menuDevices->addSeparator();
        menuDevices->addSeparator();
        menuDevices->addAction(transferToAkamai);
        menuDevices->addSeparator();
        menuDevices->addSeparator();
        menuDevices->addSeparator();
        menuDevices->addAction(actionUpdateSharePoint);
        menuDevices->addSeparator();
        menuDevices->addAction(exit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        getAndZip->setText(QCoreApplication::translate("MainWindow", "Get and Zip", nullptr));
        check->setText(QCoreApplication::translate("MainWindow", "Check", nullptr));
        process->setText(QCoreApplication::translate("MainWindow", "Process", nullptr));
        generateToProcess->setText(QCoreApplication::translate("MainWindow", "Generate ToProcess", nullptr));
        generateToSend->setText(QCoreApplication::translate("MainWindow", "Generate ToSend", nullptr));
        transferToAkamai->setText(QCoreApplication::translate("MainWindow", "Transfer to Akamai", nullptr));
        exit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        actionRemoveZipFiles->setText(QCoreApplication::translate("MainWindow", "Remove Zip files", nullptr));
        actionUpdateSharePoint->setText(QCoreApplication::translate("MainWindow", "Update SharePoint", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Files to be send:", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "LTspice Windows version:", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Sharepoint location", nullptr));
        lineEditLTspiceDevelopment->setText(QCoreApplication::translate("MainWindow", "LTspiceDevelopment", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "LTspice Mac Version:", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "LTspiceDevelopment directory", nullptr));
        comboBoxSharePoint->setCurrentText(QCoreApplication::translate("MainWindow", "C:/Users/GErgueta/Analog Devices, Inc/New Models - New devices", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Processing date:", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Files to process:", nullptr));
        lineEditFilesToProcess->setText(QCoreApplication::translate("MainWindow", "ToProcess", nullptr));
        lineEditFilesToSend->setText(QCoreApplication::translate("MainWindow", "ToSend", nullptr));
        menuDevices->setTitle(QCoreApplication::translate("MainWindow", "Devices", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

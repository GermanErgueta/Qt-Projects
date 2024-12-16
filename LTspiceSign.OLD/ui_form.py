# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'form.ui'
##
## Created by: Qt User Interface Compiler version 6.8.0
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide6.QtCore import (QCoreApplication, QDate, QDateTime, QLocale,
    QMetaObject, QObject, QPoint, QRect,
    QSize, QTime, QUrl, Qt)
from PySide6.QtGui import (QAction, QBrush, QColor, QConicalGradient,
    QCursor, QFont, QFontDatabase, QGradient,
    QIcon, QImage, QKeySequence, QLinearGradient,
    QPainter, QPalette, QPixmap, QRadialGradient,
    QTransform)
from PySide6.QtWidgets import (QApplication, QFormLayout, QLabel, QLineEdit,
    QPushButton, QRadioButton, QSizePolicy, QTextEdit,
    QWidget)

class Ui_Widget(object):
    def setupUi(self, Widget):
        if not Widget.objectName():
            Widget.setObjectName(u"Widget")
        Widget.resize(562, 696)
        self.actionSign = QAction(Widget)
        self.actionSign.setObjectName(u"actionSign")
        self.actionSign.setMenuRole(QAction.MenuRole.NoRole)
        self.SignButton = QPushButton(Widget)
        self.SignButton.setObjectName(u"SignButton")
        self.SignButton.setGeometry(QRect(390, 630, 100, 32))
        self.label = QLabel(Widget)
        self.label.setObjectName(u"label")
        self.label.setGeometry(QRect(30, 30, 58, 16))
        self.LTspiceVersion = QLineEdit(Widget)
        self.LTspiceVersion.setObjectName(u"LTspiceVersion")
        self.LTspiceVersion.setGeometry(QRect(130, 30, 113, 21))
        self.formLayoutWidget = QWidget(Widget)
        self.formLayoutWidget.setObjectName(u"formLayoutWidget")
        self.formLayoutWidget.setGeometry(QRect(20, 70, 211, 121))
        self.formLayout = QFormLayout(self.formLayoutWidget)
        self.formLayout.setObjectName(u"formLayout")
        self.formLayout.setLabelAlignment(Qt.AlignmentFlag.AlignLeading|Qt.AlignmentFlag.AlignLeft|Qt.AlignmentFlag.AlignVCenter)
        self.formLayout.setContentsMargins(0, 0, 0, 0)
        self.LTspiceRadioButton = QRadioButton(self.formLayoutWidget)
        self.LTspiceRadioButton.setObjectName(u"LTspiceRadioButton")

        self.formLayout.setWidget(0, QFormLayout.LabelRole, self.LTspiceRadioButton)

        self.LTspiceMsiRadioButton = QRadioButton(self.formLayoutWidget)
        self.LTspiceMsiRadioButton.setObjectName(u"LTspiceMsiRadioButton")

        self.formLayout.setWidget(1, QFormLayout.LabelRole, self.LTspiceMsiRadioButton)

        self.formLayoutWidget_2 = QWidget(Widget)
        self.formLayoutWidget_2.setObjectName(u"formLayoutWidget_2")
        self.formLayoutWidget_2.setGeometry(QRect(260, 70, 221, 121))
        self.formLayout_2 = QFormLayout(self.formLayoutWidget_2)
        self.formLayout_2.setObjectName(u"formLayout_2")
        self.formLayout_2.setContentsMargins(0, 0, 0, 0)
        self.LTspiceFilename = QLineEdit(self.formLayoutWidget_2)
        self.LTspiceFilename.setObjectName(u"LTspiceFilename")

        self.formLayout_2.setWidget(0, QFormLayout.LabelRole, self.LTspiceFilename)

        self.LTspiceMsiFilename = QLineEdit(self.formLayoutWidget_2)
        self.LTspiceMsiFilename.setObjectName(u"LTspiceMsiFilename")

        self.formLayout_2.setWidget(1, QFormLayout.LabelRole, self.LTspiceMsiFilename)

        self.information = QTextEdit(Widget)
        self.information.setObjectName(u"information")
        self.information.setGeometry(QRect(20, 200, 461, 411))

        self.retranslateUi(Widget)

        QMetaObject.connectSlotsByName(Widget)
    # setupUi

    def retranslateUi(self, Widget):
        Widget.setWindowTitle(QCoreApplication.translate("Widget", u"Widget", None))
        self.actionSign.setText(QCoreApplication.translate("Widget", u"Sign", None))
#if QT_CONFIG(tooltip)
        self.actionSign.setToolTip(QCoreApplication.translate("Widget", u"Sign", None))
#endif // QT_CONFIG(tooltip)
        self.SignButton.setText(QCoreApplication.translate("Widget", u"Sign", None))
        self.label.setText(QCoreApplication.translate("Widget", u"Version", None))
        self.LTspiceRadioButton.setText(QCoreApplication.translate("Widget", u"LTspice", None))
        self.LTspiceMsiRadioButton.setText(QCoreApplication.translate("Widget", u"LTspice msi", None))
        self.LTspiceFilename.setText(QCoreApplication.translate("Widget", u"LTspice.exe", None))
        self.LTspiceMsiFilename.setText(QCoreApplication.translate("Widget", u"LTspice64.msi", None))
    # retranslateUi


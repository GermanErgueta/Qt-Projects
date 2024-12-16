# This Python file uses the following encoding: utf-8
import sys
import argparse
import logging, logging.handlers
import hashlib
import json
import os, os.path
import time
import warnings
from PySide6.QtWidgets import QApplication, QWidget

from urllib3.fields import RequestField

# Important:
# You need to run the following command to generate the ui_form.py file
#     pyside6-uic form.ui -o ui_form.py, or
#     pyside2-uic form.ui -o ui_form.py
from ui_form import Ui_Widget
from urllib3.filepost import  encode_multipart_formdata
from urllib.parse import urljoin
import requests
import yaml
import glob
import re
import shutil

warnings.filterwarnings('ignore', message='Unverified HTTPS request')

__version__ = "0.1.3"

from PySide6.QtWidgets import QApplication, QWidget
from PySide6.QtCore import QTimer

from PySide6.QtWidgets import QApplication, QWidget
from PySide6.QtCore import QTimer
from ui_form import Ui_Widget

class Widget(QWidget):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.ui = Ui_Widget()
        self.ui.setupUi(self)


if __name__ == "__main__":
    app = QApplication(sys.argv)
    widget = Widget()
    widget.show()
    sys.exit(app.exec())

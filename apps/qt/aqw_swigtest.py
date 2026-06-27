#!/usr/bin/python2

from PyQt4 import QtGui

from aqw import *
#a = QtGui.QApplication([])


import sys

# from qt import *



a=QuarterApplication (["boo"])




qmw = QtGui.QMainWindow()
centralwidget = QtGui.QWidget(qmw)
qmw.resize(800,600)
qmw.setCentralWidget(centralwidget)
animatedQuarterWidget = AnimatedQuarterWidget(centralwidget)
animatedQuarterWidget.setGeometry(-1,-1,791,551)
animatedQuarterWidget.setObjectName("aqw test")

qmw.show()
sys.exit(a._exec())


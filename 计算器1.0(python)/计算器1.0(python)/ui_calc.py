# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file '计算器1.0.ui'
#
# Created by: PyQt5 UI code generator 5.15.7
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(315, 349)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.lvDisplay = QtWidgets.QListView(self.centralwidget)
        self.lvDisplay.setGeometry(QtCore.QRect(20, 10, 271, 71))
        self.lvDisplay.setObjectName("lvDisplay")
        self.widget = QtWidgets.QWidget(self.centralwidget)
        self.widget.setGeometry(QtCore.QRect(20, 90, 271, 211))
        self.widget.setObjectName("widget")
        self.verticalLayout = QtWidgets.QVBoxLayout(self.widget)
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout.setObjectName("verticalLayout")
        self.horizontalLayout = QtWidgets.QHBoxLayout()
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.btn_1 = QtWidgets.QPushButton(self.widget)
        self.btn_1.setMinimumSize(QtCore.QSize(50, 40))
        self.btn_1.setMaximumSize(QtCore.QSize(50, 40))
        self.btn_1.setObjectName("btn_1")
        self.horizontalLayout.addWidget(self.btn_1)
        self.btn_2 = QtWidgets.QPushButton(self.widget)
        self.btn_2.setMinimumSize(QtCore.QSize(50, 40))
        self.btn_2.setMaximumSize(QtCore.QSize(50, 40))
        self.btn_2.setObjectName("btn_2")
        self.horizontalLayout.addWidget(self.btn_2)
        self.btn_3 = QtWidgets.QPushButton(self.widget)
        self.btn_3.setMinimumSize(QtCore.QSize(50, 40))
        self.btn_3.setMaximumSize(QtCore.QSize(50, 40))
        self.btn_3.setObjectName("btn_3")
        self.horizontalLayout.addWidget(self.btn_3)
        self.btn_plus = QtWidgets.QPushButton(self.widget)
        self.btn_plus.setMinimumSize(QtCore.QSize(50, 40))
        self.btn_plus.setMaximumSize(QtCore.QSize(50, 40))
        self.btn_plus.setObjectName("btn_plus")
        self.horizontalLayout.addWidget(self.btn_plus)
        self.verticalLayout.addLayout(self.horizontalLayout)
        self.horizontalLayout_2 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_2.setObjectName("horizontalLayout_2")
        self.btn_4 = QtWidgets.QPushButton(self.widget)
        self.btn_4.setMinimumSize(QtCore.QSize(50, 40))
        self.btn_4.setMaximumSize(QtCore.QSize(50, 40))
        self.btn_4.setObjectName("btn_4")
        self.horizontalLayout_2.addWidget(self.btn_4)
        self.btn_5 = QtWidgets.QPushButton(self.widget)
        self.btn_5.setMinimumSize(QtCore.QSize(50, 40))
        self.btn_5.setMaximumSize(QtCore.QSize(50, 40))
        self.btn_5.setObjectName("btn_5")
        self.horizontalLayout_2.addWidget(self.btn_5)
        self.btn_6 = QtWidgets.QPushButton(self.widget)
        self.btn_6.setMinimumSize(QtCore.QSize(50, 40))
        self.btn_6.setMaximumSize(QtCore.QSize(50, 40))
        self.btn_6.setObjectName("btn_6")
        self.horizontalLayout_2.addWidget(self.btn_6)
        self.btn_sub = QtWidgets.QPushButton(self.widget)
        self.btn_sub.setMinimumSize(QtCore.QSize(50, 40))
        self.btn_sub.setMaximumSize(QtCore.QSize(50, 40))
        self.btn_sub.setObjectName("btn_sub")
        self.horizontalLayout_2.addWidget(self.btn_sub)
        self.verticalLayout.addLayout(self.horizontalLayout_2)
        self.horizontalLayout_3 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_3.setObjectName("horizontalLayout_3")
        self.btn_7 = QtWidgets.QPushButton(self.widget)
        self.btn_7.setMinimumSize(QtCore.QSize(50, 40))
        self.btn_7.setMaximumSize(QtCore.QSize(50, 40))
        self.btn_7.setObjectName("btn_7")
        self.horizontalLayout_3.addWidget(self.btn_7)
        self.btn_8 = QtWidgets.QPushButton(self.widget)
        self.btn_8.setMinimumSize(QtCore.QSize(50, 40))
        self.btn_8.setMaximumSize(QtCore.QSize(50, 40))
        self.btn_8.setObjectName("btn_8")
        self.horizontalLayout_3.addWidget(self.btn_8)
        self.btn_9 = QtWidgets.QPushButton(self.widget)
        self.btn_9.setMinimumSize(QtCore.QSize(50, 40))
        self.btn_9.setMaximumSize(QtCore.QSize(50, 40))
        self.btn_9.setObjectName("btn_9")
        self.horizontalLayout_3.addWidget(self.btn_9)
        self.btn_mul = QtWidgets.QPushButton(self.widget)
        self.btn_mul.setMinimumSize(QtCore.QSize(50, 40))
        self.btn_mul.setMaximumSize(QtCore.QSize(50, 40))
        self.btn_mul.setObjectName("btn_mul")
        self.horizontalLayout_3.addWidget(self.btn_mul)
        self.verticalLayout.addLayout(self.horizontalLayout_3)
        self.horizontalLayout_4 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_4.setObjectName("horizontalLayout_4")
        self.btn_0 = QtWidgets.QPushButton(self.widget)
        self.btn_0.setMinimumSize(QtCore.QSize(50, 40))
        self.btn_0.setMaximumSize(QtCore.QSize(50, 40))
        self.btn_0.setObjectName("btn_0")
        self.horizontalLayout_4.addWidget(self.btn_0)
        self.btn_delete = QtWidgets.QPushButton(self.widget)
        self.btn_delete.setMinimumSize(QtCore.QSize(50, 40))
        self.btn_delete.setMaximumSize(QtCore.QSize(50, 40))
        self.btn_delete.setObjectName("btn_delete")
        self.horizontalLayout_4.addWidget(self.btn_delete)
        self.btn_equal = QtWidgets.QPushButton(self.widget)
        self.btn_equal.setMinimumSize(QtCore.QSize(50, 40))
        self.btn_equal.setMaximumSize(QtCore.QSize(50, 40))
        self.btn_equal.setObjectName("btn_equal")
        self.horizontalLayout_4.addWidget(self.btn_equal)
        self.btn_chu = QtWidgets.QPushButton(self.widget)
        self.btn_chu.setMinimumSize(QtCore.QSize(50, 40))
        self.btn_chu.setMaximumSize(QtCore.QSize(50, 40))
        self.btn_chu.setObjectName("btn_chu")
        self.horizontalLayout_4.addWidget(self.btn_chu)
        self.verticalLayout.addLayout(self.horizontalLayout_4)
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 315, 23))
        self.menubar.setObjectName("menubar")
        self.menu = QtWidgets.QMenu(self.menubar)
        self.menu.setObjectName("menu")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)
        self.action = QtWidgets.QAction(MainWindow)
        self.action.setObjectName("action")
        self.menu.addAction(self.action)
        self.menubar.addAction(self.menu.menuAction())

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.btn_1.setText(_translate("MainWindow", "1"))
        self.btn_2.setText(_translate("MainWindow", "2"))
        self.btn_3.setText(_translate("MainWindow", "3"))
        self.btn_plus.setText(_translate("MainWindow", "+"))
        self.btn_4.setText(_translate("MainWindow", "4"))
        self.btn_5.setText(_translate("MainWindow", "5"))
        self.btn_6.setText(_translate("MainWindow", "6"))
        self.btn_sub.setText(_translate("MainWindow", "-"))
        self.btn_7.setText(_translate("MainWindow", "7"))
        self.btn_8.setText(_translate("MainWindow", "8"))
        self.btn_9.setText(_translate("MainWindow", "9"))
        self.btn_mul.setText(_translate("MainWindow", "*"))
        self.btn_0.setText(_translate("MainWindow", "0"))
        self.btn_delete.setText(_translate("MainWindow", "删除"))
        self.btn_equal.setText(_translate("MainWindow", "="))
        self.btn_chu.setText(_translate("MainWindow", "/"))
        self.menu.setTitle(_translate("MainWindow", "设置"))
        self.action.setText(_translate("MainWindow", "标准"))

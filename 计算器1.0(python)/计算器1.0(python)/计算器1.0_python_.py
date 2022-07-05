#
#       项目名称：计算器
#       文件名称：
#       文件作者:
#       创建时间：
#       文件描述：
#   
from pickle import FALSE
from PyQt5.QtWidgets import QApplication,QMainWindow,QPushButton,QVBoxLayout,QMessageBox
from PyQt5.QtCore import QStringListModel
from ui_calc import Ui_MainWindow   #把设计的界面导入
import re

class CalcWindow(QMainWindow):

    #类 CalcWindow 一使用，就自动执行__init__函数里面的代码
    def __init__(self) -> None:
        super().__init__()
        self.ui = Ui_MainWindow()   #使用导入的界面
        self.ui.setupUi(self)       #把界面绑定到这个CalcWindow类

        self.clickHistory = ""      #记录用户点击的历史
        self.qList = []             #记录用户点击的历史和结果
        self.bClearDisplay = False

        self.InitClickEvent()       #调用函数

    def InitClickEvent(self):
         # 绑定界面按钮点击 按钮点击，则调用OnBtnClicked函数
        self.ui.btn_0.clicked.connect(lambda: self.OnBtnClicked(0))
        self.ui.btn_1.clicked.connect(lambda: self.OnBtnClicked(1))
        self.ui.btn_2.clicked.connect(lambda: self.OnBtnClicked(2))
        self.ui.btn_3.clicked.connect(lambda: self.OnBtnClicked(3))
        self.ui.btn_4.clicked.connect(lambda: self.OnBtnClicked(4))
        self.ui.btn_5.clicked.connect(lambda: self.OnBtnClicked(5))
        self.ui.btn_6.clicked.connect(lambda: self.OnBtnClicked(6))
        self.ui.btn_7.clicked.connect(lambda: self.OnBtnClicked(7))
        self.ui.btn_8.clicked.connect(lambda: self.OnBtnClicked(8))
        self.ui.btn_9.clicked.connect(lambda: self.OnBtnClicked(9))
        self.ui.btn_plus.clicked.connect(lambda: self.OnBtnClicked("+"))    # 加 减 乘 除
        self.ui.btn_sub.clicked.connect(lambda: self.OnBtnClicked("-"))
        self.ui.btn_mul.clicked.connect(lambda: self.OnBtnClicked("*"))
        self.ui.btn_chu.clicked.connect(lambda: self.OnBtnClicked("/"))
        self.ui.btn_equal.clicked.connect(lambda: self.OnBtnClicked("="))   # 等于

    def OnBtnClicked(self,num):
        self.qList = []
        if num == "=":                              # 如果参数num 是 =，则计算结果，并显示到界面
            # 过滤非法按等于
            #if len(self.clickHistory) == 0:
            #if self.clickHistrot.find["+","-","*","/"]
            #if len(split("+")) < 2

            #处理输入历史，如1+2-0*4/2  先算乘除，后算加减。加减或乘除，从左往右算
            result = self.CalcString(self.clickHistory)

            self.bClearDisplay = True
            self.qList.insert(1,"等于: "+str(result)) # 把计算记过保存到self.qList里面
        else:
            #除数不能为0
            if num == 0 and self.clickHistory[-1]=="/":
                QMessageBox("除数不能为0！")
                return

            if type(num) != str:                    # 如果是数字，就要把数据转换为字符串保持，如 1 转为 "1"
                self.clickHistory += str(num)       # 每点击一次都将num保存到 self.clickHistory里面
            else:
                if len(self.clickHistory)!=0 and self.clickHistory[-1] in ["+","-","*","/"]:
                    self.clickHistory = self.clickHistory[:-1]  #防止两个运算符，例如：1-+2、1*+2,去掉上一个-或*

                self.clickHistory += num            # 每点击一次都将num保存到 self.clickHistory里面

        self.qList.insert(0,self.clickHistory)      # 把输入历史也保存到self.qList里面

        listModel = QStringListModel()
        listModel.setStringList(self.qList)
        self.ui.lvDisplay.setModel(listModel)       # 把self.qList 显示到界面

        if self.bClearDisplay:
            self.clickHistory = ""
            self.bClearDisplay = False

    def CalcString(self,strHistory):
        nCount = 0  # 获取位置标记
        liPlus = []
        liSub  = []
        liMul  = []
        liDiv  = []
        liPlusSubCh = []
        for ch in strHistory:
            if ch == "+":
                nCount += 1
                liPlus.append(nCount)
                liPlusSubCh.append(ch)
            if ch == "-":
                nCount += 1
                liSub.append(nCount)
                liPlusSubCh.append(ch)
            if ch == "*":
                nCount += 1
                liMul.append(nCount)
            if ch == "/":
                nCount += 1
                liDiv.append(nCount)

        # 提取数字 1，43，2，7，2
        listNum = re.split("\+|-|\*|/",strHistory)

        liMulNum = []   # 计算乘除
        liDivNum = []
        nFlag = 0
        bothLen = len(liMul) + len(liDiv) 
        for i in range(0,bothLen):
            if len(liMul) == 0:
                for div in liDiv:
                    result = float(listNum[div-1]) / float(listNum[div])
                    liDivNum.append(result)

                    liPreNum = listNum[:div-1]
                    liPreNum.append(result)
                    liLastNum = listNum[div+1:]
                    listNum = liPreNum+liLastNum
                    nFlag += 1
                continue
            if len(liDiv) == 0:
                for mul in liMul:
                    result = float(listNum[mul-1]) * float(listNum[mul])
                    liMulNum.append(result)

                    liPreNum = listNum[:mul-1]
                    liPreNum.append(result)
                    liLastNum = listNum[mul+1:]
                    listNum = liPreNum+liLastNum
                    nFlag += 1
                continue

            minMulNum = min(liMul)
            minChuNum = min(liDiv)
            if minMulNum < minChuNum:
                result = float(listNum[minMulNum-1]) * float(listNum[minMulNum])
                liMulNum.append(result)
                liMul.remove(minMulNum)

                liPreNum = listNum[:minMulNum-1]
                liPreNum.append(result)
                liLastNum = listNum[minMulNum+1:]
                listNum = liPreNum+liLastNum

            else:
                result = float(listNum[minChuNum-1]) / float(listNum[minChuNum])
                liDivNum.append(result)
                liDiv.remove(minChuNum)

                liPreNum = listNum[:minChuNum-1]
                liPreNum.append(result)
                liLastNum = listNum[minChuNum+1:]
                listNum = liPreNum+liLastNum

            liMul = [i-1 for i in liMul]
            liDiv = [i-1 for i in liDiv]
            nFlag += 1

        target = float(listNum[0])  # 计算加减
        lenCh = len(liPlusSubCh)
        for i in range(1,lenCh+1):
            preNum = float(listNum[i])
            if liPlusSubCh[i-1] == "+":
                target += preNum
            else:
                target -= preNum


        return target


if __name__ == "__main__":
    app = QApplication([])

    calcWin = CalcWindow()
    calcWin.show()

    app.exec()




from threading import Timer
import time
import os


class LastUpload():
    def __init__(self,strForder):
        self.nFileIndex = 1#第几个文件
        self.mapFile = {}#通过id找到文件名
        self.bFirstRun = True#程序第一次运行
        self.nHisSize = 0
        self.strForder = strForder
        self.strConfig = "./config.txt"

    def IterForder(self,forder:str):
        '''递归遍历文件'''
        for root,dirs,files in os.walk(forder):
            if files:
                for file in files:
                    #提取文件名
                    names = file.split(".")

                    if names[1] in self.mapFile.values():# 不同目录，同名文件处理
                        continue

                    self.mapFile[str(self.nFileIndex)] = names[1]
                    self.nFileIndex += 1
            if dirs:
                for dir in dirs:
                    self.IterForder(forder + '/' +dir)

    def GetHistoryConfig(self):
        '''获取历史文件'''
        historyFile = []
        if os.path.exists(self.strConfig):
            with open(self.strConfig,"r") as fp:
                lines = fp.readlines()
                for line in lines:
                    row = line.split(' ')
                    historyFile.append(row[1])
        else:
            with open(self.strConfig,"w")as fp:
                pass
        return historyFile

    def SaveConfig(self):
        '''保存新上传的文件'''  
        #保存修改文件名、删除文件 bug
        hisFile:list = self.GetHistoryConfig()
        addCount = len(hisFile) + 1
        with open(self.strConfig,"a") as fp:
            for index,file in self.mapFile.items():
                if not hisFile and not file in hisFile:
                    time.gmtime(time.time())
                    strTime = time.strftime('%Y/%m/%d/%H:%M:%S', time.gmtime(time.time()))

                    strRow = strTime+' '+file+' '+str(addCount) + "\n"
                    fp.write(strRow)

                    addCount += 1


    def GetHisSize(self)->int:
        '''获取历史文件数量'''
        self.bFirstRun = False
        nHisSize = 0
        with open(self.strConfig,"r") as fp:
            lines = fp.readlines()
            lastLine = lines[-1]
            nHisSize = int(lastLine.split(' ')[2])
        return nHisSize

    def WorkThread(self):
        self.IterForder(self.strForder)

        if self.nFileIndex != self.nHisSize:
            self.SaveConfig()#保存新上传的文件记录到配置文件中

        if self.bFirstRun:
            self.nHisSize = self.GetHisSize()

        self.LoopTimer()

    def LoopTimer(self):
        if self.bFirstRun:
            Timer(0,self.WorkThread).start()
        else:
            Timer(10,self.WorkThread).start()

    def GetLastFiles(self)->list:
        '''获取最新上传的文件'''
        uploadTime = ""
        lastFiles = []
        with open(self.strConfig,"r") as fp:
            lines = fp.readlines()
            for row in lines:
                strRow = row.split(' ')

                if uploadTime != strRow[0]:
                    uploadTime = strRow[0]
                    lastFiles = []
                lastFiles.append(strRow[1])

        return lastFiles

    def GetNameById(self,id:str):
        return self.mapFile[id]

if __name__ == "__main__":
    print("定时线程已经启动.")
    lastUpload = LastUpload("./test")
    lastUpload.LoopTimer()
    time.sleep(2)
    print(lastUpload.GetLastFiles())
    print(lastUpload.GetNameById("1"))


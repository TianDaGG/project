
# 处理输入历史字符串，例如：1+43-2*7/2
import re

def CalcString(strHistory):
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
    num = CalcString("1+43-2*7/2+2-3+4*2-64/8")
    print(num)

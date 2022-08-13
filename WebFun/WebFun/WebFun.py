# -*- coding: utf-8 -*-
#==================================================
#	Project Name: WebFun
#	File Name	: WebFun.py
#	Author		: HuangDaTian
#	Create Time	: 2022-03-13  9:29:08
#	Modify Time	: 2022-03-13  9:29:08
#	Description	: 
#==================================================*/
import os
from server.struct import CreateTable
CreateTable()
from server import app

if __name__ == '__main__':
    workDir = os.getcwd()
    if workDir[0] != "E":
        app.run("10.0.20.15","80",debug=False)
    else:
        app.run("127.0.0.1","8889",debug=True)

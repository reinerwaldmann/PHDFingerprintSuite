#!/usr/bin/python3
# -*- coding: utf-8 -*-

import sys


#берём имя файла из первого выданного параметра
fname=sys.argv[1]
if (len(sys.argv)>2):
        ifShowDebug=1
else:
        ifShowDebug=0



#задаём строку поиска
variantLine = "ColAverage"

def splitStripLine (line):
	lnl=line.split('\t')
	return lnl[1:len(lnl)-1]

#открываем файл 
try:
        f = open(fname, "r", 1)
except:
        print("Error: Wrong filename, aborting")
        exit(1)

#выдёргиваем строку имён контейнера
factorNamesList = splitStripLine(f.readline())


#ищем строку в файле, префикс которой задан строкой variantLine
lineWithValues=" "
for line in f:
        if (line.find("ColAverage")==0):
                lineWithValues=line
                break
if(lineWithValues==" "):
   print("No variantLine in input file")
   exit(1)

lineWVList = splitStripLine(lineWithValues)

#print ([line for line in lineWVList])


#стоим матрицу из единичек
#roll-flat-internalmobile-internalmobile-ds45-fork.txt
#roll-flat 1   flat-flat -1
#internalmobile=1  normal=-1
#ds45-fork=1  fork-fork=-1

#order:  1 ds45-fork  internalmobile   roll-flat

#for line in factorNamesList:
#решим, что порядок тестов неизменен, и т. о. матрица может быть задана явно

import numpy as np
from scipy import linalg


A=np.array(
[[1,1,1,1],
[1,1,1,-1],
[1,1,-1,1],
[1,1,-1,-1],
[1,-1,1,-1],
[1,-1,-1,-1]])

t=[]
 
for line in lineWVList:
       t.append(float(line))

B=np.array([t])
B=B.T

if (ifShowDebug):
        print ("Matrix A: \n")
        print(A)
        print ("Matrix B: \n")
        print(B)
        print ("\n \n \n")
        print ("Matrix Results: \n")
 
  
Solution=(linalg.pinv(A)).dot(B)

for d in Solution:
        print (d[0])

f.close()







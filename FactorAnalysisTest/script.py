#!/usr/bin/python3
# -*- coding: utf-8 -*-


#задаём строку поиска
variantLine = "rightthumb0.9999"



def splitStripLine (line):
	lnl=line.split('\t')
	return lnl[1:len(lnl)-1]


#открываем файл 
f = open("FingerCellFRRResults.txt", "r", 1)

#выдёргиваем строку имён контейнера
factorNamesList = splitStripLine(f.readline())
#print ([line for line in factorNamesList])


#ищем строку в файле, префикс которой задан строкой variantLine
lineWithValues=" "
for line in f:
   if line.find(variantLine):
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
[1,1,-1,1],
[1,-1,1,-1],
[1,-1,-1,-1]])

t=[]
#счётчик для грязного хака
i=0

for line in lineWVList:
      i+=1
      if (i==2) or (i==4):
              continue
      t.append(float(line))

B=np.array(t)

print(A)
print(B)


 
 
print (np.linalg.solve(A,B))
  
        












print ("Succeeded")

f.close()







from asyncore import read
from cgitb import text
import sys
import numpy as np
from utils import *
import copy

class Sudoku(object):
    def __init__(self, n=4, textfile=''):
        self.n = n
        self.matrix = self.read_file(textfile)
    
    def read_file(self, textfile):
        """read initial puzzle from textfile

		Args:
			textfile (str): name of textfile

		Returns:
			List[List]: initial puzzle
		"""
        f = open(textfile,'r')
        i, j = 0, 0
        matrix=[[0 for x in range(self.n)] for y in range(self.n)]
        while True:
            j = 0
            char = f.readline()
            for c in char:
                matrix[i][j] = int(c)
                j += 1
                if j == 4:
                    i += 1
                    break
            if i == 4:
                break
        return matrix
    
    def print_puzzle(self):
        for i in range(self.n):
            print('+'+'+'.join(['---']*4)+'+')
            print('|'+'|'.join([' %d ' % item for item in self.matrix[i] ])+'|')
        print('+'+'+'.join(['---']*4)+'+')
        
    def goal_reached(self,matrix):                                #判断是否完成解
        num=0
        for i in range (len(matrix)):
            for j in range (len(matrix[i])):                      #判断待充填位置数目
                if matrix[i][j]==0:
                    num+=1
        return num==0                                             #判断是否为0
    
    def all_diff(self,array):                                     #判断array内的值是否都不一样
        array_1=[]
        array_2=[]
        for a in range (len(array)):                              #去掉所有的零项并写入array
            if array[a]!=0:
                array_1.append(array[a])
        for b in range (len(array)):                              #去掉所有零项以及重复的项
            if not array[b] in array_2 and array[b]!=0:
                array_2.append(array[b])
        return len(array_1)==len(array_2)                         #判断两个array长度是否相同判断是否全部的值都是不同的
    
    def expand(self,matrix,k=0):                                  #发展项
        values=np.array([1,2,3,4])                                #域值  
        squence=[[0,0],[1,0],[0,1],[1,1]]                         #正方形取值顺序 
        i=j=0 
        while matrix[i][j]!=0:                                    #获得尚未填充位置的坐标
            if i==3 and j==3:
                 break
            elif j==3:
                i+=1
                j=0
            else:
                j+=1
        row_diff=np.setdiff1d(values,matrix[i])                  #获得行中仍未出现的值
        while k<len(row_diff):
            new_matrix=copy.deepcopy(matrix)                     
            new_matrix[i][j]=row_diff[k]                         
            column_array=[]
            for column in range (len(new_matrix)):      
                column_array.append(new_matrix[column][j])
            if Sudoku.all_diff(self,column_array)is False:       #查看列中是否所有值都不同
                k+=1                                             #若有重复项则重新选择域值
                if k==len(row_diff):                             #若已检查
                    break
                else:
                   continue
            x=(-1)**(j)
            y=(-1)**(i)
            square=[]
            for z in range (len(squence)):
                square.append(new_matrix[i+squence[z][0]*y][j+squence[z][1]*x])     
            if Sudoku.all_diff(self,square) is False:           #查看2*2正方形范围内是否所有值都不同
                k+=1                                            #若有重复项则重新选择域值
                continue
            elif Sudoku.all_diff(self,square) is True and Sudoku.all_diff(self,column_array) is True:
                break                                           #当正方形范围以及列中所有值都不同时结束
        if k==len(row_diff):                                 
            return matrix                                       #如果没有合适的解则返回输入的矩阵                             
        return new_matrix                                       #如果有解则输出解
    
    def solve_puzzle(self,game):
        matrix=np.array(game.matrix)
        s=Stack()
        s.push(matrix)
        game.print_puzzle()                              #输出初始状态
        while 1:
            next_matrix=Sudoku.expand(self,matrix)             #单个为充填位置求解
            while (next_matrix==matrix).all():
                matrix=s.pop()                                 #若没有合适解则返回上一个状态并从第二个赋值求解
                if matrix is None:                             #若没有返回状态则结束
                    break
                next_matrix=game.expand(matrix,1)
            if matrix is None:
                print("无解")
                break
            s.push(next_matrix)
            matrix=next_matrix
            if game.goal_reached(matrix) is True:
                print("求解成功！")
                game.matrix=matrix                      
                game.print_puzzle()                   #求解成功并输出结果
                break
    
game = Sudoku(n=4, textfile='test_case_6.txt')
game.solve_puzzle(game)
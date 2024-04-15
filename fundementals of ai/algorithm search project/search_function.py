from utils import *
import numpy as np
from copy import deepcopy
import random as rand

class Node():
    def __init__(self, map,parent=None, path_cost=0, direction=0):
        self.map=map
        self.parent=parent
        self.path_cost=path_cost
        self.depth=0
        self.direction=direction
        if parent:
            self.depth=parent.depth+1
    
    def child_node(self,problem, egg_coordinate,action):
        next_state = problem.move(egg_coordinate, action)
        x_diff=egg_coordinate[1]-action[1]
        y_diff=egg_coordinate[0]-action[0]
        if x_diff==0:
            if y_diff==1:
                direction=[1,0]
            else:
                direction=[-1,0]
        if y_diff==0:
            if x_diff==1:
                direction=[0,1]
            else:
                direction=[0,-1]
        next_node = Node(next_state, self, self.path_cost+1,direction)
        return next_node

    def path(self):
        node, path_back, pathing = self, [], []
        while node:
            path_back.append(node)
            node = node.parent
        for i in range (len(path_back)):
            pathing.append(path_back[len(path_back)-(i+1)])
        return pathing

    def __repr__(self):
        return format(self.direction)



class Problem_solving():

    def __init__(self,map):
        self.node=Node(map)
    
    def action(self,coordinate):
        valid_candidates = []
        candidates = [[coordinate[0]-1, coordinate[1]], [coordinate[0]+1, coordinate[1]],[coordinate[0], coordinate[1]-1], [coordinate[0], coordinate[1]+1]]
        for i in range (len(candidates)):
            if self.node.map[candidates[i][0]][candidates[i][1]]!=1:
                valid_candidates += [candidates[i]]        
        return valid_candidates

    def move(self,coordinate,action):
        new_map=deepcopy(self.node.map)
        new_map[action[0]][action[1]]=self.node.map[coordinate[0]][coordinate[1]]
        new_map[coordinate[0]][coordinate[1]]=0
        return new_map
    
    def expand(self,node,coordinate,action):
        return node.child_node(self, coordinate,action)

    def get_egg(self):
        for i in range (len(self.node.map)):
            for j in range(len(self.node.map[i])):
                if self.node.map[i][j]==3:
                    break
            if self.node.map[i][j]==3:
                    break
        return [i,j]


class Map():

    def __init__(self,row=10,column=12):
        self.row=row
        self.column=column

    def empty_space(self,map):
        array=[]
        for i in range (len(map)):
            for j in range (len(map[i])):
                if map[i][j]==0:
                    array.append([i,j])
                    
        return array

    def map_building(self):
        block=[]
        map=np.zeros((self.row,self.column))
        for i in range (self.column):
            map[0][i]=1
        for i in range (self.column):
            map[self.row-1][i]=1
        for i in range (self.row):
            map[i][0]=1
        for i in range (self.row):
            map[i][self.column-1]=1
        while len(block)<8:
            wall=[rand.randint(1,self.row-2),rand.randint(1,self.column-2)]
            if not wall in block:
                block.append(wall)      
        for i in range (len(block)):
            map[block[i][0]][block[i][1]]=1
        return map


    def fill_coordinate(self,map,list):
        for i in range(4):
            map[list[i][0]][list[i][1]]=3
        for i in range(4,8):
            map[list[i][0]][list[i][1]]=4

    def get_wall(self,map):
        array=[]
        for i in range (len(map)):
            for j in range (len(map[i])):
                if map[i][j]==1:
                    array.append([i,j])
        return array

    def get_coordinate(self,map):
        zeros=self.empty_space(map)
        coordinate=[]
        while len(coordinate)<8:
            place=zeros[rand.randint(0,len(zeros)-1)]
            if place not in coordinate:
                if len(coordinate)<4:
                    if place[0]!=1 and place[0]!=self.row-2 and place[1]!=1 and place[1]!=self.column-2:
                        coordinate.append(place)
                else:
                    coordinate.append(place)
        return coordinate

    def make_partial(self, map, coordinate):
        new_map=deepcopy(map)
        for i in range(len(map)):
            for j in range(len(map[i])):
                if map[i][j]==3:
                    new_map[i][j]=1
        new_map[coordinate[0]][coordinate[1]]=3
        return new_map
    
    def map_validation(self, map,list):
        for i in range (4):
            is_wall=0
            for j in range(1,3):
                if map[list[i][0]][list[i][1]+pow(-1,j)]==1 or 3:
                    is_wall+=1
                if map[list[i][0]+pow(-1,j)][list[i][1]]==1 or 3:
                    is_wall+=1
            if is_wall>1:
                print(list[i],"egg is not valid")
                return False
        for i in range (4,8):
            is_wall=0
            for j in range(1,3):
                if map[list[i][0]][list[i][1]+pow(-1,j)]==1:
                    is_wall+=1
                if map[list[i][0]+pow(-1,j)][list[i][1]]==1:
                    is_wall+=1
            if is_wall==4:
                print(list[i],"hole is not valid")
                return False
        return True
    def init_map():
        

if __name__ == "__main__":
    Solution=False
    m=Map()
    mapping=m.map_building()
    coordinate_list=m.get_coordinate(mapping)
    m.fill_coordinate(mapping,coordinate_list)
    print(mapping)
    while m.map_validation(mapping,coordinate_list)==False:
        mapping=m.map_building()
        coordinate_list=m.get_coordinate(mapping)
        m.fill_coordinate(mapping,coordinate_list)
        print(mapping)
    
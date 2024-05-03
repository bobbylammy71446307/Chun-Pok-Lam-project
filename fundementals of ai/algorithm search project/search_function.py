from utils import *
import numpy as np
from copy import deepcopy
import random as rand

direction=[[-1,0],[1,0],[0,-1],[0,1]]


class Node():
    def __init__(self, map,parent=None, path_cost=0,direction=None):
        self.map=map
        self.parent=parent
        self.path_cost=path_cost
        self.depth=0
        self.direction=direction
        if parent:
            self.depth=parent.depth+1
    
    def child_node(self,new_map, distance,direction):
        dir_cost=0
        if self.parent is not None and self.parent.direction != direction:
           dir_cost=10

        next_node = Node(map=new_map, parent=self, path_cost=self.depth+1+distance+dir_cost,direction=direction)
        return next_node

    def path(self):
        node, path_back, pathing = self, [], []
        while node.parent is not None:
            path_back.append(node.direction)
            node = node.parent
        for i in range (1,len(path_back)+1):
            pathing.append(path_back[-i])
        return pathing




class Problem_solving():

    def __init__(self,node):
        self.node=node
    
    def action(self,coordinate):
        valid_candidates = []
        valid_direction = []
        candidates = [[coordinate[0]-1, coordinate[1]], 
                      [coordinate[0]+1, coordinate[1]],
                      [coordinate[0], coordinate[1]-1], 
                      [coordinate[0], coordinate[1]+1]]
        for i in range (0,len(direction),2):
            element_1=self.node.map[coordinate[0]+direction[i][0]][coordinate[1]+direction[i][1]]
            element_2=self.node.map[coordinate[0]+direction[i+1][0]][coordinate[1]+direction[i+1][1]]
            accept=[[0,0],[0,4],[4,0]]
            if [element_1,element_2] in accept:
                valid_candidates += [candidates[i]]
                valid_candidates += [candidates[i+1]]
                valid_direction += [direction[i]]
                valid_direction += [direction[i+1]]
        return valid_candidates, valid_direction



    def mouse_action(self,coordinate):
        valid_candidates = []
        valid_direction = []
        candidates = [[coordinate[0]-1, coordinate[1]], 
                      [coordinate[0]+1, coordinate[1]],
                      [coordinate[0], coordinate[1]-1], 
                      [coordinate[0], coordinate[1]+1]]
        for i in range (0,len(direction)):
            element_1=self.node.map[coordinate[0]+direction[i][0]][coordinate[1]+direction[i][1]]
            if element_1==0:
                valid_candidates += [candidates[i]]
                valid_direction += [direction[i]]
        return valid_candidates, valid_direction

    def move(self,coordinate,action):
        new_map=deepcopy(self.node.map)
        new_map[action[0]][action[1]]=self.node.map[coordinate[0]][coordinate[1]]
        new_map[coordinate[0]][coordinate[1]]=0
        return new_map
    
    def expand(self,coordinate,action,destination_coordinate,direction):
        new_map=self.move(coordinate,action)
        distance=abs(destination_coordinate[0]-action[0])+abs(destination_coordinate[1]-action[1])
        child=self.node.child_node(new_map,distance,direction)
        return child

    def get_element(self,is_egg):
        if is_egg:
            element=3
        else:
            element=2
        for i in range (len(self.node.map)):
            for j in range(len(self.node.map[i])):
                if self.node.map[i][j]==element:
                    break
            if self.node.map[i][j]==element:
                    break
        return [i,j]
    
    def get_solution(self,destination_coordinate,q_action,is_egg=True):
        coordinate=self.get_element(is_egg)
        if is_egg:
            validcandidates, validdirection = self.action(coordinate)
        else:
            validcandidates,validdirection= self.mouse_action(coordinate)
        for i in range (len(validcandidates)):
            next_node=self.expand(coordinate,validcandidates[i],destination_coordinate,validdirection[i])
            q_action.push(next_node)




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
        mouse_coordinate=[self.row-2,1]
        map[mouse_coordinate[0]][mouse_coordinate[1]]=2
        block.append(mouse_coordinate)
        while len(block)<9:
            wall=[rand.randint(1,self.row-2),rand.randint(1,self.column-2)]
            if not wall in block:
                block.append(wall)      
        for i in range (1,len(block)):
            map[block[i][0]][block[i][1]]=1
        return mouse_coordinate,map


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

    def make_completed(self,map,egg_coordinate,hole_coordinate):
        map[egg_coordinate[0]][egg_coordinate[1]]=0
        map[hole_coordinate[0]][hole_coordinate[1]]=3
        return map
    
    def mouse_complete(self,map,mouse,start):
        map[mouse[0]][mouse[1]]=0
        map[start[0]][start[1]]=2
        return map
    
    def make_partial(self, map, egg_coordinate,hole_coordinate):
        new_map=deepcopy(map)
        for i in range(len(map)):
            for j in range(len(map[i])):
                if map[i][j]==3 and [i,j]!=egg_coordinate:
                    new_map[i][j]=1
                elif map[i][j]==4 and [i,j]!=hole_coordinate:
                    new_map[i][j]=1
        return new_map
    
    def map_validation(self, map,list):
        for i in range (4):
            is_wall=0
            for j in range(1,3):
                if map[list[i][0]][list[i][1]+pow(-1,j)] == 1 or map[list[i][0]][list[i][1]+pow(-1,j)]==3:
                    is_wall+=1
                if map[list[i][0]+pow(-1,j)][list[i][1]]== 1 or map[list[i][0]+pow(-1,j)][list[i][1]]==3:
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
    
    def get_close_hole(self,egg_coordinate,hole_list):
        closest_hole_distance=99
        for i in range(len(hole_list)):
            hole_from_egg=abs(egg_coordinate[0]-hole_list[i][0])+abs(egg_coordinate[1]-hole_list[i][1])
            if closest_hole_distance>hole_from_egg:
                closest_hole_distance=hole_from_egg
                closest_hole=hole_list[i]
        hole_list.remove(closest_hole)
        return closest_hole

    def get_egg_prio(self):
        egg_list=np.zeros(22,dtype=list)
        for i in range(4):
            dis=(10-coordinate_list[i][0])+coordinate_list[i][1]
            if egg_list[dis]==0:
                egg_list[dis]=coordinate_list[i]
            else:
                egg_list[dis+1]=coordinate_list[i]
        egg_list=[i for i in egg_list if i!=0]
        return egg_list
    
    def map_init(self):
        mouse,mapping=self.map_building()
        coordinate_list=self.get_coordinate(mapping)
        self.fill_coordinate(mapping,coordinate_list)
        print(mapping)
        map_valid=m.map_validation(mapping,coordinate_list)
        return mapping,coordinate_list,map_valid,mouse


        

if __name__ == "__main__":
    map_valid=False
    m=Map()
    while map_valid==False:
        mapping,coordinate_list,map_valid,mouse=m.map_init()  
        if map_valid==False:
            continue
        egg_list=m.get_egg_prio()
        hole_list=coordinate_list[4:]
        solve_map=deepcopy(mapping)
        for i in range (len(egg_list)):
            egg=egg_list[i]
            hole=m.get_close_hole(egg,hole_list)
            partial_map=m.make_partial(solve_map,egg,hole)
            completed_map=m.make_completed(deepcopy(partial_map),egg,hole)
            q_action=PriorityQueue(Node(partial_map))
            while q_action.empty() is False:
                solve=Problem_solving(q_action.pop())
                solve.get_solution(hole,q_action)
                if (solve.node.map==completed_map).all():
                    print("solved")
                    break
            if q_action.empty():
                map_valid==False
                continue
            path=solve.node.path()

            egg_start=[egg[0]-path[0][0],egg[1]-path[0][1]]
            complete_start_map=m.mouse_complete(deepcopy(partial_map),mouse,egg_start)
            q_egg_action=PriorityQueue(Node(partial_map))
            while q_egg_action.empty() is False:
                start=Problem_solving(q_egg_action.pop())
                start.get_solution(egg_start,q_egg_action,is_egg=False)
                if (start.node.map==complete_start_map).all():
                    print("started")
                    break;
            if q_egg_action.empty():
                map_valid==False
                continue
            start_path=start.node.path()
            start_path+=path
            print(start_path)


            solve_map[egg[0]][egg[1]]=0
            solve_map[hole[0]][hole[1]]=1
            mouse=[hole[0]-path[-1][0],hole[1]-path[-1][1]]
            solve_map[mouse[0]][mouse[1]]==2
            print(f"egg {i+1} {egg} solved")
            print(start_path)            


import numpy as np
import random as rand
from utils import *
import pygame
from copy import deepcopy


FPS=3
WHITE=(255,255,255)
GREY=(169,169,169)
WIDTH=1200
HEIGHT=1000

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



class Wall(pygame.sprite.Sprite):

    def __init__(self,x,y):
        pygame.sprite.Sprite.__init__(self)
        self.image=pygame.Surface((100,100))
        self.image.fill(GREY)
        self.rect=self.image.get_rect()
        self.rect.x=x*100
        self.rect.y=y*100


class Egg(pygame.sprite.Sprite):
    def __init__(self,x,y,ori_pos=[0,0]):
        pygame.sprite.Sprite.__init__(self)
        self.image=pygame.image.load('image/egg.png')
        self.image=pygame.transform.scale(self.image,(100,100))
        self.rect=self.image.get_rect()
        self.rect.x=x*100
        self.rect.y=y*100
        self.ori_pos=ori_pos
    
    def update(self):

        if self.rect.right>WIDTH-100:
            self.rect.right=WIDTH-100
        if self.rect.left<100:
            self.rect.left=100
        if self.rect.top<100:
            self.rect.top=100
        if self.rect.bottom>HEIGHT-100:
            self.rect.bottom=HEIGHT-100
    

class Hole(pygame.sprite.Sprite):
    def __init__(self,x,y):
        pygame.sprite.Sprite.__init__(self)
        self.image=pygame.image.load('image/hole.png')
        self.image=pygame.transform.scale(self.image,(100,100))
        self.rect=self.image.get_rect()
        self.rect.x=x*100
        self.rect.y=y*100


class Complete(pygame.sprite.Sprite):
    def __init__(self,x,y):
        pygame.sprite.Sprite.__init__(self)
        self.image=pygame.image.load('image/hole_complete.png')
        self.image=pygame.transform.scale(self.image,(100,100))
        self.rect=self.image.get_rect()
        self.rect.x=x
        self.rect.y=y


class Finish(pygame.sprite.Sprite):
    def __init__(self):
        pygame.sprite.Sprite.__init__(self) 
        self.image=pygame.image.load('image/finish.jpeg')
        self.image=pygame.transform.scale(self.image,(500,500))
        self.rect=self.image.get_rect()
        self.rect.x=WIDTH/4
        self.rect.y=HEIGHT/4

if __name__ =="__main__":
    Solution=False
    while Solution is False:
        Solution=True
        q_egg=Queue()
        q_hole=Queue()
        sequence=[]
        map=Map()
        mapping=map.map_building()
        coordinate_list=map.get_coordinate(mapping)
        map.fill_coordinate(mapping,coordinate_list)
        for i in range (4,8):
            q_hole.push(coordinate_list[i])
        node=Node(mapping)
        p=Problem_solving(node.map)
        list_len=len(coordinate_list)
        distance_list=PriorityQueue(node)
        distance_list.pop()
        for i in range (4):
            min_val=99
            for j in range(4):
                len(coordinate_list)
                egg_x=coordinate_list[i][0]
                egg_y=coordinate_list[i][1]
                hole_x=coordinate_list[list_len-j-1][0]
                hole_y=coordinate_list[list_len-j-1][1]
                egg_hole_distance=abs(egg_x-hole_x)+abs(egg_y-hole_y)
                if min_val>(egg_hole_distance):
                    min_val=(egg_hole_distance)
            distance_list.push([min_val,i])
        egg_sequence=[]
        for i in range (4):
            value=distance_list.pop()
            q_egg.push(coordinate_list[value[1]])
            egg_sequence.append(value[1])

        for i in range (4):
            egg_coordinate=q_egg.pop()
            partial_map=map.make_partial(p.node.map,egg_coordinate)
            print(partial_map)
            q_action=Queue()
            q_log=Queue()
            log=[]
            p=Problem_solving(partial_map)
            q_log.push(p.node)
            while q_hole.find(egg_coordinate) is None:
                actions=p.action(egg_coordinate)
                for i in range (len(actions)):
                    if actions[i] not in log:
                        log.append(actions[i])
                        q_action.push(actions[i])
                while q_action.empty() is False:
                    destination=q_action.pop()
                    new_state=p.expand(p.node,egg_coordinate,destination)
                    q_log.push(new_state)
                if q_log.empty() is True:
                    Solution=False
                    break
                p.node=q_log.pop()
                egg_coordinate=p.get_egg()
            if Solution is False:
                break
            direction_path=p.node.path()
            sequence.append(direction_path)
            q_hole._items[q_hole.find(egg_coordinate)]=0

    pygame.init()
    screen=pygame.display.set_mode((WIDTH,HEIGHT))
    pygame.display.set_caption("鸡蛋")
    clock=pygame.time.Clock()


    all_sprites=pygame.sprite.Group()
    blocks=pygame.sprite.Group()
    eggs=pygame.sprite.Group()
    holes=pygame.sprite.Group()
    completed=pygame.sprite.Group()

    wall_coordinate=map.get_wall(mapping)
    for i in range((len(wall_coordinate))):
        wall=Wall(wall_coordinate[i][1],wall_coordinate[i][0])
        all_sprites.add(wall)
        blocks.add(wall)
    for i in range (4):
        egg=Egg(coordinate_list[i][1],coordinate_list[i][0])
        all_sprites.add(egg)
        eggs.add(egg)
    for i in range (4,8):
        hole=Hole(coordinate_list[i][1],coordinate_list[i][0])
        all_sprites.add(hole)
        holes.add(hole)



  
    running= True
    moving_num=0
    sequence_num=1
    while running:
        clock.tick(FPS)
        for event in pygame.event.get():
            if event.type==pygame.QUIT:
                running=False
        all_sprites.update()
        if moving_num<len(sequence):   
            if sequence_num==1:
                egg_coordinate=coordinate_list[egg_sequence[moving_num]]
                for entity in eggs:
                    if entity.rect.x==egg_coordinate[1]*100 and entity.rect.y==egg_coordinate[0]*100:
                        move_egg=entity    
            movement=sequence[moving_num][sequence_num]
            move=movement.direction
            move_egg.rect.x-=move[1]*100
            move_egg.rect.y-=move[0]*100
            if sequence_num<len(sequence[moving_num])-1:
                sequence_num+=1
            else:
                moving_num+=1
                sequence_num=1
        

        egg_hole_collide=pygame.sprite.groupcollide(eggs,holes,False,True)
        for hit in egg_hole_collide:
            for entity in eggs:
                if entity in egg_hole_collide:
                    collide_egg=entity
                    complete=Complete(collide_egg.rect.x,collide_egg.rect.y)
                    all_sprites.add(complete)
                    completed.add(complete)

        if len(completed)==4:
            finish=Finish()
            all_sprites.add(finish)

        screen.fill(WHITE)    
        all_sprites.draw(screen)
        pygame.display.update()
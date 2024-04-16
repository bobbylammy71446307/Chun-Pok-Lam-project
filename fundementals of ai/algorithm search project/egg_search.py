import numpy as np
import random as rand
from utils import *
import pygame
from copy import deepcopy
from search_function import *


FPS=3
WHITE=(255,255,255)
GREY=(169,169,169)
WIDTH=1200
HEIGHT=1000

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
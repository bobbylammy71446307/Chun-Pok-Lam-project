from filecmp import clear_cache
from hashlib import new
import numpy as np
from copy import deepcopy
from utils import *
import time

class Node(object):  # Represents a node in a search tree
    def __init__(self, state, parent=None, action=None, path_cost=0):
        self.state = state
        self.parent = parent
        self.action = action
        self.path_cost = path_cost
        self.depth = 0
        if parent:
            self.depth = parent.depth + 1

    def child_node(self, problem, action, empty_pos):
        next_state = problem.move(self.state, empty_pos, action)
        next_node = Node(next_state, self, action,
                            problem.g(self.path_cost, self.state,
                                    action, next_state))
        return next_node

    def path(self):
        """
        Returns list of nodes from this node to the root node
        """
        node, path_back = self, []
        while node:
            path_back.append(node)
            node = node.parent
        return list(reversed(path_back))


    def __repr__(self):
        return "<Node {}(g={})>".format(self.state, self.path_cost)

    def __lt__(self, other):
        return self.path_cost < other.path_cost
        
    def __eq__(self, other):
        return self.state == other.state


class Problem(object):
    def __init__(self, init_state=None, goal_state=None):
        self.init_state = Node(init_state)
        self.goal_state = Node(goal_state)

    def actions(self, state):
        """
        Given the current state, return valid actions.
        :param state:
        :return: valid actions
        """
        pass

    def move(self, state, action):
        pass

    def is_goal(self, state):
        pass

    def g(self, cost, from_state, action, to_state):
        return cost + 1

    def solution(self, goal):
        """
        Returns actions from this node to the root node
        """
        if goal.state is None:
            return None
        return [node.action for node in goal.path()[1:]]
    
    def expand(self, node):  # Returns a list of child nodes
        return [node.child_node(self, action, pos) for action, pos in self.actions(node.state)]
    

class GridsProblem(Problem):
    def __init__(self,
                 n,
                 init_state=[[1, 1, 1, 0], 
                             [2, 1, 1, 2], 
                             [2, 0, 1, 2], 
                             [1, 2, 2, 2]],
                 goal_state=[[1, 1, 1, 1], 
                             [1, 1, 1, 0], 
                             [2, 2, 2, 0], 
                             [2, 2, 2, 2]]):
        super().__init__(init_state, goal_state)
        self.n = n

    def is_valid(self, loc):
        if -1 < loc[0] < self.n and -1 < loc[1] < self.n:
            return True
        else:
            return False

    def actions(self, state):
        empty_index_list = np.argwhere(np.array(state) == 0)
        valid_candidates = []
        for empty_row, empty_col in empty_index_list:
            candidates = [[empty_row-1, empty_col], [empty_row+1, empty_col],
                        [empty_row, empty_col-1], [empty_row, empty_col+1]]
            valid_candidates += [[item, [empty_row, empty_col]] for item in candidates if self.is_valid(item)]
        return valid_candidates

    def move(self, state, empty_pos, action):
        new_state = deepcopy(state)
        new_state[empty_pos[0]][empty_pos[1]] = state[action[0]][action[1]]
        new_state[action[0]][action[1]] = 0
        return new_state

    def is_goal(self, state):
        return state == self.goal_state.state

    def g(self, cost, from_state, action, to_state):
        return cost + 1
    
def search_with_info(problem,node,node_back,result,result_back):
    print("有信息搜索：")
    start=time.time()                                                  #开始计时
    pq=PriorityQueue(node)                                             #设定从初始态开始搜索状态的优先队列
    pq_back=PriorityQueue(node_back)                                   #设定从目标态开始搜索状态的优先队列
    q=Queue()                                                          #设定从初始态开始搜索队列
    q.push(node.state)
    q_log=Queue()                                                      #设定从初始态开始搜索查考状态队列
    q_log.push(node.state)                                       
    q_back=Queue()                                                     #设定从目标态开始搜索队列
    q_back.push(node_back.state)
    while 1:
        for i in range(len(result)):                                   #处理从初始态开始搜索状态
            a=0
            new_state=result[i]                                        #依次输入发展节点
            if q.find(new_state.state) is not None:                    #跳过已发展节点
                continue    
            for j in range(4):                                         #判断当前节点与目标状态不一样位置的数量
                for k in range(4):
                    if new_state.state[j][k]!=problem.goal_state.state[j][k]:       
                        a+=1
            new_state.path_cost=a+new_state.depth                       #定义节点代价为对比数量以及发展深度的和
            pq.push(new_state)

        for ii in range (len(result_back)):                             #处理从目标态开始搜索状态
            aa=0
            back_state=result_back[ii]                                  #依次输入发展节点
            if q.find(back_state.state) is not None:                    #判断对比在另一搜索方向是否有已发展节点
                new_state=q_log._items[q.find(back_state.state)]        #获得另一方向的节点以及信息
                print("Goal Reached")
                print("depth is:",new_state.depth+back_state.depth)     #输出解的发展深度（步数）
                break
            elif q_back.find(back_state.state) is not None:             #跳过已发展节点
                continue
            for jj in range(4):                                         #判断当前节点与初始状态不一样位置的数量
                for kk in range(4):
                    if back_state.state[jj][kk]!=problem.init_state.state[jj][kk]:
                        aa+=1
            back_state.path_cost=aa+back_state.depth                    #定义节点代价为数量以及发展深度的和
            pq_back.push(back_state)
        if new_state.state==back_state.state:                           #判断当找到节点后
            alist=new_state.path()                                      #输出方向1搜索路径
            blist=back_state.path()                                     #输出方向2搜索路径
            blist.reverse()                                             #翻转列表2顺序
            for a in range(len(blist)):
                alist.append(blist[a])                                  #整合列表
            print(alist)                                                #输出整体搜索路径
            break
        node=pq.pop()                         
        node_back=pq_back.pop()
        while q.find(node.state) is not None:                           #当弹出已发展节点则重新弹出节点
            node=pq.pop()
        while q_back.find(node_back.state) is not None:                 #当弹出已发展节点则重新弹出节点
            node_back=pq_back.pop()
        q.push(node.state)
        q_back.push(node_back.state)
        q_log.push(node)
        result=problem.expand(node)                                     #发展节点
        result_back=problem.expand(node_back)                           #发展节点
    end=time.time()                                                     #结束计时
    print("Running time:",end-start)                                    #输出运行时间

def search_without_info(problem,node,node_back,result,result_back):
    print("无信息搜索：")
    start=time.time()                                                   #开始计时
    q=Queue()
    q_log=Queue()
    q_log.push(node.state)
    q_back=Queue()
    q_back_log=Queue()
    q_back_log.push(node_back.state)
    h=k=0
    while 1:
        for i in range(len(result)):                                    #分别对从初始状态发展态进行排查，若已发展则不会进入到队列里
            new_state=result[i]
            if q_log.find(new_state.state) is None:
                q.push(new_state)
                q_log.push(new_state.state)
        for j in range(len(result_back)):                                #分别对从结果状态发展态进行排查，若已发展则不会进入到队列里
            back_state=result_back[j]
            if q_back_log.find(back_state.state) is None:
                q_back.push(back_state)
                q_back_log.push(back_state.state)
            if  q_log.find(back_state.state) is not None:                #查找从初始状态发展态中是否有相同发展态
                k=q_log.find(back_state.state)
                new_state=q._items[k-1]
                break
        if k!=0:
            print("Goal Reached")
            print("Depth is:",new_state.depth+back_state.depth)
            alist=new_state.path()                                       #输出两个方向的路径
            blist=back_state.path()
            blist.reverse()  
            for a in range(len(blist)):                                  #调整代价顺序并整合列表
                node=blist[a]
                node.path_cost=a+new_state.path_cost
                blist[a]=node
                alist.append(blist[a])                                   
            print(alist)
            break
        h+=1
        node=q._items[h]
        node_back=q_back.pop()
        result=problem.expand(node)                                     #发展节点
        result_back=problem.expand(node_back)                            
    end=time.time()                                                     #结束计时
    print("Running time:",end-start)                                    #输出运行时间

if __name__ == "__main__":
    problem = GridsProblem(4)
    node_init = Node(state=[[1, 1, 1, 0], 
                            [2, 1, 1, 2], 
                            [2, 0, 1, 2], 
                            [1, 2, 2, 2]])
    node_goal = Node(state=[[1, 1, 1, 1], 
                            [1, 1, 1, 0], 
                            [2, 2, 2, 0], 
                            [2, 2, 2, 2]])
    print("请分别使用有信息和无信息搜索方法求解单车整理问题。")
    search_with_info(problem,node_init,node_goal,problem.expand(node_init),problem.expand(node_goal))
    search_without_info(problem,node_init,node_goal,problem.expand(node_init),problem.expand(node_goal))
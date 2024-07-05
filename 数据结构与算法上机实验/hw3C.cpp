#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;
struct nodeGraph
{
    int val;
    nodeGraph *next;

    nodeGraph(int val)
    {
        this->val = val;
        next = nullptr;
    }
};
struct headGraph
{
    nodeGraph *head;
    nodeGraph *tail;

    headGraph()
    {
        head = new nodeGraph(INT16_MAX);
        tail = new nodeGraph(0); 
        head->next = tail;

    }
};
// 头节点的向量
vector<headGraph> v(20001);
// 记录是否遍历
vector<int> visited(20001, 0);



void DFS(int toVisit)
{   
    // 不断遍历
    vector<int> toVisitVec;
    if(visited[toVisit] == 0)
    {
        visited[toVisit] = 1;
        cout << toVisit << " ";
        nodeGraph * p = v[toVisit].head->next;
        while(p!= v[toVisit].tail)
        {
            toVisitVec.push_back(p->val);
            p = p->next;
        }

        sort(toVisitVec.begin(), toVisitVec.end());

        for(int i = 0; i < toVisitVec.size(); i++)
        {
            DFS(toVisitVec[i]);
        }
    }
}



int main()      
{
    int n, e;
    cin >> n >> e;
    

    // 建图
    for(int i = 0; i < e; i++)
    {
        int a, b;
        cin >> a >> b;
        
        nodeGraph * insertPointer = v[a].head;
        nodeGraph * p = new nodeGraph(b);
        p->next = insertPointer->next;
        insertPointer->next = p; 

    }
    //从0开始遍历
    for(int i = 0; i < n; i++)
    {
        DFS(i);
    }

    
    return 0;
}
/*
C 图深度优先遍历
分数 10
作者 朱允刚
单位 吉林大学
编写程序对给定的有向图（不一定连通）进行深度优先遍历，图中包含n个顶点，编号为0至n-1。本题限定在深度优先遍历过程中，如果同时出现多个待访问的顶点，则优先选择编号最小的一个进行访问，以顶点0为遍历起点。

输入格式:
输入第一行为两个整数n和e，分别表示图的顶点数和边数，其中n不超过20000，e不超过50。接下来e行表示每条边的信息，每行为两个整数a、b，表示该边的端点编号，但各边并非按端点编号顺序排列。

输出格式:
输出为一行整数，每个整数后一个空格，即该有向图的深度优先遍历结点序列。

输入样例1:
3 3
0 1
1 2
0 2
输出样例1:
0 1 2 
输入样例2:
4 4
0 2
0 1
1 2
3 0
输出样例2:
0 1 2 3 
代码长度限制
16 KB
时间限制
50 ms
内存限制
64 MB
*/
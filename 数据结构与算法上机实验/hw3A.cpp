#include <iostream>
#include <vector>

using namespace std;
struct nodeGraph// 邻接表节点
{
    int point;
    int val;
    nodeGraph *next;

    nodeGraph(int point, int val)
    {
        this->point = point;
        this->val = val;
        next = nullptr;
    }
};
struct headGraph// 邻接表头
{
    nodeGraph *head;
    nodeGraph *tail;

    headGraph()
    {
        head = new nodeGraph(INT8_MAX, 0);
        tail = new nodeGraph(INT8_MAX, 0); 
        head->next = tail;

    }
};




int main()      
{
    int n, e;
    cin >> n >> e;
    vector<headGraph> v(n + 1);

    for(int i = 0; i < e; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;

        nodeGraph * insertPointer = v[a].head->next;
        nodeGraph * p = v[a].head;
        while(true)
        {
            if(insertPointer->point < b && insertPointer != v[a].tail)
            {
                insertPointer = insertPointer->next;
                p = p->next;
            }
            else
            {
                insertPointer = new nodeGraph(b, c);
                insertPointer->next = p->next;
                p->next = insertPointer;
                break;
            }
        }
        
    }

    for(int i = 0; i < n; i++)
    {
        int sum = 0;
        nodeGraph *temp = v[i].head->next;
        bool flag = false;
        if(temp != v[i].tail)
        {
            cout << i << ":";
            flag = true;
        }
        while(temp!= v[i].tail)
        {
            cout << "(" << i << "," << temp->point << "," << temp->val << ")";
            temp = temp->next;   
        }
        if(flag)
            cout << endl;
    }
    return 0;
}
/*
A 图的创建
分数 10
作者 朱允刚
单位 吉林大学
请编写程序创建一个有向图。有向图中包含n个顶点，编号为0至n-1。

输入格式:
输入第一行为两个正整数n和e，分别表示图的顶点数和边数，其中n不超过20000，e不超过20000。接下来e行表示每条边的信息，每行为3个非负整数a、b、c，其中a和b表示该边的端点编号，c表示权值。各边并非按端点编号顺序排列。

输出格式:
按顶点编号递增顺序输出每个顶点引出的边，每个顶点占一行，若某顶点没有引出边，则不输出。每行表示一个顶点引出的所有边，格式为a:(a,b,w)……，表示有向边a->b的权值为w，a引出的多条边按编号b的递增序排列。

输入样例:
7 7
0 1 5
0 3 7
0 6 6
1 2 4
2 5 1
3 5 3
6 5 4

输出样例:
0:(0,1,5)(0,3,7)(0,6,6)
1:(1,2,4)
2:(2,5,1)
3:(3,5,3)
6:(6,5,4)

代码长度限制
16 KB
时间限制
500 ms
内存限制
20 MB
*/
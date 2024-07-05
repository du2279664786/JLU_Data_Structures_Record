#include <iostream>
#include <vector>

using namespace std;
struct nodeGraph
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
struct headGraph
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

    for(int i = 0; i < e; i++)//建图
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

    int k;
    cin >> k;
    for(int i = 0; i < k; i++)// 删边
    {
        int a, b;
        cin >> a >> b;
        nodeGraph * pointerDelete = v[a].head->next;
        nodeGraph * p = v[a].head;
        while(true)
        {
            if(pointerDelete->point == b)
            {
                p->next = pointerDelete->next;
                delete pointerDelete;
                break;
            }
            else
                p = p->next;
                pointerDelete = pointerDelete->next;
            }
    }

    for(int i = 0; i < n; i++)// 遍历输出
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
B 图的删边操作
分数 10
作者 朱允刚
单位 吉林大学
请编写程序对给定的有向图删除若干条边。有向图中包含n个顶点，编号为0至n-1。

输入格式:
输入第一行为两个正整数n和e，分别表示图的顶点数和边数，其中n不超过20000，e不超过1000。接下来e行表示每条边的信息，每行为3个非负整数a、b、c，其中a和b表示该边的端点编号，c表示权值。各边并非按端点编号顺序排列。随后一行为一个整数k，表示删除的边的条数，接下来k行，每行为2个非负整数a、b，表示待删除的边为a->b。保证删除的边一定在原图中。

输出格式:
输出执行删边操作之后的图。每行表示一个顶点引出的所有边，格式为a:(a,b,w)……，表示有向边a->b的权值为w，a引出的多条边按编号b的递增序排列。若某顶点没有引出边，则不输出。

输入样例:
7 7
0 1 5
0 3 7
0 6 6
1 2 4
2 5 1
3 5 3
6 5 4
2
2 5
0 1

输出样例:
0:(0,3,7)(0,6,6)
1:(1,2,4)
3:(3,5,3)
6:(6,5,4)

代码长度限制
16 KB
时间限制
200 ms
内存限制
64 MB
*/
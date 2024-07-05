#include <iostream>
#include <vector>


using namespace std;

struct node{
    int point;
    int val;
    node *next;
    node(int point, int val) : point(point), val(val), next(NULL) {}
    node() : next(nullptr){}
};




int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    // 输入点数和边数
    int n, e;
    cin >> n >> e;

    // 构造个点头
    vector<node*> head(n, nullptr);
    vector<int> dist(n, INT16_MAX); // 记录源点到个点最短长度，若无则定位无限大
    vector<int> visited(n, 0); // 记录点是否被访问过

    // 邻接表初始化
    for(int i = 0; i < n; i++)
    {
        head[i] = new node();
        head[i]->point = i;
        head[i]->val = 0;
    }
    
    
    // 输入边值
    for(int i = 0; i < e; i++)
    {
        int a, b, c;
        // 分别是出发点，终点和权值
        cin >> a >> b >> c;
        node * p = new node(b, c);
        // 插到尾
        node * q = head[a];
        while(q->next!= nullptr)
        {
            q = q->next;
        }
        q->next = p;
    }

    // 迪杰斯特拉算法
    node * p = head[0];// 正要访问的点
    dist[0] = 0;
    visited[0] = 1;
    for(int i = 1; i < n; i++)
    {
        
        
        for(auto j = p->next; j!= nullptr; j = j->next)
        {
            // 当当前点未被访问过且（上个点到原点距离+上个点到当前点距离）小于之前记录的最小距离
            if(visited[j->point] == 0 && j->val + dist[p->point] < dist[j->point])
            {
                dist[j->point] = j->val + dist[p->point];
            }
        }

        int minDist = INT16_MAX; // 本次遍历的最小距离
        int minDistIndex;
        // 放松点的距离，并判断是否为本次遍历的最小距离
        for(int j = 0; j < dist.size(); j++)
            if(dist[j] < minDist && visited[j] == 0)
            {
                minDistIndex = j;
                minDist = dist[j];
            }

        visited[minDistIndex] = 1;

        p = head[minDistIndex];
        
    }
    
    for(int i = 1; i < n; i++)
    {
        if(dist[i] == INT16_MAX)
        {
            continue;
        }
        cout << dist[i] << " ";
    }

    return 0;
}
/*
D 单源最短路径
分数 30
作者 朱允刚
单位 吉林大学
请编写程序求给定正权有向图的单源最短路径长度。图中包含n个顶点，编号为0至n-1，以顶点0作为源点。

输入格式:
输入第一行为两个正整数n和e，分别表示图的顶点数和边数，其中n不超过20000，e不超过1000。接下来e行表示每条边的信息，每行为3个非负整数a、b、c，其中a和b表示该边的端点编号，c表示权值。各边并非按端点编号顺序排列。

输出格式:
输出为一行整数，为按顶点编号顺序排列的源点0到各顶点的最短路径长度（不含源点到源点），每个整数后一个空格。如源点到某顶点无最短路径，则不输出该条路径长度。

输入样例:
4 4
0 1 1
0 3 1
1 3 1
2 0 1
输出样例:
1 1 
代码长度限制
16 KB
时间限制
100 ms
内存限制
20 MB
*/
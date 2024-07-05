#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct node{// 点的名字和时间
    int name;
    int time;

    node(int n, int t) : name(n), time(t) {}
};

struct event{// 活动路径
    int from;
    int to;

    event(int a, int b) : from(a), to(b) {}
};

int main()
{
    int n, e;//点数 和 边数
    while(cin >> n >> e)
    {
        
        vector<vector<node *>> dist;// 邻接点
        vector<int> inDegree;// 入度
        vector<int> outDegree;// 出度
        vector<int> topOder;// 拓扑排序
        vector<int> latesTime;// 最晚完成时间
        vector<int> earliestTime;// 最早完成时间

        topOder.push_back(0);// 对齐坐标

        for(int i = 0; i < n + 1; i++)
        {
            dist.push_back(vector<node*>());
            inDegree.push_back(0);
            outDegree.push_back(0);
            latesTime.push_back(INT32_MAX);
            earliestTime.push_back(0);
        }

        for(int i = 0; i < e; i++)// 初始化邻接表
        {
            int a,b, c;
            cin >> a >> b >> c;
            node * p = new node(b, c);
            dist[a].push_back(p);
            inDegree[b]++;
            outDegree[a]++;
        }

        // 拓扑排序
        vector<int> waitToVisit;

        // 初始化入度0的点
        for(int i = 1;i < n + 1; i++)
        {
            if(inDegree[i] == 0)
            {
                waitToVisit.push_back(i);
                break;
            }
        }

        vector<int> tmpInDegree = inDegree;//替代下
        int cnt = 0;
        while(waitToVisit.size() > 0)
        {
            int v = waitToVisit[0];
            waitToVisit.erase(waitToVisit.begin());
            topOder.push_back(v);
            cnt++;

            // 遍历该点的邻接点，入度减一
            for(auto it : dist[v])
            {
                if(--tmpInDegree[it->name] == 0)
                {
                    waitToVisit.push_back(it->name);
                }
            }

            sort(waitToVisit.begin(), waitToVisit.end());
        }

        if(cnt != n)
        {
            cout << "unworkable project" << endl;
            continue;
        }

        // 计算最早完成时间和最晚完成时间
        for(auto v : topOder)
        {
            
            for(auto it : dist[v])
            {
                earliestTime[it->name] = max(earliestTime[it->name], earliestTime[v] + it->time);
            }
        }
        // 最迟
        int endIndex = topOder[n];
        for(int i = 1; i < n + 1; i++)
        {
            latesTime[i] = earliestTime[endIndex];
        }

        for(int i = n; i >= 0; i--)
        {
            for(auto it : dist[topOder[i]])
            {
                if(latesTime[topOder[i]] > latesTime[it->name] - it->time)
                {
                    latesTime[topOder[i]] = latesTime[it->name] - it->time;
                }
            }
        }

        // 从拓扑排序顺序输出总时间与点
        vector<event> keyWay;
        
        for(int i = 1; i < n + 1; i++)
        {
            for(auto v : dist[i])
            {
                if(earliestTime[i] == latesTime[v->name] - v->time)
                {
                    keyWay.push_back(event(i, v->name));
                }
            }
        }

        cout << latesTime[topOder[n]] << endl;

        for(int i = 0; i < keyWay.size(); i++)
        {
            cout << keyWay[i].from << "->" << keyWay[i].to << endl;
        }
    }


    return 0;
}

/*
G 关键路径
分数 30
作者 朱允刚
单位 吉林大学
假定一个工程由若干子任务构成，使用一个包含n个顶点、e条边的AOE网表示该工程，顶点编号为1至n，有向边表示该工程的每个子任务，边的权值表示完成该子任务所需的时间，假定网中只含一个源点和一个汇点。请编写程序求出该工程的所有关键活动，并计算完成该工程所需的最短时间。

输入格式:
每个测试点包含多组测试数据。每组数据第一行为2个整数n和e，均不超过200，分别表示AOE网的顶点数和边数。接下来e行表示每条边的信息，每行为3个正整数a、b、c，其中a和b表示该边的端点编号，c表示权值。各边并不一定按端点编号顺序排列，且各顶点并不一定按拓扑序排列。

输出格式:
对每组数据，若工程不可行（AOE网中存在环），输出“unworkable project”；若工程可行，则输出第一行为完成工程所需的最短时间，并从第2行开始输出关键活动，每个关键活动占一行，格式为i->j，其中i和j表示关键活动所在边的端点编号。各关键活动输出顺序为：按i的递增顺序输出，若多个关键活动的i值相同，则按j的递增顺序输出。

输入样例:
4 4
1 2 6
1 3 4
2 4 1
3 4 1

输出样例:
7
1->2
2->4

代码长度限制
16 KB
时间限制
100 ms
内存限制
64 MB
*/

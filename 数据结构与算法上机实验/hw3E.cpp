#include <iostream>

using namespace std;

int main()
{
    int n, e; // n为城市数， e为距离信息个数
    while(cin >> n >> e)
    {
        int edge[n][n] = {INT32_MAX};
        int path[n][n] = {-1};

        // 初始化邻接矩阵

        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                if(i == j)
                    edge[i][j] = 0;
                else
                    edge[i][j] = INT32_MAX;
            }
        }

        for(int i = 0; i < e; i++)
        {
            int a, b, c;// ab为城市编号，c为距离
            cin >> a >> b >> c;
            edge[a][b] = c;
            edge[b][a] = c;

            path[a][b] = a * (b - 1);
        }

        

        

        // 求每对顶点最短路径并记录最小值对应的顶点
        for(int k = 0; k < n; k++)
        {
            for(int i = 0; i < n; i++)
            {
                if(i != k)
                {
                    for(int j = 0; j < n; j++)
                    {
                        if(j != k && j != i
                        && edge[i][k] < INT32_MAX
                        && edge[k][j] < INT32_MAX
                        && edge[i][k] + edge[k][j] < edge[i][j])
                        {
                            edge[i][j] = edge[i][k] + edge[k][j];
                            path[i][j] = path[k][j];
                        }
                    }
                }
            }
        }
        int minDistSum = INT32_MAX;
        int minIndex = 0;
        // 算最短距离和
        for(int i = 0; i < n; i++)
        {
            int tmpSum = 0;
            for(int j = 0; j < n; j++)
            {
                if(edge[i][j] != INT32_MAX)
                {
                    tmpSum += edge[i][j];
                }
            }
            if(tmpSum < minDistSum)
            {
                minIndex = i;
                minDistSum = tmpSum;
            }
        }
        cout << minIndex << endl;

    }
        



    return 0;
}


/*
E 双十一
分数 20
作者 朱允刚
单位 吉林大学
双十一期间，某著名电商平台“东东”为应对销售高峰，准备在n个城市中再增加一个自营仓库，其要求是该仓库设在n个城市中的某个城市，且距离其他所有城市的最短距离之和最小。请编写程序帮助“东东”找出设立仓库的地点。假定n个城市编号为0至n-1，它们之间至少有一个城市与其他所有城市可及。

输入格式:
输入包含多组数据。每组数据第一行为两个正整数n和e，均不超过100。n表示城市数。接下来e行表示两个城市间的距离信息，每行为3个非负整数a、b、c，其中a和b表示两个城市编号，c表示城市间的距离。

提示：可使用EOF判断输入结束。

输出格式:
输出为一个整数，表示建立仓库的城市编号，如多个城市满足要求，则输出编号最小者。

输入样例:
6 5
0 1 1
0 2 1
0 3 1
0 4 1
0 5 1
4 5
0 1 1
0 2 5
1 2 2
1 3 4
2 3 1

输出样例:
0
1

代码长度限制
16 KB
时间限制
50 ms
内存限制
64 MB
*/
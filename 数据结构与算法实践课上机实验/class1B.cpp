#include <iostream>
#include <vector>

using namespace std;



int main()
{
    // 提速
	ios::sync_with_stdio(false);
	cin.tie(NULL);
    cout.tie(NULL);
    int n, e, a, b, c;//存放题目的点数，边数， 点的起点，终点，权值
    cin >> n >> e;
    long long D[101][101];//路径距离
    long long minWay[101][101];//点之间最短路径数量
    double effect[101];

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= n; j++)
        {
            if(i == j)
                D[i][j] = 0;
            else
                D[i][j] = INT32_MAX;
            minWay[i][j] = 0;
        }
        effect[i] = 0;
    }

    for(int i = 0; i < e; i++)
    {
        cin >> a >> b >> c;
        D[a][b] = c;
        D[b][a] = c;

        minWay[a][b] = 1;
        minWay[b][a] = 1;
    }

    // Floyd
    for(int k = 1; k <= n; k++)
    {
        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= n; j++)
            {
                if(D[i][k] < INT32_MAX && D[k][j] < INT32_MAX)
                {
                    if(D[i][k] + D[k][j] < D[i][j])
                    {
                        D[i][j] = D[i][k] + D[k][j];
                        minWay[i][j] = minWay[i][k] * minWay[k][j];//重新更新为其两最短路径分段之积
                    }
                    else if(D[i][k] + D[k][j] == D[i][j] && i != k && j != k && i != j)
                    {
                        minWay[i][j] += minWay[i][k] * minWay[k][j];
                    }
                }
                
            }
        }
    }

    // 计算权值
    for(int k = 1; k <= n; k++)
    {
        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= n; j++)
            {
                if(D[i][k] + D[k][j] == D[i][j] && i != k && j != k && i != j)// 说明k在i和j的最短路径上
                {
                    effect[k] += 1.0 * D[i][j] * minWay[i][k] * minWay[k][j] / minWay[i][j];
                    
                    //cout << k << "+=" << D[i][j] << "*" << minWay[i][k] << "*" << minWay[k][j] << "/" << minWay[i][j] << endl; 
                }
            }
        }
    }

    // output result

    for(int i = 1; i <= n; i++)
    {
        printf("%.3f\n", effect[i]);
    }

    return 0;
}

/*
B 社交网络
分数 50
作者 朱允刚
单位 吉林大学
可以将n个QQ用户间的好友关系建模为一个包含n个顶点的无向图，顶点编号为1至n，每个顶点对应一个用户，若2个用户i和j是QQ好友，则在顶点i和j之间连接一条边，并根据用户间的亲密度对该边附以一个权值c 
ij。在该图中，可以利用两个顶点间的最短路径长度衡量两个用户的关系密切程度，也可以利用经过一个顶点的最短路径数目来衡量一个用户在关系网络中的影响力，具体地，我们定义用户k在QQ关系网络中的“影响力”为：

333.png

其中Nij 为顶点i到j的最短路径数目，Nijk 为顶点i到j的所有最短路径中经过顶点k的最短路径数目（上述二值可能超出int型范围，请使用long long类型）。Dij 表示i到j的最短路径长度。

现给定一个如上描述的无向图，请编写程序，计算每个顶点的“影响力”，假定给定的图是连通的。

输入格式:
输入第一行为两个正整数n和e，分别表示图的顶点数和边数，接下来e行表示每条边的信息，每行为3个正整数a、b、c，其中a和b表示该边的端点编号，c表示权值。各边并非按端点编号顺序排列。

n≤100，e≤5000，c≤1000，任意两点间的最短路径数目≤10 
10
 

输出格式:
输出为n行，每行一个实数，精确到小数点后3位，第i行为顶点i的影响力。

输入样例:
4 4
3 2 6
4 3 1
1 3 9
4 1 1

输出样例:
0.000
0.000
30.000
20.000

解释:
对于顶点1：边2-3、3-4、2-4的最短路径均不经过顶点1，故顶点1的影响力为0.

对于顶点3：
顶点1到2的最短路径共1条，长度为8，经过点3，顶点2到4的最短路径共1条，长度为7，经过点3，顶点1到4的最短路径共1条，但不经过点3。
故f(3)=D 12 ∗1+D 24 ∗1+D 14 ∗0+D 21 ∗1+D 42 ∗1+D 41 ∗0=8+7+0+8+7+0=30.000

提示:
若顶点a到顶点b有x条路径，点b到点c有y条路径，则a经过b到达c的路径有x*y条。

代码长度限制
16 KB
时间限制
50 ms
内存限制
64 MB
栈限制
8192 KB
*/
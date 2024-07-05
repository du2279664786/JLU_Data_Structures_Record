#include <iostream>
#include <vector>

using namespace std;

int n; // 公司数目
void warShall(vector<vector<int>>& WSM)
{
    for(int k = 1; k < n + 1; k++)
    {
        for(int i = 1; i < n + 1; i++)
        {
            if(WSM[i][k] == 1)
            {
                for(int j = 1; j < n + 1; j++)
                {
                    WSM[i][j] = WSM[i][j] || WSM[k][j];
                }
            }
        }
    }

}

void allComponet(vector<vector<int>> &WSM)
{
    warShall(WSM);

    vector<int> markedList(n + 1, 0);// 记录已经处理的点
    vector<int> scList; // 一个连通分量

    int t = 0;// 连通分量个数

    for(int v = 1; v < n + 1; v++)
    {
        if(markedList[v] == 0)
        {
            t++;// 处理新的连通分量
            markedList[v] = 1;
            scList.push_back(v);
            for(int i = 1; i < n + 1; i++)
            {
                if(i != v && WSM[v][i] == 1
                && WSM[i][v] == 1)
                {
                    markedList[i] = 1;
                    scList.push_back(i);
                }
            }

        }
    }
    cout << t << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int T;// 组数
    cin >> T;

    for(int i = 0; i < T; i++)
    {
        cin >> n;
        int graph[n + 1][n + 1] = {0};
        vector<vector<int>> WSM(n + 1,vector<int>(n + 1));

        for(int i = 0; i < n + 1; i++)
        {
            for(int j = 0; j < n + 1; j++)
            {
                graph[i][j] = 0;
                WSM[i][j] = 0;
            }
        }

        for(int j = 1; j < n + 1; j++)
        {
            int num;// 分发公司标号，为0结束
            cin >> num;
            while(num != 0)
            {
                graph[j][num] = 1;
                WSM[j][num] = 1;
                cin >> num;
            }
        }

        // 对角线为1
        for(int j = 0; j < n + 1; j++)
        {
            WSM[j][j] = 1;
        }

        

        allComponet(WSM);

    }



    return 0;
}
/*
H 联盟数目
分数 20
作者 朱允刚
单位 吉林大学
艾迪是一家集团公司的老板，该集团包含n家公司，为了管理公司，艾迪会时常通过网络向各公司发送消息。各公司间的网络是单向的，每个公司都有一个分发列表，表示其能向哪些公司直接传达消息。例如A公司的分发列表为B、C，表示A可将消息直接传送给B和C（由于网络是单向的，B或C不一定能向A传送消息），这样艾迪若想向A、B、C公司发送消息，则只需向A发送消息即可，随后A可将消息传送到B和C。

为了便于管理各公司，艾迪打算将n家公司分成若干组，每组称为一个区域联盟，每组满足如下条件：组内的任意公司消息互相可达。即对于组内任意公司u和v，u可将消息传送到v（可由u直接传送到v，也可通过组内其他公司中转传送到v），v也可将消息传送到u。可以认为一个公司可以将消息传送给自己，即一个公司可以自成一组。

艾迪希望组的数量尽可能少，即在满足上述条件的情况下，每组包含的公司数目尽可能多。

现给定每个公司的分发列表，请编写程序告知艾迪，他的集团最少能分成多少组。

输入格式:
第一行包含一个整数T (1≤T≤100)表示数据组数。对于每组数据，第一行为一个整数n (2≤n≤100)，表示公司数目，公司编号为1到n。随后n行，第i行包含若干整数，表示第i个公司的分发列表，每行以0结尾。

输出格式:
对于每组数据，输出一行，为一个整数，表示组数。

输入样例:
3
5
2 4 3 0
4 5 0
0
0
1 0
3
2 0
0
2 1 0
3
2 0
3 0
0

输出样例:
3
3
3

代码长度限制
16 KB
时间限制
100 ms
内存限制
64 MB
*/
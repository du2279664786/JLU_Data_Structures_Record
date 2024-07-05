#include <iostream>
#include <vector>


using namespace std;

vector<int> v;

int searchHead(int num)// 储存上一个关联的坐标
{
    if(v[num] == num)
    {
        return num;
    }
    
    return v[num] = searchHead(v[num]);
}



int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    

    int T;
    cin >> T;

    for(int i = 0; i < T; i++)
    {
        int n, m;
        cin >> n >> m;
        v.clear();
        for(int j = 0; j < n + 1; j++)
        {
            v.push_back(j);
        }

        for(int j = 0; j < m; j++)
        {
            int x, y;
            cin >> x >> y;
            // 把x所在列放y上
            // x可能无衣架
            // x可能与y同列
            if(x == y)
            {
                continue;
            }

            int tailX = x, tailY = y;

            tailX = searchHead(x);
            tailY = searchHead(y);

            if(tailX == tailY)
            {
                continue;
            }

            v[tailX] = v[tailY];
            
        }
        

        

        for(int j = 1; j < v.size(); j++)
            {
                cout << searchHead(j) << " ";
            }
            cout << endl;
        }
    

    return 0;
}
/*
H 衣服挂游戏
分数 20
作者 朱允刚
单位 吉林大学
有n个衣服挂，编号为1至n，初始时按顺序挂在一个晾衣杆上，每个衣挂自成一列（即相当于有n列，每列只含一个衣挂）。

1.jpg

爸爸让艾迪做如下操作“x y”，表示将衣挂x所在的列放在衣挂y所在的列下面，即把x所在列的第一个衣挂，挂在y所在列的最下面的衣挂下面，如果x和y已在同一列里，则忽略该操作。例如上图执行操作“3 5”后，得到下图：

2.jpg

再执行操作“3 2”后，得到下图：

3.jpg

爸爸给出一系列指令，请编写程序，输出艾迪完成爸爸的所有操作后，每个衣挂所在的列的第一个衣挂的编号。

输入格式:
每个测试点包含多组测试数据，第一行1个整数 T ，表示测试数据组数。对于每组数据，第一行两个整数 n 和 m，分别表示衣挂个数和操作次数。接下来 m 行，每行两个整数x和y，表示爸爸让艾迪执行的一个操作。T≤5，1≤n, m≤30000，1≤x, y≤n。

输出格式:
输出为T 行，每行为 n个整数a1 a2 … an ，每个整数后一个空格，ai(1≤i≤n)表示衣挂i所在列的第一个衣挂的编号。

输入样例:
2
4 2
2 1
4 3
5 4
1 2
2 3
4 5
1 3


输出样例:
1 1 3 3 
3 3 3 5 5 

代码长度限制
16 KB
时间限制
80 ms
内存限制
64 MB
*/
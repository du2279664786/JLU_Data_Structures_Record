#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

vector<vector<int>> outDegree;// 邻接点
vector<int> inDegree;// 入度
vector<int> topOder;

int n , e;// 点数 边数

bool compare(int a, int b)
{
    return a > b;
}

void TopSort()
{
    vector<int> stack;

    // 初始化入度0的点
    for(int i = 0;i < n; i++)
    {
        if(inDegree[i] == 0)
        {
            stack.push_back(i);
        }
    }

    sort(stack.begin(), stack.end(), compare);

    // 记录排序结果个数
    int cnt = 0;

    while(stack.size() > 0)
    {
        int v = stack[stack.size() - 1];
        stack.erase(stack.end() - 1);
        cnt++;
        // 取点并加入结果列中
        topOder.push_back(v);


        // 遍历该点的邻接点，入度减一
        for(auto it : outDegree[v])
        {
            if(--inDegree[it] == 0)
            {
                stack.push_back(it);
                
            }
        }

        sort(stack.begin(), stack.end(), compare);
    }

    if(cnt != n)
    {
        cout << "unworkable project";
    }
    else
    {
        for(auto it : topOder)
        {
            cout << it << " ";
        }
    }
    return;
}

int main()
{
    cin >> n >> e;

    outDegree.resize(n);
    inDegree.resize(n);

    for(int i = 0; i < e; i++)
    {
        int a ,b;
        cin >> a >> b;
        inDegree[b]++;
        outDegree[a].push_back(b);
    }

    TopSort();

    return 0;
}

/*
F 任务拓扑排序
分数 30
作者 朱允刚
单位 吉林大学
一个工程被分解成n个子任务，编号为0至n-1。要完成整个工程需要完成所有的子任务。其中一些子任务必须先于另外一些子任务被完成。给定各子任务之间的先后关系，请编写程序给出一个合理的任务完成顺序，若工程不可行，程序亦能识别。

输入格式:
输入第一行为两个整数n和e，均不超过100。n表示子任务数。接下来e行，表示已知的两个子任务间的先后关系，每行为两个整数a和b，表示任务a必须先于任务b完成。

输出格式:
若工程不可行（一些子任务以自己为先决条件），输出“unworkable project”；若工程可行，输出为1行整数，每个整数后一个空格，为n个子任务的编号，表示子任务的完成顺序，如果有多种可能的顺序，则输出字典序最小者。

注：字典序，即对象在字典中的顺序。对于两个数字序列，从第一个数字开始比较，当某一个位置的数字不同时，该位置数字较小的序列，字典序较小，例如1 2 3 9比1 2 4 5小，1 2 8 9比1 2 10 3小。

输入样例1:
3 2
0 1
1 2
输出样例1:
0 1 2 
输入样例2:
3 3
0 1
1 2
2 0
输出样例2:
unworkable project
代码长度限制
16 KB
时间限制
50 ms
内存限制
64 MB
*/
#include <iostream>
#include <vector>

using namespace std;

typedef struct treeNode
{
    int val;
    treeNode * left;
    treeNode * right;
    treeNode(int num) : val(num), left(nullptr), right(nullptr){};
}treeNode;

treeNode * head = nullptr;
int maxSum = INT8_MIN;
int tmpSum = 0;
vector<int> way;
vector<int> maxWay;

void createTree(treeNode * & p)// 创建二叉树
{
    int val;
    cin >> val;
    if(val == 0)
    {
        return;
    }
    else
    {
        p = new treeNode(val);
        createTree(p->left);
        createTree(p->right);
    }
}

void DFS(treeNode * p)// 深度优先遍历
{
    if(p == nullptr)
    {
        if(tmpSum > maxSum)
        {
            maxSum = tmpSum;
            maxWay = way;
        }
        return;
    }
    way.push_back(p->val);
    tmpSum += p->val;
    DFS(p->left);
    DFS(p->right);
    tmpSum -= p->val;
    way.pop_back();
    
}

int main()
{
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);
    
    createTree(head);

    DFS(head);
    cout << maxSum << endl;
    for(int i = 0; i < maxWay.size(); i++)
    {
        cout << maxWay[i] << " ";
    }
    
    return 0;
}
/*
E 二叉树路径和
分数 20
作者 朱允刚
单位 吉林大学
编写程序找出二叉树中和最大的路径，二叉树结点为不等于0的整数。本题的“路径”限定为以根结点为起点，以叶结点为终点的路径。路径的和，即该路径所包含的所有结点的数据值之和。

输入格式:
输入为一组用空格间隔的整数，个数不超过100个，表示带空指针信息的二叉树先根序列。

输出格式:
输出为两行，第一行为该二叉树路径和的最大值，第二行为一组整数，每个整数后一个空格，即该最大路径包含的结点值（按从根的叶的顺序），如果存在多条满足条件路径，则输出最左边一条。

输入样例1:
1 2 0 0 3 0 0
输出样例1:
4
1 3 
输入样例2:
-1 2 0 0 3 0 0
输出样例2:
2
-1 3 
代码长度限制
16 KB
时间限制
50 ms
内存限制
64 MB
*/
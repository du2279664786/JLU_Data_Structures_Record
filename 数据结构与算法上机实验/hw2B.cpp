#include <iostream>

using namespace std;

typedef struct treeNode
{
    int val;
    treeNode * left;
    treeNode * right;
    treeNode(int num) : val(num), left(nullptr), right(nullptr){};
}treeNode;

treeNode * head = nullptr;
bool existFlag = false;

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

void searchParent(treeNode * p, int num)// 查找父结点
{
    if(p == nullptr)
    {
        return;
    }

    if((p->left != nullptr && p->left->val == num) || 
        (p->right != nullptr && p->right->val == num))
    {
        cout << p->val << endl;
        existFlag = true;
        return;
    }
    else
    {
        searchParent(p->left, num);
        searchParent(p->right, num);
    }

}



int main()
{
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);
    
    createTree(head);

    int m;
    cin >> m;
    while(m > 0)
    {
        int tmpNum;
        cin >> tmpNum;
        searchParent(head, tmpNum);   
        if(!existFlag)
        {
            cout << "0" << endl;
        }
        existFlag = false;
        m--;
    }
    return 0;
}

/*
B 二叉树查找结点及父结点
分数 10
作者 朱允刚
单位 吉林大学
编写程序在二叉树中查找给定结点及父结点。二叉树结点的数据域值不等于0的整数。

输入格式:
输入第1行为一组用空格间隔的整数，表示带空指针信息的二叉树先根序列，其中空指针用0表示。例如1 5 8 0 0 0 6 0 0表示如下图的二叉树。第2行为整数m，表示查询个数。接下来m行，每行为一个不等于0的整数K，表示要查找的结点的数据值。m不超过100，二叉树结点个数不超过150000，高度不超过6000。输入数据保证二叉树各结点数据值互不相等。

输出格式:
输出为m行，每行1个整数，表示被查找结点K的父结点数据值，若二叉树中无结点K或结点K无父结点，则输出0。

输入样例:
1 5 8 0 0 0 6 0 0
3
8
1
6
输出样例:
5
0
1
代码长度限制
16 KB
时间限制
300 ms
内存限制
20 MB
*/
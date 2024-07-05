#include <iostream>

using namespace std;

typedef struct treeNode
{
    int val;
    treeNode * left;
    treeNode * right;
    treeNode(int num) : val(num), left(nullptr), right(nullptr){};
}treeNode;

void createTree(treeNode *& p)// 创建二叉树
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

void preOrder(treeNode * p)// 先根
{
    if(p == nullptr)
    {
        return;
    }
    cout << p->val << " ";
    preOrder(p->left);
    preOrder(p->right);

}

void midOrder(treeNode * p)// 中根
{
    if(p == nullptr)
    {
        return;
    }
    preOrder(p->left);
    cout << p->val << " ";
    preOrder(p->right);
}

void postOrder(treeNode * p)// 后根
{
    if(p == nullptr)
    {
        return;
    }
    preOrder(p->left);
    preOrder(p->right);
    cout << p->val << " ";
}
treeNode * head = nullptr;

int main()
{
    ios::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);
    createTree(head);

    preOrder(head);
    cout << endl;
    midOrder(head);
    cout << endl;
    postOrder(head);
    cout << endl;

    return 0;
}

/*
A 二叉树的创建与遍历
分数 10
作者 朱允刚
单位 吉林大学
通过带空指针信息的先根序列（亦称先序序列）创建二叉树，并进行先根（先序）、中根（中序）、后根（后序）遍历。二叉树结点数据域值为不等于0的整数（可能是正数也可能是负数），空指针用0表示，例如1 5 8 0 0 0 6 0 0表示如下图的二叉树。

输入格式:
输入为一组用空格间隔的整数，表示带空指针信息的二叉树先根序列。其中空指针信息用0表示。二叉树结点个数不超过150000，高度不超过6000。输入数据保证二叉树各结点数据值互不相等。

输出格式:
输出为3行整数，每个整数后一个空格。第1行为该二叉树的先根序列，第2行为中根序列，第3行为后根序列。

输入样例:
1 5 8 0 0 0 6 0 0
输出样例:
1 5 8 6 
8 5 1 6 
8 5 6 1 
代码长度限制
16 KB
时间限制
200 ms
内存限制
20 MB
*/
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

void midOrder(treeNode *p)// 中根
{
    if(p == nullptr)
    {
        return;
    }

    midOrder(p->left);
    cout << p->val << " ";
    midOrder(p->right);
}

void delTreeNode(treeNode *p, int num)// 删除节点
{
    if(p == nullptr)
    {
        return;
    }
    if(p->left != nullptr && p->left->val == num)
    {
        p->left = nullptr;
        existFlag = true;
    }
    else if(p->right != nullptr && p->right-> val == num)
    {
        p->right = nullptr;
        existFlag = true;

    }
    else
    {
        delTreeNode(p->left, num);
        delTreeNode(p->right, num);
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
        if(head != nullptr && head->val == tmpNum)
        {
            head = nullptr;
        }
        else
        {
            delTreeNode(head, tmpNum);   
        }
        if(!existFlag)
        {
            cout << "0" << endl;
        }
        else
        {
            midOrder(head);
            cout << endl;
        }
        existFlag = false;
        m--;
    }
    return 0;
}
/*
C 二叉树删除子树
分数 10
作者 朱允刚
单位 吉林大学
编写程序对给定二叉树执行若干次删除子树操作，输出每次删除子树后剩余二叉树的中根序列。二叉树结点的数据域值为不等于0的整数。每次删除操作是在上一次删除操作后剩下的二叉树上执行。

输入格式:
输入第1行为一组用空格间隔的整数，表示带空指针信息的二叉树先根序列，其中空指针信息用0表示。例如1 5 8 0 0 0 6 0 0表示如下图的二叉树。第2行为整数m，表示要进行的删除操作次数。接下来m行，每行一个不等于0的整数K，表示要删除以K为根的子树。m不超过100，二叉树结点个数不超过5000。输入数据保证各结点数据值互不相等，且删除子树后二叉树不为空。

输出格式:
输出为m行，每行为一组整数，表示执行删除操作后剩余二叉树的中根序列（中根序列中每个整数后一个空格）。若要删除的子树不在当前二叉树中，则该行输出0（0后无空格）。

输入样例:
1 5 8 0 0 0 6 0 0
3
5
8
6
输出样例:
1 6 
0
1 
代码长度限制
16 KB
时间限制
100 ms
内存限制
10 MB
*/
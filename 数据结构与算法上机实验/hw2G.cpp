#include <iostream>
#include <stack>

using namespace std;


typedef struct treeNode
{
    int val;
    treeNode * left;
    treeNode * right;
    treeNode(int num) : val(num), left(nullptr), right(nullptr){};
}treeNode;

treeNode * head = nullptr;

void createTree(treeNode *& p)// 建树
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

stack<treeNode *> goLeft;// 向左遍历时记录的点
stack<treeNode *> goRight;// 向右遍历时记录的点
bool printFlag = false;// 结点a和b之间才输出
int a, b;

void sTra()// S遍历
{
    goLeft.push(head);
    while(!(goLeft.empty() && goRight.empty()))
    {
        while(!goLeft.empty())
        {
            treeNode * p = goLeft.top();
            goLeft.pop();

            if(!printFlag && p->val == a)
            {
                printFlag = true;
            }
            

            if(printFlag)
            {
                cout << p->val << " ";
            }
            
            if(printFlag && p->val == b)
            {
                printFlag = false;
            }
            if(p->right != nullptr)
                goRight.push(p->right);
            if(p->left != nullptr)
                goRight.push(p->left);
        }

        while(!goRight.empty())
        {
            treeNode * p = goRight.top();
            goRight.pop();

            if(!printFlag && p->val == a)
            {
                printFlag = true;
            }
            

            if(printFlag)
            {
                cout << p->val << " ";
            }
            
            if(printFlag && p->val == b)
            {
                printFlag = false;
            }
            if(p->left != nullptr)
                goLeft.push(p->left);
            if(p->right != nullptr)
                goLeft.push(p->right);
        }
    }

}

int main()
{
    createTree(head);
    cin >> a >> b;
    sTra();

    return 0;
}
/*
G S遍历
分数 30
作者 朱允刚
单位 吉林大学
二叉树的“S遍历”定义为从根结点开始，先自右向左遍历，然后下一层自左向右遍历，再下一层自右向左遍历，以此类推…。例如下图所示二叉树的S遍历序列为1 2 3 6 5 4 7 8。现给定一棵非空二叉树，结点数据域值为互不相等且不等于0的正整数，同时给定两个正整数a和b，请编写程序输出结点a和b间的S遍历序列。

555.jpg

输入格式:
输入第一行为1组用空格间隔的正整数，表示带空指针信息的二叉树先根序列，二叉树结点个数不超过150000，高度不超过5000。第二行为两个正整数a和b，含义如题目所述，保证a和b一定在二叉树中，且在S遍历序列中a在b的前边。

输出格式:
输出为一行整数，每个整数后一个空格，表示数据值为a和b的两个结点间的S遍历序列。

输入样例1:
1 2 4 0 0 0 3 5 7 0 0 8 0 0 6 0 0
1 8
输出样例1:
1 2 3 6 5 4 7 8 
输入样例2:
1 2 0 4 0 7 0 0 3 5 0 0 6 8 20 0 0 21 0 0 0
6 8
输出样例2:
6 5 4 7 8 
输入样例3:
1 2 0 3 4 5 0 0 6 0 0 0 7 0 8 9 10 0 0 11 0 0 0
1 11
输出样例3:
1 2 7 8 3 4 9 11 
输入样例4:
2 4 3 0 0 8 0 0 10 5 7 9 0 0 1 0 0 17 0 0 6 0 0
2 9
输出样例4:
2 4 10 6 5 8 3 7 17 1 9 
数据规模:
测试点0-2、5-9：结点个数≤50，树高≤20
测试点3：4500≤结点个数≤5500，4000≤树高≤5000
测试点4：130000≤结点个数≤150000，10≤树高≤20

代码长度限制
16 KB
时间限制
100 ms
内存限制
20 MB
*/
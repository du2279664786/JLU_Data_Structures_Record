#include <iostream>
#include <string>
#include <ctime>
#include <queue>


using namespace std;

struct treeNode{
    char val;
    treeNode * left = nullptr;
    treeNode * right = nullptr;
    treeNode(char val) : val(val),left(nullptr),right(nullptr){}
    ~treeNode()
    {
        if (left != nullptr)
        {
            delete left;
        }
        if (right!= nullptr)
        {
            delete right;
        }
    }
};

int treeHeigh;
int flag = 1;


treeNode * buildTree(string post, string mid)
{
    auto last = post.rbegin();
    treeNode * root = new treeNode(*last);

    int rootPoint = mid.find(root->val);

    string left = mid.substr(0, rootPoint);
    string right = mid.substr(rootPoint + 1);
    int lsize = left.size();
    int rsize = right.size();
    string pleft, pright;
    if(lsize != 0)
    {
        pleft = post.substr(0, lsize);
    }
    if (rsize!= 0)
    {
        pright = post.substr(post.size() - rsize - 1, rsize);
    }

    for(int i = 0; i < lsize; i++)
    {
        if(left.find(pleft[i]) == string::npos)
        {
            flag = 0;
            return nullptr;
        }
    }

    for(int i = 0; i < rsize; i++)
    {
        if(right.find(pright[i]) == string::npos)
        {
            flag = 0;
            return nullptr;
        }
    }


    if(lsize != 0)
        root->left = buildTree(pleft, left);
    if(rsize != 0)
        root->right = buildTree(pright, right);

    return root;
}


void preOrder(treeNode * root, int heigh)
{
    if(root == nullptr)
    {
        return;
    }

    cout << root->val;
    
    preOrder(root->left, heigh);
    preOrder(root->right, heigh);
}

int dfs(treeNode * root)// 层次遍历，并记树的高度
{
    queue<treeNode *> q;
    if(root == nullptr)
    {
        return 0;
    }
    q.push(root);
    treeHeigh = 0;
    while(!q.empty())
    {
        
        int size = q.size();
        for(int i = 0; i < size; i++)
        {
            treeNode * p = q.front();
            q.pop();    
            if(p->left!= nullptr)
            {
                q.push(p->left);
            }
            if (p->right!= nullptr)
            {
                q.push(p->right);
            }
        }
        treeHeigh++;
    }
    return treeHeigh-1;
}


int main()
{
    string post, mid;
    while(getline(cin, post) && getline(cin, mid))
    {
        //clock_t time1 = clock();
        treeHeigh = 0;
        flag = 1;

        treeNode * p = buildTree(post, mid);
        if(flag == 0)
        {
            printf("INVALID\n");
            continue;
        }
        //cout << endl << mid << endl << tmpString << endl;
        
        if(flag)
        {
            treeHeigh = dfs(p);
            cout << treeHeigh << endl;
            preOrder(p, 0);
            cout << endl;
        }
        else
        {
            cout << "INVALID" << endl;
        }
        
    }
    return 0;
}

/*
D 重建二叉树
分数 30
作者 朱允刚
单位 吉林大学
给定非空二叉树的中根序列和后根序列，请编写程序创建该二叉树，计算其高度和先根序列；如给定的中根和后根序列不合法，则亦能识别。

输入格式:
输入包含多组数据（不超过10组），每组为两行字符串，第一行表示某二叉树的后根序列，第二行表示其中根序列。结点的值均为A-Z的大写字母，故二叉树结点个数不超过26，且保证输入的两个序列都是结点的全排列，但不一定是合法的中根和后根序列。输入保证不是空二叉树。

输出格式:
对于每组数据，如果输入的序列不合法（不是同一棵树的中根序列和后根序列），则输出INVALID；若输入序列合法，输出为两行，第一行为一个整数，表示该二叉树的高度，第二行为一个字符串，表示该二叉树的先根序列。

输入样例1:
CEFDBHGA
CBEDFAGH
CBEDFAGH
CEFDBHGA
BCA 
CAB

输出样例1:
3
ABCDEFGH
INVALID
INVALID

代码长度限制
16 KB
时间限制
50 ms
内存限制
64 MB
*/
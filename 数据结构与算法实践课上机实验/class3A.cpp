#include <iostream>
#include <string>

using namespace std;

class BSTNode
{
public:
    BSTNode(int num)
    {
        numVal = num;
        left = nullptr;
        right = nullptr;
    }

    

    int numVal;
    BSTNode *left;
    BSTNode *right;
};

void insert(BSTNode *&root, int num)
{
    // 插入，指针为空说明无值，小则左，大则右
    if(root == nullptr)
    {
        root = new BSTNode(num);
    }
    else if(num == root->numVal)
    {
        return;
    }
    else if(num < root->numVal)
    {
        insert(root->left, num);
    }
    else if(num > root->numVal)
    {
        insert(root->right, num);
    }
}

void remove(BSTNode * &root, int K)
{
    // 删除
    if(root == nullptr)
    {
        // 说明没有该值
        return;
    }
    // 小则左，大则右
    if(K < root->numVal) remove(root->left, K);
    else if(K > root->numVal) remove(root->right, K);
    else if(root->left != nullptr && root->right != nullptr)
    {
        // 有两子节点，则与右儿子的最小点换，并删之
        BSTNode *s = root->right;
        while(s->left != nullptr)
        {
            s = s->left;
        }
        root->numVal = s->numVal;
        remove(root->right, s->numVal);
    }
    else
    {
        // 有一或无儿子，则替换指针后直接删除
        BSTNode *oldRoot = root;
        root = (root->left != nullptr)? root->left : root->right;
        delete oldRoot;
    }
}

void printMiddle(BSTNode *root)
{
    if(root == nullptr) return;
    printMiddle(root->left);
    cout << root->numVal << " ";
    printMiddle(root->right);
}

void printPre(BSTNode *root)
{
    if(root == nullptr) return;
    cout << root->numVal << " ";
    printPre(root->left);
    printPre(root->right);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    BSTNode *head = nullptr;
    int T, K;
    string op;
    string insertSign = "Insert";
    cin >> T;
    for(int i = 0; i < T; i++)
    {
        cin >> op >> K;
        if(op == insertSign)
        {
            insert(head, K);
        }
        else
        {
            remove(head, K);
        }
    }

    printMiddle(head);
    cout << endl << endl;

    printPre(head);
    cout << endl;
    return 0;
}

/*
A 手撕BST
分数 50
作者 朱允刚
单位 吉林大学
对一棵初始为空的二叉查找树（Binary Search Tree, BST）进行若干插入或删除操作，请输出最后的二叉查找树。

bst.png

输入格式:
输入第一行为一个整数 T，表示操作数目。随后 T 行，每行为Insert K（表示插入关键词为K的结点，若树中已有关键词为K的结点，则不插入）或Remove K（表示删除关键词为K的结点，若树中无关键词为K的结点，则不删除），其中K为整数。 T 不超过2×10^5，树高不超过10^4。

输出格式:
输出经上述操作后得到的二叉查找树的中根序列和先根序列，序列中每个整数后一个空格，两个序列之间用空行间隔。

输入样例:
16
Insert 17
Insert 31
Insert 13
Insert 11
Insert 20
Insert 35
Insert 25
Insert 8
Insert 4
Insert 11
Insert 24
Insert 40
Insert 27
Insert 9
Remove 17
Remove 13

输出样例:
4 8 9 11 20 24 25 27 31 35 40 

20 11 8 4 9 31 25 24 27 35 40 

代码长度限制
16 KB
时间限制
500 ms
内存限制
64 MB
栈限制
8192 KB
*/
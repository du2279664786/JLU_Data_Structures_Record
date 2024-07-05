#include <iostream>
#include <string>

using namespace std;

typedef struct _AVLNode{
public:
    _AVLNode(int K){
        key = K;
        height = 0;
        left = nullptr;
        right = nullptr;
    }
    
    int key;
    int height;
    struct _AVLNode *left, *right;
}AVLnode;

int max(int a, int b)
{
    return(a>b)?a:b;
}

int Height(AVLnode *t)
{
    return (t==nullptr)?-1:t->height + 1;
}

void UpdateHeight(AVLnode *t){
    t->height = max(Height(t->left), Height(t->right));
}

void LL(AVLnode *&A)
{
    // 单右转
    AVLnode *B = A->left;
    A->left = B->right;
    B->right = A;
    UpdateHeight(A);
    UpdateHeight(B);
    A = B;
}

void RR(AVLnode *&A)
{
    // 单左转
    AVLnode *B = A->right;
    A->right = B->left;
    B->left = A;
    UpdateHeight(A);
    UpdateHeight(B);
    A = B;
}

void LR(AVLnode *&A)
{
    // 先将C转到左侧，再将C转到中间
    RR(A->left);
    LL(A);
}

void RL(AVLnode *&A)
{
    // 先将C转到右侧，再将C转到中间
    LL(A->right);
    RR(A);
}

void Balance(AVLnode *&t)
{
    // 左子树高
    if(Height(t->left) - Height(t->right) == 2)
    {
        // 最左偏高
        if(Height(t->left->left) >= Height(t->left->right))
        {
            LL(t);
        }
        else
        {
            // 折线，先左再右
            LR(t);
        }
    }
    else if(Height(t->right) - Height(t->left) == 2)
    {
        // 最右偏高
        if(Height(t->right->right) >= Height(t->right->left))
        {
            RR(t);
        }
        else
        {
            // 折线，先右再左
            RL(t);
        }
    }
    UpdateHeight(t);
}


void Insert(AVLnode *&t, int K){
    // 无则新建点，小左大右，相等则不变
    if(t == nullptr)
    {
        t = new AVLnode(K);
    }
    else if(K < t->key)
    {
        Insert(t->left, K);
    }
    else if(K > t->key)
    {
        Insert(t->right, K);
    }
    else if(K == t->key)
    {
        return;
    }
    Balance(t);
}

void Remove(AVLnode *&t, int K)
{
    // 无则返回
    if(t == nullptr)
    {
        return;
    }
    // 左小右大
    if(t->key > K)
    {
        Remove(t->left, K);
    }
    else if(t->key < K)
    {
        Remove(t->right, K);
    }
    // 两儿取右儿最小
    else if(t->left != nullptr && t->right != nullptr)
    {
        AVLnode *s = t->right;
        while(s->left != nullptr) s = s->left;
        t->key = s->key;
        Remove(t->right, s->key);
    }
    // 单或无儿直接继承
    else
    {
        AVLnode *oldroot = t;
        t = (t->left != nullptr) ? t->left : t->right;
        delete oldroot;
    }

    if(t != nullptr)
    {
        Balance(t);
    }
}

void printMiddle(AVLnode *root)
{
    if(root == nullptr) return;
    printMiddle(root->left);
    std::cout << root->key << " ";
    printMiddle(root->right);
}

void printPre(AVLnode *root)
{
    if(root == nullptr) return;
    std::cout << root->key << " ";
    printPre(root->left);
    printPre(root->right);
}

int main()
{
    /*ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);*/
    AVLnode *head = nullptr;
    int T, K;
    string op;
    string insertSign = "Insert";
    std::cin >> T;
    for(int i = 0; i < T; i++)
    {
        std::cin >> op >> K;
        if(op == insertSign)
        {
            Insert(head, K);
        }
        else
        {
            Remove(head, K);
        }
        /*
        printMiddle(head);
        std::cout << endl << endl;

        printPre(head);
        std::cout << endl << endl;
        */
        
    }

    printMiddle(head);
    std::cout << endl << endl;

    printPre(head);
    //std::cout << endl;
    return 0;
}

/*
B 手撕AVL树（基础版）
分数 50
作者 朱允刚
单位 吉林大学
对一棵初始为空的高度平衡树（AVL树）进行若干插入或删除操作，请输出最后得到的AVL树。

备注：
（1）当有多种旋转方案时，优先选择旋转次数少的方案。
（2）70%的测试点只包含插入操作，如果你只实现插入操作，也能获得70%的分数。

输入格式:
输入第一行为一个整数 T，表示操作数目。随后 T 行，每行为Insert K（表示插入关键词为K的结点，若树中已有关键词为K的结点，则不插入）或Remove K（表示删除关键词为K的结点，若树中无关键词为K的结点，则不删除），其中K为整数。 T 不超过2×10^5 。

输出格式:
输出经上述操作后得到的高度平衡树的中根序列和先根序列，序列中每个整数后一个空格，两个序列之间用空行间隔。

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

20 8 4 11 9 31 25 24 27 35 40 
代码长度限制
16 KB
时间限制
100 ms
内存限制
64 MB
栈限制
8192 KB
*/
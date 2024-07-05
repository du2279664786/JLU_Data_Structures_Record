#include <iostream>
#include <string>

using namespace std;

typedef struct _RBNode{
public:
    _RBNode(int K){
        key = K;

        left = nullptr;
        right = nullptr;
        parent = nullptr;
        color = 'R';
        isNull = false;
    }
    
    int key;
    char color;
    bool isNull;
    struct _RBNode *left, *right, *parent;
}RBnode;

RBnode *head = nullptr;

void LL(RBnode *A)
{
    // 右旋
    RBnode *p = A->parent;
    RBnode *B = A->left;
    RBnode *BR = B->right;
    A->left = BR;
    if(BR != nullptr)
    {
        BR->parent = A;
    }
    B->right = A;
    A->parent = B;
    if(p != nullptr)
    {
        if(p->left == A)
        {
            p->left = B;
        }
        else
        {
            p->right = B;
        }
    }
    else
    {
        head = B;
        head->parent = nullptr;
    }
    B->parent = p;
    A->parent = B;
}

void RR(RBnode *A)
{
    // 左旋
    RBnode *p = A->parent;
    RBnode *B = A->right;
    RBnode *BL = B->left;
    A->right = BL;

    if(BL != nullptr)
    {
        BL->parent = A;
    }
    B->left = A;
    if(p != nullptr)
    {
        if(p->left == A)
        {
            p->left = B;
        }
        else
        {
            p->right = B;
        }
    }
    else
    {
        head = B;
        head->parent = nullptr;
    }
    B->parent = p;
    A->parent = B;
}

void LR(RBnode *A)
{
    // 先将C转到左侧，再将C转到中间
    RR(A->left);
    LL(A);
}

void RL(RBnode *A)
{
    // 先将C转到右侧，再将C转到中间
    LL(A->right);
    RR(A);
}

void insertBalance(RBnode *&t)
{
    if(head != nullptr)
    {
        // 保证根节点为黑色
        head->color = 'B';
    }

    if(t == nullptr)// 取到空则返回
    {
        return;
    }

    RBnode *p = t->parent;// 父亲

    if(p == nullptr)// 父亲为空则返回
    {
        return;
    }

    if(p->color == 'B')// 父亲为黑色则无需修正
    {
        return;
    }

    RBnode *g = p->parent;// 爷爷

    RBnode *u = nullptr;// 叔叔

    char parentLoc;// 父亲左右记录
    
    if(p == g->left)// 父亲为左，叔叔为右
    {
        u = g->right;
        parentLoc = 'L';
    }
    else // 父亲为右，叔叔为左
    {
        u = g->left;
        parentLoc = 'R';
    }

    if(u != nullptr && u->color == 'R')// 叔叔存在且为红
    {
        p->color = 'B';
        u->color = 'B';
        g->color = 'R';
        insertBalance(g);
    }
    else//叔叔不存在||叔叔为黑
    {
        if(parentLoc == 'L')// p = g->left
        {
            if(t == p->left)
            {
                LL(g);
                g->color = 'R';
                p->color = 'B';
            }
            else
            {
                LR(g);
                g->color = 'R';
                t->color = 'B';
            }
        }
        else// p = g->right
        {
            if(t == p->left)
            {
                RL(g);
                g->color = 'R';
                t->color = 'B';

            }
            else
            {
                RR(g);
                g->color = 'R';
                p->color = 'B';
            }
        }
    }
    if(head != nullptr)
    {
        // 保证根节点为黑色
        head->color = 'B';
    }
}


RBnode* Insert(RBnode *&head, int K){
    // 发现无该点
    RBnode *p = nullptr;
    RBnode *t = head;
    if(head == nullptr)// 头指针无点则直接插入
    {
        head = new RBnode(K);
        head->color = 'B';
        return head;
    }

    while(t != nullptr && t->key != K)// 二叉树查找位置
    {
        p = t;
        if(t->key > K)// 小左
        {
            t = t->left;
        }
        else if(t->key < K)// 大右
        {
            t = t->right;
        }
        else
        {
            return nullptr;
        }
    }

    if(t == nullptr)// 不存在值K点，创造一个
    {
        t = new RBnode(K);
        t->parent = p;
        if(p->key > K)
        {
            p->left = t;
        }
        else
        {
            p->right = t;
        }
    
        return t;
    }
    // 出现重复值
    return t;
}

void removeBalance(RBnode *t)// 专门修复双黑缺陷
{
    
    if(t == nullptr)// 排除删空
    {
        return;
    }
    RBnode *x = t;// 更换删除节点名字
    RBnode *p = t->parent;// 取到父亲节点

    if(p == nullptr)// 防止递归到根的情况
    {
        return;
    }
    if(t->color == 'R')
    {
        t->color = 'B';
        return;
    }

    RBnode *s = nullptr;// 取x兄弟
    char xLoc;

    if(x == p->left)// 删点为父亲左儿子
    {
        xLoc = 'L';
        s = p->right;
    }
    else // 删点为父亲右儿子
    {
        xLoc = 'R';
        s = p->left;
    }

    if(s != nullptr && s->color == 'R')// 兄弟为红
    {
        if(xLoc == 'R')// 兄弟为p左孩子
        {
            LL(p);
            s->color = 'B';
            p->color = 'R';
            removeBalance(x);
        }
        else// 兄弟为p右孩子
        {
            RR(p);
            s->color = 'B';
            p->color = 'R';
            removeBalance(x);
        }
    }
    else// 兄弟为黑也可能为空
    {
        // 看兄弟有无红孩子
        char sRedChildLoc;
        RBnode *n = nullptr;
        if(s != nullptr && s->right != nullptr && s->right->color == 'R')// 红孩子在右
        {
            sRedChildLoc = 'R';
            n = s->right;
            if(xLoc == 'R')
            {
                LR(p);
                n->color = p->color;
                p->color = 'B';
                s->color = 'B';
            }
            else
            {
                RR(p);
                char pColor = p->color;
                n->color = 'B';
                p->color = 'B';
                s->color = pColor;
            }
        }else if(s != nullptr && s->left != nullptr && s->left->color == 'R')// 红孩子在左
        {
            sRedChildLoc = 'L';
            n = s->left;
            if(xLoc == 'R')
            {
                LL(p);
                char pColor = p->color;
                p->color = 'B';
                s->color = pColor;
                n->color = 'B';
            }
            else
            {
                RL(p);
                n->color = p->color;
                p->color = 'B';
            }
        }
        else if(s != nullptr)//无红孩子
        {
            if(p->color == 'R')//父亲为红
            {
                s->color = 'R';
                p->color = 'B';
                
                if(t->isNull == true)// 说明这个是要补删的点，但因临时充当黑色叶结点暂时保留
                {
                    if(t == t->parent->left)// t为左儿子
                    {
                        if(t->right != nullptr)// t有右儿子
                        {
                            t->parent->left = t->right;
                            t->right->parent = t->parent;
                            delete t;
                        }
                        else if(t->left != nullptr)// t有左儿子
                        {
                            t->parent->left = t->left;
                            t->left->parent = t->parent;
                            delete t;
                        }
                        else
                        {
                            t->parent->left = nullptr;
                            delete t;
                        }
                    }
                    else if(t == t->parent->right)// t为右儿子
                    {
                        if(t->right != nullptr)// t有右儿子
                        {
                            t->parent->right = t->right;
                            t->right->parent = t->parent;
                            delete t;
                        }
                        else if(t->left != nullptr)// t有左儿子
                        {
                            t->parent->right = t->left;
                            t->left->parent = t->parent;
                            delete t;
                        }
                        else
                        {
                            t->parent->right = nullptr;
                            delete t;
                        }
                    }
                }
                return;
            }
            else // 父亲为黑
            {
                s->color = 'R';
                removeBalance(p);
            }
        }
    }

    if(t->isNull == true)// 说明这个是要补删的点，但因临时充当黑色叶结点暂时保留
    {
        if(t == t->parent->left)// t为左儿子
        {
            if(t->right != nullptr)// t有右儿子
            {
                t->parent->left = t->right;
                t->right->parent = t->parent;
                delete t;
            }
            else if(t->left != nullptr)// t有左儿子
            {
                t->parent->left = t->left;
                t->left->parent = t->parent;
                delete t;
            }
            else
            {
                t->parent->left = nullptr;
                delete t;
            }
        }
        else if(t == t->parent->right)// t为右儿子
        {
            if(t->right != nullptr)// t有右儿子
            {
                t->parent->right = t->right;
                t->right->parent = t->parent;
                delete t;
            }
            else if(t->left != nullptr)// t有左儿子
            {
                t->parent->right = t->left;
                t->left->parent = t->parent;
                delete t;
            }
            else
            {
                t->parent->right = nullptr;
                delete t;
            }
        }
    }
    
    
    if(head != nullptr)
    {
        // 保证根节点为黑色
        head->color = 'B';
    }
}

RBnode *Remove(RBnode *t, int K)// 找到要真正删除的节点
{
    // 先找到t在哪
    while(t != nullptr && t->key != K)
    {
        if(t->key > K) t = t->left;
        else if(t->key < K) t = t->right;
    }
    if(t == nullptr) return t; // 不存在K值点

    if(t->left != nullptr && t->right != nullptr)// 有两儿
    {
        RBnode *minR = t->right;
        while(minR->left != nullptr)// 找t右子树最小点
        {
            minR = minR->left;
        }
        t->key = minR->key;
        t = minR;
    }

    //考虑t为根
    if(t->parent == nullptr)
    {
        if(t->left != nullptr)
        {
            head = t->left;
            delete t;
        }
        else if(t->right != nullptr)
        {
            head = t->right;
            delete t;
        }
        else
        {
            head = nullptr;
        }

        return nullptr;
    }


    // 下面都是t单儿子或无儿子
    if(t->color == 'R')// 删除节点为红色，直接删掉,返回空，不用修复
    {
        if(t == t->parent->left)// t为左儿子
        {
            if(t->right != nullptr)// t有右儿子
            {
                t->parent->left = t->right;
                t->right->parent = t->parent;
                delete t;
            }
            else if(t->left != nullptr)// t有左儿子
            {
                t->parent->left = t->left;
                t->left->parent = t->parent;
                delete t;
            }
            else
            {
                t->parent->left = nullptr;
                delete t;
            }
        }
        else if(t == t->parent->right)// t为右儿子
        {
            if(t->right != nullptr)// t有右儿子
            {
                t->parent->right = t->right;
                t->right->parent = t->parent;
                delete t;
            }
            else if(t->left != nullptr)// t有左儿子
            {
                t->parent->right = t->left;
                t->left->parent = t->parent;
                delete t;
            }
            else
            {
                t->parent->right = nullptr;
                delete t;
            }
        }
        t = nullptr;
    }
    else// 删除结点为黑色，无论如何也要先执行完删除操作
    {
        RBnode *newT = nullptr;
        if(t == t->parent->left)// t为左儿子
        {
            if(t->right != nullptr)// t有右儿子
            {
                newT = t->right;
                t->parent->left = t->right;
                t->right->parent = t->parent;
                delete t;
                if(newT->color == 'R')//代替结点为红色，
                {
                    newT->color = 'B';
                    newT = nullptr;
                }
            }
            else if(t->left != nullptr)// t有左儿子
            {
                newT = t->left;
                t->parent->left = t->left;
                t->left->parent = t->parent;
                delete t;
                if(newT->color == 'R')
                {
                    newT->color = 'B';
                    newT = nullptr;
                }
            }
            else
            {
                newT = t;
                t->isNull = true;
            }
        }
        else if(t == t->parent->right)// t为右儿子
        {
            if(t->right != nullptr)// t有右儿子
            {
                newT = t->right;
                t->parent->right = t->right;
                t->right->parent = t->parent;
                delete t;
                if(newT->color == 'R')
                {
                    newT->color = 'B';
                    newT = nullptr;
                }
            }
            else if(t->left != nullptr)// t有左儿子
            {
                newT = t->left;
                t->parent->right = t->left;
                t->left->parent = t->parent;
                delete t;
                if(newT->color == 'R')
                {
                    newT->color = 'B';
                    newT = nullptr;
                }
            }
            else
            {
                newT = t;
                t->isNull = true;
            }
        }
        t = newT;
    }
    return t;
}

void printMiddle(RBnode *root)
{
    if(root == nullptr) return;
    printMiddle(root->left);
    std::cout << root->key << " " << root->color << " ";
    printMiddle(root->right);
}

void printPre(RBnode *root)
{
    if(root == nullptr) return;
    std::cout << root->key << " " << root->color << " ";
    //cout << &root << " ";
    //if(root->parent != nullptr)
    //    std::cout << "父亲为" << root->parent->key << " ";
    printPre(root->left);
    printPre(root->right);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    int T, K;
    string op;
    string insertSign = "Insert";
    std::cin >> T;
    for(int i = 0; i < T; i++)
    {
        std::cin >> op >> K;
        if(op == insertSign)
        {
            RBnode *p = Insert(head, K);
            insertBalance(p);
        }
        else
        {
            RBnode *t = Remove(head, K);
            removeBalance(t);
        }
        
//        printMiddle(head);
  //      std::cout << endl << endl;
    //    printPre(head);
      //  std::cout << endl << endl;
    }
if(head != nullptr)
    {
        // 保证根节点为黑色
        head->color = 'B';
    }
    printMiddle(head);
    std::cout << endl << endl;

    printPre(head);
    std::cout << endl;
    return 0;
}

/*
C 手撕红黑树
分数 50
作者 朱允刚
单位 吉林大学
对一棵初始为空的红黑树（Red-Black Tree, RBT）进行若干插入或删除操作，请输出最后的红黑树。

rbt.png

备注：
（1）当有多种旋转方案时，优先选择旋转次数少的方案。
（2）70%的测试点只包含插入操作，如果你只实现插入操作，也能获得70%的分数。

输入格式:
输入第一行为一个整数 T，表示操作数目。随后 T 行，每行为Insert K（表示插入关键词为K的结点，若树中已有关键词为K的结点，则不插入）或Remove K（表示删除关键词为K的结点，若树中无关键词为K的结点，则不删除），其中K为整数。 T 不超过2×10 
5
 。

输出格式:
输出经上述操作后得到的红黑树的中根序列和先根序列，序列中对于每个结点输出其关键词和颜色（红色用R表示，黑色用B表示），每个元素后一个空格，两个序列之间用空行间隔。

输入样例:
5
Insert 8
Insert 9
Insert 3
Insert 4
Insert 5

输出样例:
3 R 4 B 5 R 8 B 9 B 

8 B 4 B 3 R 5 R 9 B 

代码长度限制
16 KB
时间限制
100 ms
内存限制
64 MB
栈限制
8192 KB
*/
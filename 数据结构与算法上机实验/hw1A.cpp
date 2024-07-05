#include <iostream>
#include <string>

using namespace std;
// 三种情况，字符串置首，插入字符串中，以及字符串的删除

typedef struct _stringNode//自定义字符串类单元，双向链表节点
{
public:
    char val;
    struct _stringNode* prev;
    struct _stringNode* next;
    _stringNode() : val('\0'), prev(nullptr), next(nullptr) {}

    _stringNode(char c) : val(c), prev(nullptr), next(nullptr) {}
}stringNode;

class myString// 自定义的字符串类，实际上是双哨兵的双向链表
{
public:
    myString()
    {
        head = new stringNode();
        tail = new stringNode();
        head->next = tail;
        tail->prev = head;
        workPointer = tail;
    }

    void typeIn(char c)// 字符插光标前
    {
        stringNode* p = new stringNode(c);
        p->next = workPointer;
        p->prev = workPointer->prev;
        workPointer->prev->next = p;
        workPointer->prev = p;
    }

    void eraseBack()// 光标前除head字符消除
    {
        stringNode* p = workPointer->prev;
        if (p != head)
        {
            workPointer->prev = p->prev;
            p->prev->next = workPointer;
            workPointer->prev = p->prev;
            delete p;
        }
        p = nullptr;
    }


    void print()// 打印字符串
    {
        stringNode* p = head->next;
        while (p != tail)
        {
            cout << p->val;
            p = p->next;
        }
        cout << endl;
    }

    void goHead()// 光标置头下一个，空则相当于置尾，否则
    {
        workPointer = head->next;
    }

    void goTail()// 置尾
    {
        workPointer = tail;
    }

    void moveLeft()// 左移
    {
        if (workPointer->prev != head)
        {
            workPointer = workPointer->prev;
        }
    }

    void moveRight()// 右移
    {
        if (workPointer != tail)
        {
            workPointer = workPointer->next;
        }
    }



    stringNode* head;
    stringNode* tail;
    stringNode* workPointer; // 光标

};




int main()
{
    // 关闭输入输出缓存，使效率提升
    ios::sync_with_stdio(false);
    // 解除cin和cout的默认绑定，来降低IO的负担使效率提升
    cin.tie(NULL); cout.tie(NULL);

    myString s2 = myString();

    string s1;
    getline(cin, s1);



    for (int i = 0; i < s1.size(); i++)
    {
        //s2.print();
        //cout << endl;
        if (s1[i] == '{')
        {
            s2.goHead();
        }
        else if (s1[i] == '}')
        {
            s2.goTail();
        }
        else if (s1[i] == '<')
        {
            s2.moveLeft();
        }
        else if (s1[i] == '>')
        {
            s2.moveRight();
        }
        else if (s1[i] == '#')
        {
            s2.eraseBack();
        }
        else
        {
            s2.typeIn(s1[i]);
        }
    }

    s2.print();

    return 0;
}

/*
A 调皮的哈利
分数 30
作者 朱允刚
单位 吉林大学
贝蒂是个打字高手，打字时有不看屏幕的习惯。在一次贝蒂打字时，调皮的哈利常常趁贝蒂不注意按下Home键、End键、左右方向键和退格键。当Home键被按下时，输入光标会跳到文本最开头；当End键被按下时，输入光标会跳到文本末尾；当左/右方向键被按下时，输入光标会向左/右移动一位；当退格键被按下时，输入光标左面的一个字符会被删除。现给出贝蒂和哈利按键的字符串，其中'{'表示Home键，'}'表示End键，'<'表示左方向键，'>'表示右方向键，'#'表示退格键，其余字符均表示输入的内容，请输出屏幕上最终显示的文本。

img.jpg

输入格式:
输入一个字符串，长度不超过5×10 
4
 ，包含大小写字母、空格、下划线、{、}、<、>、#，表示贝蒂和哈利的按键序列。

输出格式:
输出为屏幕上最终显示的字符串。

输入样例1:
jlu_cc{i_love_}st

输出样例1:
i_love_jlu_ccst
输入样例2:
stre<<aaa

输出样例2:
staaare
输入样例3:
xxx>>>yyy##z<<>k

输出样例3:
xxxykz
输入样例4:
abcd{efghi}jklm{nopq}rs{t}uvwxyz

输出样例4:
tnopqefghiabcdjklmrsuvwxyz
代码长度限制
16 KB
时间限制
25 ms
内存限制
10 MB
*/
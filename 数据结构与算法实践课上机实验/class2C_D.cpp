#include <iostream>
#include <string>
#include <algorithm>


using namespace std;

int is_new_word = 1;

int c2i(char c)
{
    if(c > 80)
        return c - 'a' + 10;
    else
        return c - '0';
}


typedef struct _data{
    _data()
    {
        val = nullptr;
        frequency = nullptr;
    }

    _data(string &s, int &num)
    {
        string * p = new string;
        *p = s;
        int *q = new int;
        *q = num;
        val = p;
        frequency = q;
    }

    void operator=(const _data &a)
    {
        val = a.val;
        frequency = a.frequency;
    }
    string *val;
    int *frequency;
}charNode;

bool charNodeCmp(charNode * a, charNode * b)
{
    return *a->frequency > *b->frequency || (*a->frequency == *b->frequency && *a->val < *b->val);
}

class trieNode
{
public:

    trieNode()
    {
        for(int i = 0; i < 36; i++)
        {
            next[i] = nullptr;
        }
        for(int i = 0; i < 11; i++)
        {
            sonStr[i] = nullptr;
        }
        sonCount = 0;
    }
    // 遍历一遍sonStr
    void printAllSon()
    {
        for(int i = 0; i < sonCount; i++)
        {
            cout << *sonStr[i]->val << endl;
        }
        cout << endl;
        for(int i = 0; i < sonCount; i++)
        {
            //cout << *sonStr[i]->frequency << endl;
        }
        //cout << endl;
    }

    // 输入，向存词尾添加，并排序
    void input(charNode * p)
    {
        // 查重
        for(int i = 0; i < sonCount; i++)
        {
            if(*p->val == *sonStr[i]->val)
            {
                if(*p->frequency > *sonStr[i]->frequency)
                {
                    *sonStr[i]->frequency = *p->frequency;
                }
                return;
            }
        }
        
        sonStr[sonCount] = p;
        
        if(sonCount < 10)
        {
            sonCount++;
        }
        //cout << *p->val << endl;
        //cout << "前" << endl;
        //printAllSon();
        sort(sonStr, sonStr + sonCount, charNodeCmp);
        //cout << "后" << endl;
        //printAllSon();
        

    }

    int sonCount;
    charNode *sonStr[11];

    trieNode* next[36];

};

class trieTree
{
public:
    // 构造函数
    trieTree()
    {
        for(int i = 0; i < 36; i++)
        {
            trieNode*p = new trieNode();
            next[i] = p;
        }
    }


    void insert(string & s, int &n)
    {
        int maxIndex = s.size();
        int inputIndex;

        trieNode *inputNode = nullptr;
        charNode *tmpCharNode = new charNode(s, n);

        for(int i = 0; i < (int)s.size(); i++)
        {
            char c = s[i];
            inputIndex = c2i(c);

            if(i == 0)
            {
                inputNode = this->next[inputIndex];
                if(i != (int)s.size() - 1)
                    inputNode->input(tmpCharNode);
            }
            else
            {
                if(inputNode->next[inputIndex] != nullptr)
                {
                    inputNode = inputNode->next[inputIndex];
                    if(i != (int)s.size() - 1)
                        inputNode->input(tmpCharNode);
                    continue;
                }
                inputNode->next[inputIndex] = new trieNode;
                inputNode = inputNode->next[inputIndex];
                if(i != (int)s.size() - 1)
                    inputNode->input(tmpCharNode);
            }
        }

        /*
        // 起始字母
        if(this->next[inputIndex] == nullptr)
        {
            trieNode * p = new trieNode();
            this->next[inputIndex] = p;
        }
        

        // 中间部分，记录最高十词
        inputNode = next[inputIndex];
        for(int i = 1; i < maxIndex - 1; i++)
        {
            //tmpCharNode = new charNode(s, n);
            inputNode->input(tmpCharNode);
            inputIndex = c2i(s[i]);
            if(inputNode->next[inputIndex] == nullptr)
            {
                trieNode * p = new trieNode();
                inputNode->next[inputIndex] = p;
            }
            inputNode = inputNode->next[inputIndex];
        }

        // 补末尾，不填词
        inputNode->input(tmpCharNode);
        inputIndex = c2i(s[maxIndex - 1]);
        if(inputNode->next[inputIndex] == nullptr)
        {
            trieNode * p = new trieNode();
            inputNode->next[inputIndex] = p;
        }
        // 这两行是末尾填词
        //inputNode = inputNode->next[inputIndex];
        //inputNode->input(tmpCharNode);
        */
        
    }

    // 返回是否有值
    int get_str(string &s, charNode ** result)
    {

        int strLen = s.size();
        trieNode *p = this->next[c2i(s[0])];
        if(p != nullptr)
            for(int i = 1; i < strLen; i++)
            {
                p = p->next[c2i(s[i])];
                if(p == nullptr)
                    return 0;
            }
        else
            return 0;
        
        int wordCount = p->sonCount;
        for(int i = 0; i < wordCount; i++)
        {
            result[i] = p->sonStr[i];
        }

        return wordCount;
    }
    

  
    trieNode* next[36];
};


// 比较频率与字典序
bool cmp(pair<string,int> a, pair<string,int> b)
{
    return a.second > b.second || (a.second == b.second && a.first > b.first);
}



int main()
{
    /*
    for(char i = '0'; i <= '9'; i++)
    {
        cout << i << " " << c2i(i) << endl;
    }
    cout << endl;

    for(char i = 'a'; i <= 'z'; i++)
    {
        cout << i << " " << c2i(i) << endl;
    }
    cout << endl;
    */
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    fflush(stdin);
    trieTree * head = new trieTree();

    
    // 建立一个字典树，每个结点存放字母/数字以及储存下层结点的指针数组
    for(int i = 0; i < n; i++)
    {
        int tmpNum;
        string tmpStr;
        char cStr[21];

        scanf("%d %s", &tmpNum, cStr);
        fflush(stdin);
        tmpStr = cStr;
        //dict.insert(pair<string, int>(tmpStr, tmpNum));
        head->insert(tmpStr, tmpNum);
    }

    // m次用户输入字符串
    for(int i = 0; i < m; i++)
    {
        string tmpStr;
        char cStr[21];
        scanf("%s", cStr);
        fflush(stdin);
        //cout << endl << "接收到字符串：" << tmpStr << " 长度为：" << tmpStr.length() << endl;
        tmpStr = cStr;
        charNode * result[10];
        int may = min(k, head->get_str(tmpStr, result));
        if(may > 0)
        {
            for(int j = 0; j < may; j++)
            {
                char tmpC[21];
                for(int k = 0; k <21;k++)
                {
                    tmpC[k] = '\0';
                }
                string s = *(result[j]->val);
                //ut << "S:" << s << s.size() <<endl;
                for(int k = 0; k < s.size();k++)
                {
                    tmpC[k] = s[k];
                }
                tmpC[s.size()] = '\0';
                printf("%s\n", tmpC);
                
                //cout << *result[i]->val << " " << *result[i]->frequency << endl;
            }
        }
        else
        {
            printf("no suggestion\n");
        }
        if(i < m - 1)
            printf("\n");
    }


    return 0;
}

/*
C 智能提示
分数 30
作者 朱允刚
单位 吉林大学
百度、谷歌等搜索引擎，以及输入法等各种软件通常包含这样一个功能，当用户在输入框输入信息时，软件会提供一种“智能提示”。对用户所输入的信息，自动补全、列出可能的完整单词，提示给用户，以方便用户输入，提升用户体验。

pic.jpg

这个功能是如何实现的呢？一种典型的实现方式是，在系统后台维护一个字典，当用户输入字符时，在字典中查找以用户当前输入的字符串为前缀的全部单词，选取其中历史使用率最高的若干单词作为候选词，建议给用户。

请编写程序实现上述功能。

备注：这里约定一个字符串不能称为自己的前缀。若用户输入的字符串恰好是字典中的一个单词，则该单词不必向用户建议。

输入格式:
输入第一行为3个正整数n、m、k。n为字典中单词个数。m为用户查询数，即用户输入的单词个数。对于用户输入的每个字符串，程序需要返回字典中以该字符串为前缀的、历史使用频率最高的k个单词。接下来n行，表示字典信息，每行为1个整数和1个字符串，整数表示单词的历史使用频率，字符串表示单词，请注意，单词包含的每个字符为a-z的小写字母或0-9的数字，即数字也可能构成字典中的单词。字典内的单词并非按使用频率有序存放。接下来m行，表示用户的查询，每行为一个a-z的小写字母或0-9的数字组成的字符串，表示用户的查询。另外请注意，由于字典往往是在用户历史数据的基础上加工而得，所以字典中可能出现重复单词，若某个单词在字典中出现多次，则其历史使用频率以最高者为准。 (n ≤ 10000, m ≤ 20000, k ≤ 10, 每个单词长度不超过20，单词历史使用频率小于2 31)

输出格式:
对于用户输入的每个字符串，按使用频率降序输出字典中以该字符串为前缀的、历史使用频率最高的k个单词，每个占1行。若多个单词历史使用频率相同，则字典序靠前的单词排名靠前。若单词中包含数字，则字典序以ACSII码判定，即0<1<2<…<9<a<b<c<…<z。若字典中满足输出条件的单词个数大于0小于k，则有多少就输出多少个。若字典中没有满足输出条件的单词，则输出“no suggestion”。针对用户每个查询所输出的信息，用空行间隔。

输入样例:
20 3 4
1827187200	the
1595609600	to
1107331800	that
401542500	this
334039800	they
282026500	their
250991700	them
196118888	these
150877900	than
144968100	time
125563600	then
109336600	two
196120000	there
87862100	those
79292500	through
75885600	the
71578000	think
67462300	2
65648600	tx356
57087700	though
th
xxx
the
输出样例:
the
that
this
they

no suggestion

they
their
them
there

代码长度限制
16 KB
时间限制
800 ms
内存限制
64 MB
栈限制
8192 KB
*/

/*
D 智能提示（时间限制更严格）
分数 20
作者 朱允刚
单位 吉林大学
题目内容与前一题完全一致，但时间限制更为严格，若上题程序效率足够高，可直接将代码提交至本题。

备注：本题的测试点其实就是上一题的测试点4、5。如果上一题测试点4、5能在60ms内通过，本题就可以通过了。

输入格式:
与前一题相同。

输出格式:
与前一题相同。

输入样例:
与前一题相同。
输出样例:
与前一题相同。
代码长度限制
16 KB
时间限制
60 ms
内存限制
64 MB
栈限制
8192 KB
*/
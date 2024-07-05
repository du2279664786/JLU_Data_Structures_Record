#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main()
{
    stack<char> q;
    string s;
    // 关闭输入输出缓存，使效率提升
    ios::sync_with_stdio(false);
    // 解除cin和cout的默认绑定，来降低IO的负担使效率提升
    cin.tie(NULL); cout.tie(NULL);
    while(cin >> s)
    {
        for(string::iterator it = s.begin(); it != s.end(); it++)
        {
            if(*it == '(')
            {
                q.push(*it);
            }
            else
            {
                if(!q.empty() && q.top() == '(')
                {
                    q.pop();
                }
                else
                {
                    q.push(*it);
                }
            }
        }

        if(q.empty())
        {
            cout << "Match" << endl;
        }
        else
        {
            cout << q.size() << endl;
            while(!q.empty())
            {
                if(q.top() == ')')
                {
                    s.insert(0, "(");
                }
                else
                {
                    s.push_back(')');
                }
                q.pop();
            }
            cout << s << endl;
        }
    }
    
    
    return 0;
}

/*
B 括号匹配
分数 20
作者 朱允刚
单位 吉林大学
请编写程序判断一个包含“（”和“）”的括号序列是否匹配。如匹配则输出Match；如不匹配，计算出使该序列变为匹配序列所需添加的最少括号数目（只允许在该序列开始和结尾处添加括号），并输出经添加最少括号后得到的合法匹配序列。

输入格式:
输入为若干行，每行一个字符串，包含不超过10 
5
 个括号。输入行数不超过10行。

输出格式:
对于输入的每个括号序列输出1行或2行信息。若输入的括号序列匹配，则输出Match。若不匹配，则输出分为2行，第1行为一个整数，表示将该序列变为匹配序列所需添加的最少括号数目，第2行为一个字符串，表示经添加最少括号后得到的合法匹配序列。

输入样例:
(())()
)(
()))((

输出样例:
Match
2
()()
4
((()))(())

代码长度限制
16 KB
时间限制
20 ms
内存限制
10 MB
*/
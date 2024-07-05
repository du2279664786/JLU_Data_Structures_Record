#include <iostream>
#include <stack>
#include <queue>
#include <string>

using namespace std;

queue<string> revrseNotation;
stack<string> tmpOperater;
stack<char> operater;
stack<int> num;
string s;
int result = -114514;
bool validFlag = true;

int quickPow(int a, int n) // 快速幂
{
    if(n == 0)
        return 1;
    else if(n % 2 == 1)
    {
        return quickPow(a, n - 1) * a;
    }
    else 
    {
        int tempNum = quickPow(a, n / 2);
        return tempNum * tempNum;
    }
}

bool isOperator(char c)
{
    // 判断是否是操作符
    if(c == '*' || c == '+' || c == '-' || c == '/' || c == '^')
    {
        return true;
    }
    return false;
}

int isBracket(char c)
{
    // 判断是否是括号，不是返回0，左括号返回1， 右括号返回2
    if(c == '(')
    {
        return 1;
    }
    else if(c == ')')
    {
        return 2;
    }

    return 0;
}

bool isNum(char c)
{
    // 判断是否是数字
    if(c >= '0' && c <= '9')
    {
        return true;
    }
    return false;
}

int judOpLevel(char c)// 判断操作符优先级
{
    if(c == '+' || c == '-')
    {
        return 1;
    }
    else if(c == '*' || c == '/')
    {
        return 2;
    }
    else if(c == '^')
    {
        return 3;
    }
    else if(c == '(' || c == ')')
    {
        return 0;
    }
    else
    {
        return 5;
    }
}

void editNotation()
{
    // 将每组数字与符号之间加上空格分开,以及最后也补一个空格

    for(int i = 0; i < s.size(); i++)
    {
        //cout << s[i] << endl;
        if(isOperator(s[i]) || isBracket(s[i]) != 0)
        {
            if(isNum(s[i+1]))
            {
                s.insert(i + 1, " ");
            }
            s.insert(i, " ");
            i++;
            //cout << s << endl;
        }
    }
    s.insert(s.size(), " ");
}



void toRevrseNotation()// 转换为后缀表达式
{
    //cout << s << endl;

    for(int i = 0; i < s.size(); i++)
    {
        string tempS;
        for(int j = i; j < s.size(); j++)
        {
            if(s[j] == ' ')
            {
                tempS = string(s, i, j - i);

                if(isOperator(tempS[0])&& (tmpOperater.empty() || (judOpLevel(tempS[0]) > judOpLevel(tmpOperater.top()[0]))))
                {
                    tmpOperater.push(tempS);
                }
                else if(tempS[0] == '(')
                {
                    tmpOperater.push(tempS);
                }
                else if(tempS[0] == ')')
                {
                    if(!tmpOperater.empty())
                    {
                        string s1 = tmpOperater.top();
                        tmpOperater.pop();
                        while(s1[0] != '(')
                        {
                            revrseNotation.push(s1);
                            s1 = tmpOperater.top();
                            tmpOperater.pop();
                        }
                    }
                }
                else if(!tmpOperater.empty()&&(judOpLevel(tempS[0]) <= judOpLevel(tmpOperater.top()[0])))
                {
                    revrseNotation.push(tmpOperater.top());
                    tmpOperater.pop();
                    j--;
                    continue;
                }
                else
                {
                    revrseNotation.push(tempS);
                }
                
                i = j;
                break;
            }
        }
    }   

    while(!tmpOperater.empty())
    {
        revrseNotation.push(tmpOperater.top());
        tmpOperater.pop();
    }
}



int calculateNum(int num1,int num2, char o)// 用传入符号计算传入数字
{
    int result = 114514;
    if(o == '+')
    {
        result = num1 + num2;
    }
    else if(o == '-')
    {
        result = num1 - num2;
    }
    else if(o == '*')
    {
        result = num1 * num2;
    }
    else if(o == '/')
    {
        result = num1 / num2;
    }
    else if(o == '^')
    {
        result = quickPow(num1, num2);
    }

    return result;
}

void calRevrseNotation()//后缀表达式计算
{
    // 在此判断其是操作符号或数字，并开始运算
    while(!revrseNotation.empty())
    {
        string tempS = revrseNotation.front();
        revrseNotation.pop();
        if(tempS.size() > 1 || isNum(tempS[0]))
        {
            num.push(stoi(tempS));
        }
        else
        {
            if(isOperator(tempS[0]))
            {
                int a = num.top();
                num.pop();
                int b = num.top();
                num.pop();

                if(tempS[0] == '/' && a == 0)
                {
                    validFlag = false;
                    return;
                }

                num.push(calculateNum(b, a, tempS[0]));
            }
        }
    }
    result = num.top();
}




int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    
    while(cin >> s)
    {
        result = -114514;
        editNotation();

        validFlag = true;
        queue<string>().swap(revrseNotation);
        stack<int>().swap(num);
        stack<char>().swap(operater);
        toRevrseNotation();

        calRevrseNotation();


        if(validFlag)
        {
            cout << result << endl;
        }
        else
        {
            cout << "INVALID" << endl;
        }


    }



    return 0;
}
/*
C 表达式求值
分数 30
作者 朱允刚
单位 吉林大学
给定一个中缀表达式，请编写程序计算该表达式的值。表达式包含+、-、*、\、^、(、)，所有运算均为二元运算，操作数均为正整数，但可能不止一位，不超过10位。运算结果为整数，值域为[−2 
31
 ,2 
31
 )。除法运算结果若为小数则进行截尾取整。若除法运算中除数为0，则输出INVALID。幂运算须自行实现，不允许调用pow等系统函数。测试数据保证幂运算中指数为非负，底数不为0。

输入格式:
输入为多行，每行为一个长度不超过1000的字符串，表示中缀表达式。

输出格式:
对每个表达式输出一行：为一个整数（表达式的值）或为一个字符串INVALID。

输入样例:
5+(10*2)-6
8*(999+1)
1+5/(1-1)
7*2^3

输出样例:
19
8000
INVALID
56
代码长度限制
16 KB
时间限制
50 ms
内存限制
64 MB
*/
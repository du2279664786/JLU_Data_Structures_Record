#include <iostream>
#include <string>

using namespace std;

int * getNext(string & s)// KMP核心，看不懂
{
    int * next = new int[s.size() + 10];
    next[0] = -1;
    int i = 0, j = -1;
    while(i < s.size() - 1)
    {
        if(j == -1 || s[i] == s[j])
        {
            i++;
            j++;
            next[i] = j;
        }
        else
        {
            j = next[j];
        }
    }
    return next;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int group;
    cin >> group;
    string s;
    int k;
    string tmpS;
    int result = 0;

    while(group > 0)
    {
        cin >> s >> k;
        result = 0;
        tmpS.clear();
        for(int i = 0; i < k; i++)
        {
            tmpS.append("edgnb");
        }

        int * next = getNext(tmpS);

        int i = 0, j = 0;
        int size1 = s.size(), size2 = tmpS.size();
        while(i < size1 && j < size2)
        {
            if(j == -1 || s[i] == tmpS[j])
            {
                
                i++;
                j++;
            }
            else
            {
                j = next[j];
            }
            //cout << i << " " << s.size() << ";" << j << " " << tmpS.size() << endl;
            if(j == tmpS.size())
            {
                result++;
                j -= 5;
                //i -= 5 * k - 5;
            }

        }
        delete[] next;
        next = nullptr;
        cout << result << endl;
        group--;
    }
}
/*
D EDG
分数 20
作者 朱允刚
单位 吉林大学
2021年11月6日，英雄联盟全球总决赛打响，中国电子竞技战队Edward Gaming（EDG）以3:2力克韩国强敌DWG KIA（DK）战队，历史上首次夺得全球总冠军。一时间全网沸腾，大家纷纷在社交平台上直呼“edgnb”。现给定一段文本，请编写程序识别出连续的k个“edgnb”组成的字符串在该文本中出现了多少次。

输入格式:
第一行为1个整数T，表示数据组数。对于每组数据，第一行为1个字符串，表示给定的文本。第二行为1个整数k，含义如题目所述。（1≤T≤10。各组数据给定的字符串长度之和不超过10 
5
 ，且字符串中只包含a-z的小写字母。k≥1且k×5小于给定字符串长度）。

输出格式:
对于每组数据输出一行，为1个整数，表示所求的出现次数。

输入样例:
5
xyzedgnbabcedgnb
1
xyzedgnbabcedgnb
2
defedgnbedgnbxyz
2
edgnbedgnbedgnb
2
fxedgnbedgnbedgnbedgnbmem
3

输出样例:
2
0
1
2
2

数据规模:
测试点0：5≤T≤10，400≤T个字符串长度之和≤500，k=1
测试点1：5≤T≤10，400≤T个字符串长度之和≤500，k≥1
测试点2：5≤T≤10，4000≤T个字符串长度之和≤5000，k≥1
测试点3：1≤T≤3，90000≤T个字符串长度之和≤100000，k≥1
测试点4：1≤T≤3，90000≤T个字符串长度之和≤100000，k≥1

代码长度限制
16 KB
时间限制
400 ms
内存限制
64 MB
*/
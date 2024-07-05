#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

struct huffmanTreeNode
{
	char character;
	int frequency;
	huffmanTreeNode *left;
	huffmanTreeNode *right;

    huffmanTreeNode(char character, int frequency)
	{
		this->character = character;
		this->frequency = frequency;
        this->left = nullptr;
        this->right = nullptr;
	}
};

map<char, string> huffmanCode;
map<char, int> charFrequency;
string charOrder;
string s;
string inputCode;

int minNodeIndex(vector<huffmanTreeNode *> &nodes)
{
    int minIndex = 0;
    int minValue = nodes[0]->frequency;

    for(int i = 1; i < nodes.size(); i++)
    {
        if(nodes[i]->frequency < minValue)
        {
            minValue = nodes[i]->frequency;
            minIndex = i;
        }
        /*
        else if(nodes[i]->frequency == minValue && nodes[i]->character == '0' && nodes[minIndex].character != '0')
        {
            minValue = nodes[i]->frequency;
            minIndex = i;
        }
        */
        
    }
    return minIndex;
}

void preOrderAndMakeCode(huffmanTreeNode * root)
{
    if(root == nullptr)
    {
        return;
    }
    if(root->left == nullptr && root->right == nullptr)
    {
        huffmanCode.insert(pair<char, string>(root->character, s));
        return;
    }
    s.push_back('0');
    preOrderAndMakeCode(root->left);
    s.pop_back();
    s.push_back('1');
    preOrderAndMakeCode(root->right);
    s.pop_back();
}

int sameCompare(vector<huffmanTreeNode*> &nodes, int index)
{
    for(int i = 0; i < nodes.size(); i++)
    {
        if(nodes[index]->frequency == nodes[i]->frequency && i != index)
        {
            if(nodes[index]->character != '0' && nodes[index]->character != '0' && charOrder.find(index) > charOrder.find(i))
            {
                index = i;
                break;
            }
            if((nodes[index]->character != '0' && nodes[i]->character == '0') ||(nodes[index]->character == '0' && nodes[i]->character != '0'))
            {
                if(nodes[index]->character == '0')
                    index = i;
                break;
            }
            if(nodes[index]->character == '0' && nodes[i]->character == '0')
            {
                if(index > i)
                {
                    index = i;
                }
                break;
            }
        }
    }
    return index;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    getline(cin, s);
    inputCode = s;

    // 统计字符频率,并记录字符先后
    for (int i = 0; i < s.length(); i++)
    {
        if(charFrequency.count(s[i]) == 0)
        {
            charFrequency.insert(pair<char, int>(s[i], 1));
            charOrder.push_back(s[i]);
        }
        else
        {
            charFrequency[s[i]]++;
        }
    }

    // 建二叉树
    vector<huffmanTreeNode *> nodes;

    for(auto i = charOrder.begin(); i!= charOrder.end(); i++)
    {
        //cout << *i << endl;
        huffmanTreeNode * p = new huffmanTreeNode(*i, charFrequency[*i]);
        nodes.push_back(p);
        
    }

    /*
    for(int i = 0; i < nodes.size(); i++)
    {
        cout << (*nodes[i]).character << " " << (*nodes[i]).frequency << endl;
    }
    */
    

    while (nodes.size() > 1)
    {
        huffmanTreeNode* p = new huffmanTreeNode('0', 0);
        int tmp = nodes.size();
        int minIndex1 = minNodeIndex(nodes);
        minIndex1 = sameCompare(nodes, minIndex1);
        char minChar1 = nodes[minIndex1]->character;
        p->left = nodes[minIndex1];
        nodes.erase(nodes.begin() + minIndex1);

        int minIndex2 = minNodeIndex(nodes);
        minIndex2 = sameCompare(nodes, minIndex2);
        char minChar2 = nodes[minIndex2]->character;
        p->right = nodes[minIndex2];
        nodes.erase(nodes.begin() + minIndex2);

        p->frequency = p->left->frequency + p->right->frequency;

        //cout << p->character << ";" << minChar1 << ";" << minChar2 << endl;
        
        nodes.push_back(p);
    }
    


    huffmanTreeNode * root = nodes[0];
    s.clear();
    preOrderAndMakeCode(root);

    int zipSize = 0;
    for(int i = 0; i < inputCode.size(); i++)
    {
        zipSize += huffmanCode[inputCode[i]].size();
    }

    if(zipSize % 8 != 0)
    {
        zipSize += 8;
    }
    //cout << zipSize << endl;
    zipSize /= 8;

    cout << inputCode.size() << " " << zipSize << endl;

    for(auto it = charOrder.begin(); it!= charOrder.end(); it++)
    {
        cout << *it << ":" << huffmanCode[*it] << endl;
    }

    
    unordered_map<string, char> decodeSheet;
    
    for(auto it = huffmanCode.begin(); it!= huffmanCode.end(); it++)
    {
        decodeSheet.insert(pair<string, char>(it->second, it->first));
    }
    
    


    string s1;
    string result = "";
    while(getline(cin, s1))
    {
        s.clear();
        for(int i = 0; i < s1.size(); i++)
        {
            s.push_back(s1[i]);
            if(decodeSheet.find(s) != decodeSheet.end())
            {
                result += decodeSheet[s];
                s.clear();
            }
        }

        if(!s.empty())
        {
            cout << "INVALID" << endl;
        }
        else
        {
            cout << result << endl;
        }
	
        /*
        s.clear();
        string resultString = "";
        
        for(auto it : s1)
        {
            s.push_back(it);
            if(decodeSheet.find(s) != decodeSheet.end())
            {
                resultString.push_back(decodeSheet[s]);
                s.clear();
            }
        }

        if(!s.empty())
        {
            cout << "INVALID" << endl;
        }
        else
            cout << resultString << endl;
        
        
        
        huffmanTreeNode * p = root;
        string result = "";
        for(int i = 0; i < s1.size(); i++)
        {
            if(s1[i] == '0')
            {
                p = p->left;
            }
            else
            {
                p = p->right;

            }

            if(p == nullptr)
            {
                break;
            }

            if(p->character != '0')
            {
                result.push_back(p->character);
                p = root;
            }
        }
        if(p == root)
        {
            cout << result << endl;
        }
        else
        {
            cout << "INVALID" << endl;
        }
        
        
        
        */
        
        
    }



    return 0;
}


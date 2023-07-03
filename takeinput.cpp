#include <bits/stdc++.h>
#include "takeinput.hpp"

using namespace std;

void getInput(map<string, vector<vector<string>>> &forward, map<string, vector<string>> &backward, int &nodeNumber)
{
    set<string> st;
    ifstream in("circuit.txt");
    while (!in.eof())
    {
        string text;
        getline(in, text);
        stringstream ss(text);
        string word;
        string out;
        string operat;
        string inp1;
        string inp2;
        int i = 0;
        while (ss >> word)
        {
            if (i == 0)
            {
                out = word;
                st.insert(word);
            }
            else if (i == 2)
            {
                if (word == "~")
                {
                    operat = word;
                }
                else
                {
                    inp1 = word;
                    st.insert(word);
                }
            }
            else if (i == 3)
            {
                if (operat == "~")
                {
                    inp1 = word;
                    st.insert(word);
                }
                else
                    operat = word;
            }
            else if (i == 4)
            {
                inp2 = word;
                st.insert(word);
            }
            i++;
        }
        vector<string> inp1for;
        vector<string> inp2for;
        vector<string> outmap;
        if (operat == "~")
        {
            inp1for.push_back(operat);
            inp1for.push_back(out);
            outmap.push_back(operat);
            outmap.push_back(inp1);
            forward[inp1].push_back(inp1for);
            backward[out] = outmap;
        }
        else
        {
            inp1for.push_back(operat);
            inp1for.push_back(out);
            inp1for.push_back(inp2);
            inp2for.push_back(operat);
            inp2for.push_back(out);
            inp2for.push_back(inp1);
            outmap.push_back(operat);
            outmap.push_back(inp1);
            outmap.push_back(inp2);
            backward[out] = outmap;
            forward[inp1].push_back(inp1for);
            forward[inp2].push_back(inp2for);
        }
    }
    nodeNumber = st.size();
    in.close();
    return;
}

void printInput(map<string, vector<vector<string>>> forward, map<string, vector<string>> backward)
{
    for (auto it : forward)
    {
        cout << it.first << " "
             << ":"
             << " ";
        for (auto it2 : it.second)
        {
            for (auto it3 : it2)
            {
                cout << it3 << " ";
            }
            cout << endl;
        }
    }
    cout << endl;
    for (auto it : backward)
    {
        cout << it.first << " "
             << ":"
             << " ";
        for (auto it2 : it.second)
        {
            cout << it2 << " ";
        }
        cout << endl;
    }
    return;
}

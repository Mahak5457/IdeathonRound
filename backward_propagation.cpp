#include <bits/stdc++.h>
#include "backward_propagation.hpp"

using namespace std;

void backwardPropagation(queue<string> q, map<string, int> it, map<string, vector<string>> &backward, bool &gotAns, map<pair<int, int>, vector<int>> andposs, map<pair<int, int>, vector<int>> orposs, map<pair<int, int>, vector<int>> xorposs)
{
    if (it.find("A") != it.end() && it.find("B") != it.end() && it.find("C") != it.end() && it.find("D") != it.end() && !gotAns)
    {
        ofstream myfile;
        myfile.open("output.txt");
        myfile << "[A, B, C, D] = [" << it["A"] << ", " << it["B"] << ", " << it["C"] << ", " << it["D"] << "], Z = "
             << (1 ^ it["Z"]) << endl;
        myfile.close();
        cout << it["A"] << " " << it["B"] << " " << it["C"] << " " << it["D"] << endl
             << (1 ^ it["Z"]) << endl;
        gotAns = true;
        return;
    }
    while (!q.empty())
    {
        string curr = q.front();
        q.pop();
        int currval = it[curr];
        string inp1 = backward[curr][1];
        string bitoperat = backward[curr][0];
        cout << curr << " " << currval << " " << bitoperat << " " << inp1 << endl;
        if (backward[curr][0] == "~")
        {
            if (backward.find(inp1) != backward.end())
            {
                if (backward[inp1][0] == "~")
                {
                    if (it.find(backward[inp1][1]) == it.end())
                        q.push(inp1);
                }
                else if (it.find(backward[inp1][1]) == it.end() || it.find(backward[inp1][2]) == it.end())
                    q.push(inp1);
            }
            if (it.find(inp1) != it.end())
            {
                if (it[inp1] != 1 ^ currval)
                    return;
            }
            else
            {
                it[inp1] = 1 ^ currval;
                backwardPropagation(q, it, backward, gotAns, andposs, orposs, xorposs);
                return;
            }
        }
        else
        {
            string inp2 = backward[curr][2];
            cout << inp2 << endl;
            if (backward.find(inp1) != backward.end())
            {
                if (backward[inp1][0] == "~")
                {
                    if (it.find(backward[inp1][1]) == it.end())
                        q.push(inp1);
                }
                else if (it.find(backward[inp1][1]) == it.end() || it.find(backward[inp1][2]) == it.end())
                    q.push(inp1);
            }
            if (backward.find(inp2) != backward.end())
            {
                if (backward[inp2][0] == "~")
                {
                    if (it.find(backward[inp2][1]) == it.end())
                        q.push(inp2);
                }
                else if (it.find(backward[inp2][1]) == it.end() || it.find(backward[inp2][2]) == it.end())
                    q.push(inp2);
            }
            if (it.find(inp1) != it.end() && it.find(inp2) != it.end())
            {
                // cout << "hello3" << endl;
                if (bitoperat == "&" && it[inp1] & it[inp2] != currval)
                    return;
                else if (bitoperat == "|" && it[inp1] | it[inp2] != currval)
                    return;
                else if (bitoperat == "^" && it[inp1] ^ it[inp2] != currval)
                    return;
            }
            else if (it.find(inp1) != it.end())
            {
                // cout << "hello2" << endl;
                pair<int, int> key = make_pair(currval, it[inp1]);
                if (bitoperat == "&")
                {
                    if (andposs[key].size() == 0)
                        return;
                    for (auto poss : andposs[key])
                    {
                        it[inp2] = poss;
                        backwardPropagation(q, it, backward, gotAns, andposs, orposs, xorposs);
                    }
                    /* ****** */ return;
                }
                else if (bitoperat == "|")
                {
                    if (orposs[key].size() == 0)
                        return;
                    for (auto poss : orposs[key])
                    {
                        it[inp2] = poss;
                        backwardPropagation(q, it, backward, gotAns, andposs, orposs, xorposs);
                    }
                    /* ****** */ return;
                }
                else
                {
                    for (auto poss : xorposs[key])
                    {
                        it[inp2] = poss;
                        backwardPropagation(q, it, backward, gotAns, andposs, orposs, xorposs);
                    }
                    /* ****** */ return;
                }
            }
            else if (it.find(inp2) != it.end())
            {
                // cout << "hello1" << endl;
                pair<int, int> key = make_pair(currval, it[inp2]);
                if (bitoperat == "&")
                {
                    if (andposs[key].size() == 0)
                        return;
                    for (auto poss : andposs[key])
                    {
                        it[inp1] = poss;
                        backwardPropagation(q, it, backward, gotAns, andposs, orposs, xorposs);
                    }
                    /* ****** */ return;
                }
                else if (bitoperat == "|")
                {
                    if (orposs[key].size() == 0)
                        return;
                    for (auto poss : orposs[key])
                    {
                        it[inp1] = poss;
                        backwardPropagation(q, it, backward, gotAns, andposs, orposs, xorposs);
                    }
                    /* ****** */ return;
                }
                else
                {
                    for (auto poss : xorposs[key])
                    {
                        it[inp1] = poss;
                        backwardPropagation(q, it, backward, gotAns, andposs, orposs, xorposs);
                    }
                    /* ****** */ return;
                }
            }
            else
            {
                // cout << "hello" << endl;
                if (bitoperat == "&")
                {
                    if (currval == 1)
                    {
                        it[inp1] = 1;
                        it[inp2] = 1;
                        backwardPropagation(q, it, backward, gotAns, andposs, orposs, xorposs);
                        return;
                    }
                    else
                    {
                        for (int i = 0; i < 2; i++)
                        {
                            for (int j = 0; j < 2; j++)
                            {
                                if ((i == 0 && j == 1) || (i == 1 && j == 0) || (i == 0 && j == 0))
                                {
                                    it[inp1] = i;
                                    it[inp2] = j;
                                    backwardPropagation(q, it, backward, gotAns, andposs, orposs, xorposs);
                                }
                            }
                        }
                        return;
                    }
                }
                else if (bitoperat == "|")
                {
                    if (currval == 0)
                    {
                        it[inp1] = 0;
                        it[inp2] = 0;
                        backwardPropagation(q, it, backward, gotAns, andposs, orposs, xorposs);
                        return;
                    }
                    else
                    {
                        for (int i = 0; i < 2; i++)
                        {
                            for (int j = 0; j < 2; j++)
                            {
                                if ((i == 0 && j == 1) || (i == 1 && j == 0) || (i == 1 && j == 1))
                                {
                                    it[inp1] = i;
                                    it[inp2] = j;
                                    backwardPropagation(q, it, backward, gotAns, andposs, orposs, xorposs);
                                }
                            }
                        }
                        return;
                    }
                }
                else
                {
                    for (int i = 0; i < 2; i++)
                    {
                        for (int j = 0; j < 2; j++)
                        {
                            if (currval == 0)
                            {
                                if ((i == 0 && j == 0) || (i == 1 && j == 1))
                                {
                                    it[inp1] = i;
                                    it[inp2] = j;
                                    backwardPropagation(q, it, backward, gotAns, andposs, orposs, xorposs);
                                }
                            }
                            else
                            {
                                if ((i == 0 && j == 1) || (i == 1 && j == 0))
                                {
                                    it[inp1] = i;
                                    it[inp2] = j;
                                    backwardPropagation(q, it, backward, gotAns, andposs, orposs, xorposs);
                                }
                            }
                        }
                    }
                    return;
                }
            }
        }
        // cout << "hey" << endl;
    }
    return;
}
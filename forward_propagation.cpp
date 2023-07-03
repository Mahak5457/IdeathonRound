#include <bits/stdc++.h>
#include "forward_propagation.hpp"

using namespace std;

void forwardpropagation(string node, map<string, int> value, map<string, vector<vector<string>>> forward, map<string, int> uncont, vector<map<string, int>> &final)
{
    if (node == "Z")
    {
        final.push_back(value);
    }
    for (auto it : forward[node])
    {
        if (it[0] == "~")
        {
            bool node1 = false;
            if (value.find(it[1]) != value.end())
            {
                if (value[it[1]] != 1 ^ value[node])
                    return;
            }
            else
            {
                node1 = true;
                value[it[1]] = 1 ^ value[node];
            }
            forwardpropagation(it[1], value, forward, uncont, final);
            if (node1)
                value.erase(it[1]);
        }
        else if (it[0] == "^")
        {
            bool node1 = false;
            bool node2 = false;
            vector<string> it2ass;
            if (value.find(it[2]) != value.end())
            {
                int uncontrolled = value[it[2]];
                if (value.find(it[1]) != value.end())
                {
                    if ((uncontrolled == 1 && value[it[1]] == 1 ^ value[node]) || (uncontrolled == 0 && value[it[1]] == value[node]))
                    {
                        forwardpropagation(it[1], value, forward, uncont, final);
                    }
                    else
                    {
                        return;
                    }
                }
                else
                {
                    node1 = true;
                    value[it[1]] = uncontrolled == 0 ? value[node] : 1 ^ value[node];
                    forwardpropagation(it[1], value, forward, uncont, final);
                }
            }
            else
            {
                if (value.find(it[1]) != value.end())
                {
                    node2 = true;
                    value[it[2]] = value[it[1]] == value[node] ? 0 : 1;
                    for (auto point : forward[it[2]])
                    {
                        if (point[0] == "~" || value.find(point[2]) != value.end())
                        {
                            it2ass.push_back(point[1]);
                            if (point[0] == "~")
                                value[point[1]] = 1 ^ value[it[2]];
                            else if (point[0] == "&")
                                value[point[1]] = value[it[2]] & value[point[2]];
                            else if (point[0] == "|")
                                value[point[1]] = value[it[2]] | value[point[2]];
                            else
                                value[point[1]] = value[it[2]] ^ value[point[2]];
                        }
                    }
                    forwardpropagation(it[1], value, forward, uncont, final);
                }
                else
                {
                    node1 = true;
                    node2 = true;
                    value[it[2]] = 1;
                    for (auto point : forward[it[2]])
                    {
                        if (point[0] == "~" || value.find(point[2]) != value.end())
                        {
                            it2ass.push_back(point[1]);
                            if (point[0] == "~")
                                value[point[1]] = 1 ^ value[it[2]];
                            else if (point[0] == "&")
                                value[point[1]] = value[it[2]] & value[point[2]];
                            else if (point[0] == "|")
                                value[point[1]] = value[it[2]] | value[point[2]];
                            else
                                value[point[1]] = value[it[2]] ^ value[point[2]];
                        }
                    }
                    value[it[1]] = 1 ^ value[node];
                    forwardpropagation(it[1], value, forward, uncont, final);
                    for (auto val : it2ass)
                    {
                        value.erase(val);
                    }
                    it2ass.clear();
                    value[it[2]] = 0;
                    for (auto point : forward[it[2]])
                    {
                        if (point[0] == "~" || value.find(point[2]) != value.end())
                        {
                            it2ass.push_back(point[1]);
                            if (point[0] == "~")
                                value[point[1]] = 1 ^ value[it[2]];
                            else if (point[0] == "&")
                                value[point[1]] = value[it[2]] & value[point[2]];
                            else if (point[0] == "|")
                                value[point[1]] = value[it[2]] | value[point[2]];
                            else
                                value[point[1]] = value[it[2]] ^ value[point[2]];
                        }
                    }
                    value[it[1]] = value[node];
                    forwardpropagation(it[1], value, forward, uncont, final);
                }
            }
            if (node1)
                value.erase(it[1]);
            if (node2)
            {
                value.erase(it[2]);
                for (auto val : it2ass)
                {
                    value.erase(val);
                }
                it2ass.clear();
            }
        }
        else
        {
            bool node1 = false;
            bool node2 = false;
            vector<string> it2ass;
            if (value.find(it[2]) != value.end())
            {
                if (value[it[2]] != uncont[it[0]])
                    return;
            }
            else
            {
                node2 = true;
                value[it[2]] = uncont[it[0]];
                for (auto point : forward[it[2]])
                {
                    if (point[0] == "~" || value.find(point[2]) != value.end())
                    {
                        it2ass.push_back(point[1]);
                        if (point[0] == "~")
                            value[point[1]] = 1 ^ value[it[2]];
                        else if (point[0] == "&")
                            value[point[1]] = value[it[2]] & value[point[2]];
                        else if (point[0] == "|")
                            value[point[1]] = value[it[2]] | value[point[2]];
                        else
                            value[point[1]] = value[it[2]] ^ value[point[2]];
                    }
                }
            }
            if (value.find(it[1]) != value.end())
            {
                if (value[it[1]] != value[node])
                    return;
            }
            else
            {
                node1 = true;
                value[it[1]] = value[node];
            }
            forwardpropagation(it[1], value, forward, uncont, final);
            if (node1)
                value.erase(it[1]);
            if (node2)
            {
                value.erase(it[2]);
                for (auto val : it2ass)
                {
                    value.erase(val);
                }
                it2ass.clear();
            }
        }
    }
    return;
}
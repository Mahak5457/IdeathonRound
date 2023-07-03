#ifndef FORWARD_PROPAGATION_HPP
#define FORWARD_PROPAGATION_HPP
#include <bits/stdc++.h>

using namespace std;

void forwardpropagation(string node, map<string, int> value, map<string, vector<vector<string>>> forward, map<string, int> uncont, vector<map<string, int>> &final);

#endif
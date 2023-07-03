#ifndef BACKWARD_PROPAGATION_HPP
#define BACKWARD_PROPAGATION_HPP
#include <bits/stdc++.h>

using namespace std;

void backwardPropagation(queue<string> q, map<string, int> it, map<string, vector<string>> &backward, bool &gotAns, map<pair<int, int>, vector<int>> andposs, map<pair<int, int>, vector<int>> orposs, map<pair<int, int>, vector<int>> xorposs);

#endif
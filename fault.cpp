#include <bits/stdc++.h>
#include "fault.hpp"

using namespace std;

pair<string, int> getFault()
{
    string faultsitedialog;
    string faulttypedialog;
    string faultsite;
    int faulttype;
    getline(cin, faultsitedialog);
    getline(cin, faulttypedialog);
    stringstream ss(faultsitedialog);
    string word;
    int i = 0;
    while (ss >> word)
    {
        if (i == 2)
            faultsite = word;
        i++;
    }
    stringstream ss1(faulttypedialog);
    i = 0;
    while (ss1 >> word)
    {
        if (i == 2)
            faulttype = word[2] - '0';
        i++;
    }
    return make_pair(faultsite, faulttype);
}
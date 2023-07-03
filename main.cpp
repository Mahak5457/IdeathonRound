#include <bits/stdc++.h>
#include "takeinput.hpp"
#include "fault.hpp"
#include "forward_propagation.hpp"
#include "backward_propagation.hpp"

using namespace std;

int main()
{
    //mapping respective gates to their uncontrolling inputs
    map<string, int> uncont;
    uncont["&"] = 1;
    uncont["|"] = 0;

    //mapping to possible values of an input if other input and output of the gate is already decided, for all the three(AND, OR and XOR gate)
    map<pair<int, int>, vector<int>> andposs;
    map<pair<int, int>, vector<int>> orposs;
    map<pair<int, int>, vector<int>> xorposs;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            pair<int, int> key = make_pair(i, j);
            if (i == 0)
            {
                if (j == 0)
                {
                    andposs[key].push_back(0);
                    andposs[key].push_back(1);
                    orposs[key].push_back(0);
                    xorposs[key].push_back(0);
                }
                else
                {
                    andposs[key].push_back(0);
                    xorposs[key].push_back(1);
                }
            }
            else
            {
                if (j == 0)
                {
                    orposs[key].push_back(1);
                    xorposs[key].push_back(1);
                }
                else
                {
                    andposs[key].push_back(1);
                    orposs[key].push_back(0);
                    orposs[key].push_back(1);
                    xorposs[key].push_back(0);
                }
            }
        }
    }

    //mapping the nodes with the gates(and their specifications) they are acting as an input to.
    map<string, vector<vector<string>>> forward;
    //mapping the nodes with the gates(and their specifications) they are an output of.
    map<string, vector<string>> backward;
    //marking the number of nodes present in the circuit
    int nodeNumber;
    //storing input in the previously declared maps from the cicuit information given in "circuit.txt" file.
    getInput(forward, backward, nodeNumber);
    // cout << nodeNumber << endl;
    //priting both the populated map
    // printInput(forward, backward);
    pair<string, int> fault;
    //asking for the fault site and fault type(in the given format) from the user.
    fault = getFault();
    //printing fault site and fault type
    string faultsite = fault.first;
    int faulttype = fault.second;
    cout << faultsite << " SA" << faulttype << endl;
    //declaring map to hold possible value for nodes during forward propagation
    map<string, int> value;
    //FAULT SENSITISING, sesnsitizing fault site with the value opposite to the stuck at fault
    if (faulttype == 0)
        value[faultsite] = 1;
    else
        value[faultsite] = 0;
    //vector of maps to store all the feasible combinations during forward propagation 
    vector<map<string, int>> final;
    //propapgating the fault forward towards the primary output
    forwardpropagation(faultsite, value, forward, uncont, final);

    //if we get a test vector satisfying one of the combinations formed during forward propagation then we will set the belo variable to true
    bool gotans = false;

    for (auto it : final)
    {
        //printing the feasible combinations resulted during forward propagation
        // cout << endl;
        // for (auto it1 : it)
        // {
        //     cout << it1.first << " : " << it1.second << endl;
        // }

        //justifuing each of the comination one by one
        //if any of the combination gets justified resulting in a valid test vector then 
        //THE TEST VECTOR AND THE EXPECTED OUTPUT DURING PRESENCE OF FAULT WILL BE PRINTED IN THE "outputtxt" FILE
        //the loop will also terminate on the derivation of a valid test vector.
        queue<string> q;
        for (auto it1 : it)
        {
            //for every node which has a value already assigned, if any of its input is not assigned than that node is pushed into the queue
            //not gate is specially being processed.
            string curr = it1.first;
            if (backward.find(curr) != backward.end())
            {
                if (backward[curr][0] == "~")
                {
                    if (it.find(backward[curr][1]) == it.end())
                    {
                        q.push(curr);
                        // cout << curr << endl;
                    }
                }
                else if ((it.find(backward[curr][1]) == it.end() || it.find(backward[curr][2]) == it.end()))
                {
                    q.push(curr);
                    // cout << curr << endl;
                }
            }
        }
        // once all the valid nodes in a forward valid combination are pushed inside the queue the justification starts.
        backwardPropagation(q, it, backward, gotans, andposs, orposs, xorposs);
        //the gotans variable being passes as a reference in the justificaiton process, if turns to be true, that is a test vector is found, 
        //then the loop terminates as there is no need to process any further combinations from forward propagation.
        if (gotans)
            break;
    }
    return 0;
}
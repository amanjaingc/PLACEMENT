#include<vector>
#include<iostream>
#include<algorithm>
using namespace std;
void dfa_minimize()
{
    int min_no_of_states;
    vector< vector<int> > MIN_DFA
    vector< vector<int> > temp;
    if(compare(dfa_initial,dfa_final))
    {
        min_no_of_states = 1;
        MIN_DFA[0][1] = 0;
        MIN_DFA[0][2] = 0;
        return;
    }
    min_no_of_states = 2;
    temp.push_back(dfa_initial);temp.push_back(dfa_final);
    for(int i=0;i<min_no_of_states;i++)
    {
        for(int j=0;j<temp[i].size();j++)
        {
            for(int k=0;k<temp[i].size();k++)
            {
                if(temp[i][k]==DTable[temp[i][j]][1])
                    MIN_DFA[i][1] = i;
                else if(temp[i][k]==DTable[temp[i][j]][2])
                    MIN_DFA[i][2] = i;
            }
            DFA[i][1] = DTable[temp[i][j]][1];
            DFA[i][2] = DTable[temp[i][j]][2];
        }
    }




}





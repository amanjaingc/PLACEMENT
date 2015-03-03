#include<vector>
#include<algorithm>
#include<iostream>

void print_min_dfa()
{
    int DFA_MIN[100][3];
    int mapped_state;

    vector<int> min_dfa_final;
    for(int i=0;i<dfa_initial;i++)
        min_dfa_final.push_back(minmap[dfa_initial[i]]);


    for(int i=0;i<num;i++)
    {
        mapped_state = minmap[i];
        vector<int> min_dfa_initial;
        min_dfa_initial.push_back(minmap[dfa_initial[0]]);

        if(DTable[i][1]!=-1)
            DFA_MIN[mapped_state][1] = minmap[DTable[i][1]];
        if(DTable[i][2]!=-1)
            DFA_MIN[mapped_state][2] = minmap[DTable[i][2]];
    }

        cout<<endl<<endl<<"Transition Table for Minimized DFA is as follows:"<<endl;
        cout<<"Initial State for Minimized DFA Is: ";
        for(int i=0;i<min_dfa_initial.size();i++)
            cout<<min_dfa_initial[i]<<" ";
        cout<<endl<<"Final States for Minimized DFA Is: ";
        for(int i=0;i<min_dfa_final.size();i++)
            cout<<min_dfa_final[i]<<" ";
        cout<<endl;
        for(int i=0;i<MIN_DFA_SIZE;i++)
        {
            cout<<"Transitions for state "<<i<<" are:"<<endl;
            cout<<"On input 'a': {";
            if(DFA_MIN[i][1]!=-1)
                cout<<DTable[i][1]<<", ";
            cout<<"}"<<endl;
            cout<<"On input 'b': {";
            if(DTable[i][2]!=-1)
                cout<<DTable[i][2]<<", ";
            cout<<"}"<<endl;
        }

    }



}

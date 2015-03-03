#include<stdio.h>
#include<vector>
#include<iostream>
using namespace std;

main()
{
    int i=5;
    cout<<char(i+48)<<endl;
    return 0;
}

char tochar(int i)
{
    return char(i+48);
}


void dfa_minimize()
{
    int min_no_of_states;
    vector< vector<int> > MIN_DFA;
    vector< vector<int> > temp;
    if(compare(dfa_initial,dfa_final))
    {
        min_no_of_states = 1;
        MIN_DFA[0][1] = 0;
        MIN_DFA[0][2] = 0;
        return;
    }
    min_no_of_states = 2;
    for(int i=0;i<dfa_initial;i++)
        pst_vector[dfa_initial[i]]=0;
    for(int i=0;i<dfa_final;i++)
        pst_vector[dfa_final[i]]=1;

    temp.push_back(dfa_initial);temp.push_back(dfa_final);

    int i1,i2;
    char c1,c2;
    string concat;
    for(int i=0;i<min_no_of_states;i++)
    {
        for(int j=0;j<temp[i].size();j++)
        {
            i1=pst_vector[DTable[temp[i][j]][1]];
            i2=pst_vector[DTable[temp[i][j]][2]];
            a1 = tochar(i1);a2 = tochar(i2);
            concat+=a1;concat+=a2;
            mapping[temp[i][j]] = concat;
        }
    }

    for(int i=0;i<min_no_of_states;i++)
    {
        for(int j=0;j<temp[i].size();j++)
        {
            for(int k=j+1;k<temp[i].size();k++)
            {
                if(!visited[temp[i][j]])
                {
                    v.push_back(temp[i][j]);
                    if(!visited[temp[i][k]] && mapping[temp[i][j]]==mapping[temp[i][k]])
                    {
                        visited[temp[i][k]] = true;
                        v.push_back(temp[i][k]);
                    }
                }
            }
            if(v.size()==temp[i].size())
                break;
            else
            {
                min_no_of_states++;
                temp.push_back(v);
                v.erase();
            }


        }

    }



}


#include<vector>


bool simulation(string input,map<int> m,int ini,vector<int> fin)
{
    if(input=="E")
        return false;
    int pst_state = ini,val;
    for(int i=0;i<input.size();i++)
    {
        if(input[i]=='a')
            val=1;
        else
            val=2;

        if(m[val]==-1)
            return false;
        pst_state = m[val];
    }
    for(int i=0;i<fin.size();i++)
    {
        if(fin[i]==pst_state)
            return true;
    }
    return false;
}

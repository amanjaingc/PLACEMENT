
bool simulation(string input,vector<int> ini,vector<int> fin)
{
    if(input=="E")
        return false;
    int pst_state = ini[0],val;
    for(int i=0;i<input.size();i++)
    {
        if(input[i]=='a')
            val=1;
        else
            val=2;

        if(DTable[pst_state][val]==-1)
            return false;
        pst_state = DTable[pst_state][val];
    }
    for(int i=0;i<fin.size();i++)
    {
        if(fin[i]==pst_state)
            return true;
    }
    return false;
}


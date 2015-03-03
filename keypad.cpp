#include<iostream>
#include<string>
using namespace std;

long long int func(string a)
{
    long long int count = 0;
    for(int i=0;i<a.length();i++)
    {
        count+=(int)(a[i]-96);
    }
    return count;
}

main()
{
    int t;
    string s;
    cin>>t;
    while(t--)
    {
        cin>>s;
        cout<<func(s)<<endl;
    }
    return 0;
}

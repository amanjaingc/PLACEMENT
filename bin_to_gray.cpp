#include<iostream>
#include<string>
using namespace std;
int main()
{
    int t;
    string a;
    cin>>t;
    while(t--)
    {
        cin>>a;
        cout<<a[0];
        for(int i=1;i<a.length();i++)
            cout<< ((a[i]-48) ^ (a[i-1]-48));
        cout<<endl;
    }
    return 0;
}

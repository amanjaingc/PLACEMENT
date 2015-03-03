#include <iostream>
#include <map>
using namespace std;
main()
{
    long int t,n,a[10001],b[10001];
    cin>>t;
    while(t--)
    {
        cin>>n;
        map<long long int,long int> mymap;
        int mapped = 0;
        for(int i=0;i<n;i++)
        {
            cin>>a[i];
            if(!mymap[a[i]])
            {
                ++mapped;
                mymap[a[i]] = mapped;
            }
            b[mymap[a[i]]]++;
        }
        int done = 0;
        for(int i=0;i<n;i++)
        {
            if(b[mymap[a[i]]]>(n/2)){
                cout<<a[i]<<endl;
                done = 1;
                break;
            }
        }
        if(!done)
            cout<<"NO MAJOR"<<endl;
    }
    return 0;
}



#include<iostream>
#include<string>
using namespace std;

main()
{
    long long int n,m,q,a1,a2,ans,count;
    cin>>n>>m;
    while(m--)
    {
        cin>>q;
        count=0;
        if(q<=(n+1))
            ans = 0;
        else
        {
            for(long long int i=1;i<=n;i++)
            {
                if((q-i)>=(n+1) && (q-i)<=2*n)
                {
                 //   index = i;
                    a1 = n-i+1;
                    a2 = q-i-(n+1)+1;
                    ans = min(a1,a2);
                    break;
                }
            }
        }
        cout<<ans<<endl;
    }
    return 0;

}

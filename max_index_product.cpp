#include<iostream>
using namespace std;
#define lli long long int
int main()
{
    lli n,t;



        cin>>n;
        lli a[n+1];
        for(lli i=1;i<=n;i++)
            cin>>a[i];
        lli left[n+1];
        left[1] = 0;
        lli temp;
        for(lli i=2;i<=n;i++)
        {
            if(a[i-1] > a[i])
                left[i] = i-1;
            else
            {
                temp = left[i-1];
                while(true)
                {
                    if(temp == 0)
                    {
                        left[i] = temp;
                        break;
                    }
                    else if(a[temp] > a[i])
                    {
                        left[i] = temp;
                        break;
                    }
                    temp = left[temp];
                }
            }
        }
        lli right[n+1];
        right[n] = 0;
        for(lli i=n-1;i>=0;i--)
        {
            if(a[i+1] > a[i])
                right[i] = i+1;
            else
            {
                temp = right[i+1];
                while(true)
                {
                    if(temp==0)
                    {
                        right[i] = temp;
                        break;
                    }
                    else if(a[temp] > a[i])
                    {
                        right[i] = temp;
                        break;
                    }
                    temp = right[temp];
                }
            }
        }
        lli max = 0;
        for(lli i=1;i<=n;i++)
        {
            temp = left[i]*right[i];
            if(temp > max)
                max = temp;
        }
        cout<<max<<endl;

    return 0;
}

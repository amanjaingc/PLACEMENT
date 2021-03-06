#include<iostream>
#include<stdio.h>
#include<algorithm>
#include<stdlib.h>
using namespace std;

struct jobs{
int start_t;
int finish_t;
};
int compare(jobs a,jobs b)
{
    return (a.finish_t < b.finish_t);
}



int main()
{
    int t,n,count,latest_finish;
    cin>>t;
    while(t--)
    {
        count=1;
        cin>>n;
        jobs a[n];
        for(int i=0;i<n;i++)
            cin>>a[i].start_t;
        for(int i=0;i<n;i++)
            cin>>a[i].finish_t;
        sort(a,a+n,compare);
  /*      for(int i=0;i<n;i++)
        {
            cout<<a[i].start_t<<" "<<a[i].finish_t<<endl;
        }
*/        latest_finish = a[0].finish_t;
        for(int i=1;i<n;i++)
        {
            if(a[i].start_t >= latest_finish)
            {
                count++;
                latest_finish = a[i].finish_t;
            }
        }
        cout<<count<<endl;
    }
    return 0;
}

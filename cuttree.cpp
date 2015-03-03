#include<iostream>
#include<stdlib.h>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;

int main()
{
    int n;
    cin>>n;
    int w[100001],tot=0,U[n+1],V[n+1];
    for(int i=1;i<=n;i++)
    {
        cin>>w[i];
        tot+=w[i];
    }
    int l,r;
    vector<int> v[n+1];
    for(int i=1;i<n;i++)
    {
        cin>>l>>r;
        v[l].push_back(r);
        v[r].push_back(l);
        U[i]=l;  V[i]=r;
    }


    int min=100000;
    int sum=0;
    for(int i=1;i<n;i++)
    {
        int* vis = new int[n+1];
        vis[n+1]={0};
        for(int j=1;j<=n;j++)
            vis[j] = 0;
        queue<int> Q;
        Q.push(U[i]);
        vis[U[i]] = 1;
        sum = w[U[i]];
        while(Q.size()>0)
        {
            for(int j=0;j<v[Q.front()].size();j++)
            {
                if(v[Q.front()][j]!=V[i] && !vis[v[Q.front()][j]])
                {
                    vis[v[Q.front()][j]]=1;
                    Q.push(v[Q.front()][j]);
                    sum+=w[v[Q.front()][j]];
                }
            }
            Q.pop();
        }
        free(vis);
//        cout<<sum<<endl;
        if(sum>=tot/2)
            sum = tot-sum;
        sum=tot-2*sum;
        if(sum<min)
            min=sum;
    }
    cout<<min<<endl;
    return 0;
}

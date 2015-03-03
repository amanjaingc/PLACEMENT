#include<iostream>
#include<stdlib.h>
#include<algorithm>
#include<vector>
#include<stack>
#include<queue>
using namespace std;

int mod(int a)
{
    if(a<=0)
        return -a;
    else
        return a;
}

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
    int A[n+1];
    for(int i=0;i<=n;i++)
        A[i]=0;
    int dis[n+1];
    dis[1] = 0;

    queue<int> Q;
    Q.push(1);
    Q.push(-11);
    A[1] = 1;
    int k=1;
    while(Q.size()>0)
    {
        if(Q.front()==-11 && Q.size()==1)
            break;
        else if(Q.front()==-11 && Q.size()>1)
        {
            k++;
            Q.pop();
            Q.push(-11);
        }
        for(int i=0;i<v[Q.front()].size();i++)
        {
            if(!A[v[Q.front()][i]])
            {
                Q.push(v[Q.front()][i]);
                dis[v[Q.front()][i]] = k;
                A[v[Q.front()][i]] = 1;
            }
        }
        Q.pop();
    }


    cout<<"Distances from 1 are as follows:"<<endl;
    for(int i=1;i<=n;i++)
    {
        cout<<"for "<<i<<" :"<<dis[i]<<endl;
    }

    for(int i=1;i<=n;i++)
    {
        cout<<"connections with "<<i<<"are:"<<endl;
        for(int j=0;j<v[i].size();j++)
            cout<<v[i][j]<<" ";
        cout<<endl;
    }


    int min=100000;
    int sum=0;
    int W[n+1];
    for(int j=1;j<=n+1;j++)
        W[j] = 0;

    stack<int> S;
    int* vis = new int[n+1];
    for(int j=1;j<=n;j++)
        vis[j] = 0;
    S.push(1);
    vis[1] = 1;
    int am;
    while(S.size()>0)
    {
        while(true)
        {
            am=0;
            for(int j=0;j<v[S.top()].size();j++)
            {
                if(!vis[v[S.top()][j]])
                {
                    cout<<v[S.top()][j]<<"entered"<<endl;
                    vis[v[S.top()][j]] = 1;
                    S.push(v[S.top()][j]);
                    j=0;
                    am=1;
                    break;
                    am=1;
                    continue;
                }
            }
            if(!am) break;
        }
        for(int j=0;j<v[S.top()].size();j++)
        {
            W[S.top()] += W[v[S.top()][j]];
        }
        W[S.top()] += w[S.top()];
        S.pop();
    }

    cout<<"Weights are as follows:"<<endl;
    for(int i=1;i<=n;i++)
        cout<<"for "<<i<<": "<<W[i]<<endl;
    int temp;
    for(int i=1;i<n;i++)
    {
        if(dis[U[i]]<dis[V[i]])
        {
            temp = tot-W[V[i]];
            temp = mod(temp-W[V[i]]);
        }
        else
        {
            temp = tot-W[U[i]];
            temp = mod(temp-W[U[i]]);
        }
        if(temp<min)
            min = temp;
    }
    cout<<min<<endl;
    return 0;
}

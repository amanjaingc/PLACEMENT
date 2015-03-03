#include<iostream>
using namespace std;


bool issubset(int a[],int b[],int c[],int n,int P,int C,int F)
{
    bool subset[P+1][C+1][F+1][n+1];
    for(int i=0;i<=n;i++)
        subset[0][0][0][i]=true;
    for(int i=1;i<=P;i++)
    {
        for(int j=1;j<=C;j++)
        {
            for(int k=1;k<=F;k++)
            {
                subset[i][j][k][0]=false;
                for(int l=0;l<=n;l++)
                {
                    subset[0][j][k][l]=false;
                    subset[i][0][k][l]=false;
                    subset[i][j][0][l]=false;
                }
            }
        }
    }

    for(int i=1;i<=P;i++)
    {
        for(int j=1;j<=C;j++)
        {
            for(int k=1;k<=F;k++)
            {
                for(int l=1;l<=n;l++)
                {
                    subset[i][j][k][l] = subset[i][j][k][l-1];
                    if((i>=a[l-1] && j>=b[l-1] && k>=c[l-1]))
                        subset[i][j][k][l] = (subset[i][j][k][l] || subset[i-a[l-1]][j-b[l-1]][k-c[l-1]][l-1]);
                }
            }
        }
    }
    return subset[P][C][F][n];
}


int t,P,C,F,n,a[25],b[25],c[25];
int main()
{
bool issubset(int a[],int b[],int c[],int n,int P,int C,int F);

    cin>>t;
    while(t--)
    {
        cin>>P>>C>>F;
        cin>>n;
        for(int i=0;i<n;i++)
            cin>>a[i]>>b[i]>>c[i];
        if(issubset(a,b,c,n,P,C,F)==true)
            cout<<"Case #"<<(i+1)<<": "<<"yes"<<endl;
        else
            cout<<"Case #"<<(i+1)<<": "<<"no"<<endl;
    }
    return 0;
}

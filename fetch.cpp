#include<iostream>
using namespace std;
int main()
{
    int m,n;
    cin>>m>>n;
    char a[m+1][n+1];
    for(int i=0;i<m;i++)
        for(int j=0;j<n;j++)
            cin>>a[i][j];
    int left[m+1][n+1],up[m+1][n+1];
    left[0][0]=0;
    up[0][0]=0;
    for(int j=1;j<n;j++)
    {
        if(a[0][j]!='x' && a[0][j-1]!='x')
            left[0][j] = left[0][j-1] + 1;
        else
            left[0][j]=0;
        up[0][j] = 0;
    }

    for(int j=1;j<m;j++)
    {
        if(a[j][0]!='x' && a[j-1][0]!='x')
            up[j][0] = up[j-1][0] + 1;
        else
            up[j][0] = 0;
        left[j][0] = 0;
    }
    int max=0;
    for(int i=1;i<m;i++)
    {
        for(int j=1;j<n;j++)
        {
            if(a[i][j]=='x')
            {
                left[i][j]=0;
                up[i][j]=0;
            }
            else
            {
                if(a[i][j-1]!='x')
                    left[i][j] = left[i][j-1]+1;
                if(a[i][j-1]=='x')
                    left[i][j] = 0;
                if(a[i-1][j]!='x')
                    up[i][j] = up[i-1][j] +1;
                if(a[i-1][j]=='x')
                    up[i][j] = 0;
            }
        }
    }
    for(int i=0;i<m;i++)
        for(int j=0;j<n;j++)
            if(left[i][j]+up[i][j] > max)
                max = left[i][j]+up[i][j];
    if(max!=0)
    cout<<2*max<<endl;
    else
        cout<<"impossible"<<endl;
    return 0;
}

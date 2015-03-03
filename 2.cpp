#include<iostream>
using namespace std;
/*

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
*/

bool issubset(int l[], int n, int sum)
{
    // The value of subset[i][j] will be true if there is a subset of set[0..j-1]
    //  with sum equal to i
    bool subset[sum+1][n+1];

    // If sum is 0, then answer is true
    for (int i = 0; i <= n; i++)
      subset[0][i] = true;

    // If sum is not 0 and set is empty, then answer is false
    for (int i = 1; i <= sum; i++)
      subset[i][0] = false;

     // Fill the subset table in botton up manner
     for (int i = 1; i <= sum; i++)
     {
       for (int j = 1; j <= n; j++)
       {
         subset[i][j] = subset[i][j-1];
         if (i >= l[j-1])
           subset[i][j] = subset[i][j] || subset[i - l[j-1]][j-1];
       }
     }

    /* // uncomment this code to print table
     for (int i = 0; i <= sum; i++)
     {
       for (int j = 0; j <= n; j++)
          printf ("%4d", subset[i][j]);
       printf("\n");
     } */

     return subset[sum][n];
}

int t,P,C,F,n,a,b,c,l[22],s;
int main()
{
    //bool issubset(int a[],int b[],int c[],int n,int P,int C,int F);
    cin>>t;
    for(int k=1;k<=t;k++)
    {
        cin>>P>>C>>F;
        cin>>n;
        for(int i=0;i<n;i++)
        {
            cin>>a>>b>>c;
            l[i] = a+b+c;
	    s=i;
        }

        if(issubset(l,n,P+C+F)==true)
  	cout<<"Case #"<<(k)<<": "<<"yes"<<endl;          
        else
            cout<<"Case #"<<(k)<<": "<<"no"<<endl;
    }
    return 0;
}

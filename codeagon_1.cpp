#include<iostream>
using namespace std;
#define lli long long int
#define N 1000000000
#define T long long int

T modpow(T base, T exp, T modulus) {
  base %= modulus;
  T result = 1;
  while (exp > 0) {
    if (exp & 1) result = (result * base) % modulus;
    base = (base * base) % modulus;
    exp >>= 1;
  }
  return result;
}


lli pow(lli a,lli b)
{
    if(b==0) return 1;
    lli temp = (pow(a,b/2))%N;
    if(b%2==0)
        return (temp*temp)%N;
    else
        return (temp*temp*a)%N;
}

lli ceil(lli a,lli b)
{
    if(a%b==0) return (a/b);
    else
    return (a/b + 1);
}

lli func(lli n)
{
    if(n<3) return 1;
    else if (n<=4) return 3;
    else if(n<=6) return 15;
    else if(n<=10) return 105;
    else
    {
        lli ans=1;
        lli a =ceil(n,4);
        ans*=pow(2,a);
        lli b = (ceil(n,5));
        ans*=func(b);
        lli c = (ceil(n,10));
        ans*=func(c);
        return ans;
    }
}

main()
{
    lli t,num;
    cin>>t;
    cout<<modpow(144,192,N);
    while(t--)
    {
        cin>>num;
        cout<<func(num)<<endl;
    }
    return 0;
}

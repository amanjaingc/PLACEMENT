#include<iostream>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

int size = 0,a[10001];

void insert(int a[],int val)
{
    size++;
    a[size] = val;
    int parent = size/2;
    int  self = size;
    while(parent)
    {
        if(a[self]<a[parent])
        {
            int t = a[parent];
            a[parent] = a[self];
            a[self] = t;
            self = parent;
            parent/=2;
        }
        else
            break;
    }
    return;
}


int extract_min(int a[])
{
    if(size==0) return -1;
    int ret = a[1];
    a[1] = a[size];
    size--;
    int i=1;
    while(i<size)
    {
        if((2*i + 1)<=size)
        {
            if(a[i]<min(a[2*i],a[2*i + 1]))
                break;
            else
            {
                if(a[2*i]==min(a[2*i],a[2*i + 1]))
                {
                    int t = a[i];
                    a[i] = a[2*i];
                    a[2*i] = t;
                    i = 2*i;
                }
                else if(a[2*i + 1]==min(a[2*i],a[2*i + 1]))
                {
                    int t = a[i];
                    a[i] = a[2*i + 1];
                    a[2*i + 1] = t;
                    i = 2*i + 1;
                }
            }
        }
        else if((2*i)==size)
        {
            if(a[i]>a[2*i])
            {
                int t = a[i];
                a[i] = a[2*i];
                a[2*i] = t;
            }
            break;
        }
        else if(2*i > size)
        {
            break;
        }
    }
    return (ret);
}

int main()
{
    insert(a,4);insert(a,7);insert(a,1);insert(a,12);insert(a,5);insert(a,9);
    while(size)
        cout<<extract_min(a)<<endl;
    return 0;
}

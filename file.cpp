#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
main()
{
    FILE *fp_1 = fopen("/home/aman/Desktop/codes/newfile.txt","r");

    char ch,a[1000000];int i=0;
    while((ch = fgetc(fp_1)) != EOF)
    {
        a[i] = ch;
        cout<<ch<<endl;
        i++;
    }
    fclose(fp_1);

    FILE *fp_2 = fopen("/home/aman/Desktop/codes/newfile.txt","w");
    fputs(a,fp_2);

    fclose(fp_2);
    return 0;
}

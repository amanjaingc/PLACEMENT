#include<stdio.h>
#include<stdlib.h>
main()
{
    FILE *fp = fopen("cs101.txt","r");
    char ch;
    int i=10;
    while(i--)
    {
        ch = fgetc(fp);
        printf("%c\n",ch);
 //       cout<<ch<<endl;
    }
    return 0;
}

#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
main()
{
    FILE *fp_1 = fopen("cs101.txt","r");

    char ch,a[1000000];int i=0;
    while((ch = fgetc(fp_1)) != EOF)
    {
        if(ch=='\n')
            ch = '$';
        a[i] = ch;
        i++;
    }
    a[i] = '$';i++;
    fclose(fp_1);

    FILE *fp_2 = fopen("newfile.txt","w");
    fputs(a,fp_2);
    fclose(fp_2);

    FILE *fp_cs = fopen("cs.txt","w");
    FILE *fp_ma = fopen("ma.txt","w");

    char space[1],newline[1];
    space[0] = '\t';
    newline[0] = '\n';
    fp_2 = fopen("newfile.txt","r");
    char roll[10],name[40];
    while(true)
    {
        memset(roll,0,10);
        memset(name,0,40);
       // name = "";roll = "";
        i=0;
        while((ch = fgetc(fp_2)))
        {
            if(ch==',')
                break;
            roll[i]=ch;i++;
        }

        ch = fgetc(fp_2);
        //    break;
//        fp_2++;   //reached to first character of name
        i=0;
        while((ch = fgetc(fp_2)))
        {
            if(ch==',')
                break;
            name[i]=ch;i++;
        }

        if(roll[3]=='1')
        {
            fputs(roll,fp_cs);
            fputs("\t",fp_cs);
            fputs(name,fp_cs);
            fputs("\n",fp_cs);
        }
        else if(roll[3]=='2')
        {
            fputs(roll,fp_ma);
            fputs("\t",fp_ma);
            fputs(name,fp_ma);
            fputs("\n",fp_ma);
        }

        while((ch = fgetc(fp_2)))
        {
            if(ch=='$')
            {
//                fp_2++;
                break;
            }
        }
        ch = fgetc(fp_2);
//            break;
        ch = fgetc(fp_2);
//            break;

        //ch = fgetc(fp_2);

        if(ch=='$')
            break;

    }
    fclose(fp_2);fclose(fp_cs);fclose(fp_ma);

    return 0;
}

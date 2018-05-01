#include<stdio.h>
#include<conio.h>
#include<string.h>

struct raj
{
    char *p;
};
struct raj a;
int main()
//char main()
{
    //char a[12]={"akshay"},*b="aksh patel";
    char *ap;
    ap="rajkot";
    a.p=ap;
    a.p="jetpur";
    //a.p=ap;
    //printf("a=%s\t b=%s\n",a,b);

    //a="aksh";
    //fflush(stdin);
    //a[12]="aks";
    //a[12]={"aksh"};
    //a={"aksh"};
    //b="raj";
    //fflush(stdin);
    //b="raj";

    //printf("a=%s\t b=%s\n",a,b);
    //here a should be aksh and b shoulbe


    printf("\n\nap=%s \n",ap);
    fflush(stdin);
    printf("a.p=%s",a.p);

    getch();
    return 0;
}

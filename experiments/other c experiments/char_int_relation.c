#include<stdio.h>
#include<conio.h>

void main()
{
    int a;
    char ap,pa;

    ap=97;

    printf("ap: %c\n\n",ap);
    a=getchar();
    switch(a)
    {
    case 97:
        printf("a");
        break;
    case 98:
        printf("b");
        break;
    case 99:
        printf("c");
        break;
    default:
        printf("invalid");
    }
}


#include<stdio.h>
#include<conio.h>

int main()
{
    system("cls");

    int i=0;

    //for(i=0;i<=10;i++)
    while(i<=10)
    {
        if(i==5)
        {
            //break;
            continue;
        }
        printf("%d\t",i);
        i++;
    }
    getch();
    return 0;
}

#include<stdio.h>
#include<conio.h>

int main()
{
        int counter=0,ch,a,ap;
        FILE *fp;




    fp=fopen("count_file_exp.dat","r");
    counter=getw(fp);
    printf("aa=%d",counter);
    ap=counter;
    fclose(fp);
    fp=fopen("count_file_exp.dat","w");

    if(ap>=0)
    {

    counter++;
    }
    else
    {
        counter=0;
                counter++;

    }

    putw(counter,fp);
    fclose(fp);
    getch();


    fp=fopen("count_file_exp.dat","r");
    a=getw(fp);
    ch=a;
    printf("a=%d\tch=%d",a,ch);
    fclose(fp);
    getch();

    return 0;

}

#include<stdio.h>
#include<conio.h>

int main()
{
    FILE *fp;
    int ch;
    fp=fopen("file_exp.dat","ab+");
    fread(&counter,sizeof(counter),1,fp);
    ch=counter;
    printf("counter=%d\tch=%d",counter,ch);
    fclose(fp);
    getch();
    return 0;

}



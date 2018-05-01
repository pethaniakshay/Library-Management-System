#include<stdio.h>
#include<conio.h>

int main()
{
        int counter,ch,a;
        FILE *fp;

    scanf("%d",&a);
    switch(a)
    {
        case 1:
    fp=fopen("count_file_exp.dat","w");
    printf("enter value of counter: ");
    scanf("%d",&counter);
    //fclose(fp);
    counter++;
    putw(counter,fp);
    //fseek(fp,0,SEEK_END);
    //fwrite(&counter,sizeof(counter),1,fp);
    fclose(fp);
    getch();
    break;


        case 2:


    fp=fopen("count_file_exp.dat","r");
    counter=getw(fp);
    //fread(&counter,sizeof(counter),1,fp);
    ch=counter;
    printf("counter=%d\tch=%d",counter,ch);
    fclose(fp);
    getch();

    break;
    }
    return 0;

}

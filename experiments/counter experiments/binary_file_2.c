#include<stdio.h>
#include<conio.h>

struct ap
{
int aa,bb,cc;
};

struct ap p;

int main()
{
    FILE *fp;

    int aaa,ch,cd,a;

    system("cls");
    fp=fopen("binary_file_1.dat","ab+");
    fseek(fp,0,SEEK_END);
    p.aa=99;
    p.bb=45;
    p.cc=10;

    fwrite(&p,sizeof(p),1,fp);
    fclose(fp);
    p.aa++;
    p.bb++;
    p.cc++;

   fp=fopen("binary_file_1.dat","ab+");

    fread(&p,sizeof(p),1,fp);
    printf("\n\na=%d\tb=%d\tc=%d",p.aa,p.bb,p.cc);
    fclose(fp);

    return 0;
}

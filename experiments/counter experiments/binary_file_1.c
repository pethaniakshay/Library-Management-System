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

    int aaa;
    p.aa=0;
    p.bb=0;
    p.cc=0;
    system("cls");

        fp=fopen("binary_file_1.dat","ab+");
        fread(&p,sizeof(p),1,fp);
        aaa=p.aa;
        printf("aaa=%d\tp.aa=%d\n\n",aaa,p.aa);
        fclose(fp);
        printf("aaa=%d",aaa);

        fp=fopen("binary_file_1.dat","rb+");
        if(aaa>0)
        {
            p.aa++;
        }
        else
        {
            p.aa=0;
            p.aa++;
        }

        fseek(fp,ftell(fp)-sizeof(p),0);
        //fseek(fp,0,SEEK_END);
        fwrite(&p,sizeof(p),1,fp);
        fclose(fp);
        getch();

        fp=fopen("binary_file_1.dat","ab+");
        fread(&p,sizeof(p),1,fp);
        printf("aaa=%d\tp.aa=%d\n\n",aaa,p.aa);
        fclose(fp);

    return 0;
}

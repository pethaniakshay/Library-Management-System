#include<stdio.h>
#include<conio.h>
struct a
{
    char ap[50];
}pa;

void main()
{
    FILE *fp;

    fp=fopen("note.txt","rb");

    fread(&pa,sizeof(pa),1,fp);
    printf("%s",pa.ap);
    fclose(fp);
    //puts(pa.ap);
}

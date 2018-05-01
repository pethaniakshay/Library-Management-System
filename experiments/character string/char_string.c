#include"variables.h"
struct a
{
    char *ap;
}pa;

void main()
{

    FILE *fp;
    fp=fopen("note.txt","ab+");
    //gets(pa.ap);
    scanf("%[^/]s",&pa.ap);

    fseek(fp,0,SEEK_END);
    fwrite(&pa,sizeof(pa),1,fp);
    fclose(fp);

}

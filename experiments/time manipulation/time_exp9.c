#include<stdio.h>
#include<time.h>
#include<conio.h>

int main()
{
    struct tm *t1;
    time_t curnt;
    char str[80],str2[80];
    FILE *ft;
    double d_time;
    struct aksh
    {
        int aa;
        struct tm *t3;
        time_t ap;
    };

    struct aksh pp;

    time(&pp.ap);
    pp.t3=localtime(&pp.ap);
    //strftime(str,80,"%x-%X",pp.t3);
    //printf("current time is: %s\n",str);
    ft=fopen("time.dat","ab+");
    time(&pp.ap);
    pp.t3=localtime(&pp.ap);
    fseek(ft,0,SEEK_END);
    fwrite(&pp,sizeof(pp),1,ft);
    fclose(ft);
    printf("wrinten successful\n\n");


    ft=fopen("time.dat","rb");
    fread(&pp,sizeof(pp),1,ft);
    pp.t3=localtime(&pp.ap);
    strftime(str,80,"%x-%X",pp.t3);
    printf("aa=%d\t-\t%s",pp.aa,str);
    fclose(ft);

    time(&curnt);
    t1=localtime(&curnt);
    strftime(str2,80,"%x\t%X",t1);
    printf("\n\ncurent time: %s",str2);

    d_time = difftime(curnt,pp.ap);
    printf("\n\ndifferance of time is= %f\n", d_time);

    getch();
    return 0;
}

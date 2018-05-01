//#include<stdio.h>
//#include<conio.h>
#include "variables.h"

int main()
{
    FILE *ft;
    int temp_id;
    int flag=0;
    char temp_pw[25];
    system("cls");

    draw_star_box(31,6,68,12);
    gotoxy(35,8);
    printf("Login_id: ");
    scanf("%d",&temp_id);

    gotoxy(35,10);
    printf("Password: ");
    fflush(stdin);
    get_password(temp_pw);

    flag=0;
    while(1)
    {
        system("cls");
        ft = fopen("student_record.dat","rb");
        while(fread(&studnt, sizeof(studnt),1,ft)==1)
        {
            if(strcmp(temp_pw,studnt.password)==0  && temp_id==studnt.id)
            {
                flag=1;
            }

        }
        fclose(ft);
        if(flag==0)
        {
            draw_star_box(24,6,75,14);

            gotoxy(27,8);
            printf("Password or Login_id did not match! ");
            printf("Enter Again");

            gotoxy(32,10);
            printf("Login_id: ");
            scanf("%d",&temp_id);

            gotoxy(32,12);
            printf("Password: ");
            fflush(stdin);
            get_password(temp_pw);
        }
        else if(flag==1)
        {
            system("cls");
            gotoxy(10,12);
            printf("Password and Id Match");
            s_login=temp_id;
            gotoxy(10,13);
            printf("Press any key...");
            getch();
            student_menu();

}

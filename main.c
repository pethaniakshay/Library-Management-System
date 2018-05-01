#include "variables.h"

void gotoxy(int x, int y)
{
    coord.X = x; coord.Y = y; // X and Y coordinates
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


void set_text_color(int color)
{
     WORD wcolor;
     //this handle to get the current background attribute
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;

     //csbi for the wAttributes word.
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
        //Mask out all but the background attribute, and add in the forgournd color
          wcolor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
          SetConsoleTextAttribute(hStdOut, wcolor);
     }
     return;
}


void draw_star_box(int x1, int y1, int x2, int y2)
{
    int i, j;
    gotoxy(x1,y1);
    printf("*");
    for(i = x1; i <= x2; i++)
    {
        gotoxy(i, y1);
        printf("*");
        i++;

    }

    gotoxy(x2,y1);
    printf(" *");

    for(i = y1; i < y2; i++)
    {
        gotoxy(x2, i+1);
        printf(" *");
    }

    gotoxy(x2, y2);
    printf("*");

    for(i = x2; i > x1; i--)
    {
        gotoxy(i,y2);
        printf(" *");
        i--;
    }
    gotoxy(x1,y2);
    printf("*");

    for(i = y2; i > y1+1; i--)
    {
        gotoxy(x1,i-1);
        printf("*");
    }
    gotoxy(x1,y2+1);
}


void drawrectangle(int x1, int y1, int x2, int y2)
{
    int i, j;
    gotoxy(x1,y1);
    printf("%c",201);
    for(i = x1; i < x2; i++)
    {
        gotoxy(i+1, y1);
        printf("%c",205);
    }

    gotoxy(x2,y1);
    printf("%c",187);

    for(i = y1; i < y2; i++)
    {
        gotoxy(x2, i+1);
        printf("%c",186);
    }

    gotoxy(x2, y2);
    printf("%c",188);

    for(i = x2; i > x1; i--)
    {
        gotoxy(i-1,y2);
        printf("%c",205);
    }
    gotoxy(x1,y2);
    printf("%c",200);

    for(i = y2; i > y1+1; i--)
    {
        gotoxy(x1,i-1);
        printf("%c",186);
    }
    gotoxy(x1,y2+1);
}


void welcome_screen()
{
    system("cls");
    SetConsoleTitle("Atmiya Library Management System");
    gotoxy(25,10);
    printf("Welcome To Atmiya Library Management System");
    getch();
}


void exit_screen()
{
    system("cls");
    gotoxy(25,8);
    printf("Thanks For Using Atmiya Libary Management System");
    gotoxy(37,10);
    printf("Have A Good Day!!!");
    getch();
    exit(1);
}


int main()
{
    welcome_screen();

    login_menu();
    //exit_screen();
    //getch();
    return 0;
}


void login_menu()
{

    char ch2;
    system("cls");

    login=fopen("librarian_account_detail.dat","rb");

    if(login==NULL)
    {
        gotoxy(25,10);
        printf("Database Do not exits. Be an adminstrator. Sign Up");
        getch();
        librarian_signup();
    }

    else
    {
        while(1)
        {
            system("cls");

            drawrectangle(31,5,57,9);

            gotoxy(33,6);
            printf("1. Sign in as Librarian");

            gotoxy(33,8);
            printf("2. Sign in as Student");

            drawrectangle(31,11,57,13);
            gotoxy(33,12);
            printf("Enter Choice: ");
            scanf("%c",&ch2);

            switch(ch2)
            {
                case '1':
                librarian_signin();
                break;

                case '2':
                student_signin();
                break;

                default :
                gotoxy(30,16);
                printf("Invalid Entry Please Try Again");
                getch();
                break;
            }
        }
    }
}


void get_password(char* pass)
{
    char temp_passP[25];
    int i=0;
    while(1)
    {
        temp_passP[i]=getch();

        if(temp_passP[i]==13)
        {
            break;
        }

        else if(temp_passP[i]==8)
        {
            if(i!=0)
            {
                printf("\b \b");
                i--;
            }

            else
            {
                printf("\a");
            }
        }

        else
        {
            printf("*");
            *(pass+i) = temp_passP[i];
            i++;
        }

        *(pass+i)='\0';
     }
}


void librarian_signup()
{
    char temp[25];
    login = fopen("librarian_account_detail.dat","wb");
    system("cls");


    draw_star_box(31,6,68,15);
    gotoxy(35,8);
    printf("Enter Login id: ");
    gets(lad.login_id);

    gotoxy(35,10);
    printf("Enter Password: ");

    get_password(lad.password);

    gotoxy(35,12);
    printf("Re Enter Password: ");

    get_password(temp);
    while(strcmp(lad.password,temp)!=0)
    {
        system("cls");
        draw_star_box(29,6,70,16);
        gotoxy(32,8);
        printf("Password did not matched! Enter again");


        gotoxy(34,10);
        printf("Enter Login id: ");
        gets(lad.login_id);


        gotoxy(34,12);
        printf("Enter Password: ");

        get_password(lad.password);

        gotoxy(34,14);
        printf("Re Enter Password: ");
        get_password(temp);
    }

    fwrite(&lad,sizeof(lad),1,login);
    fclose(login);

    librarian_menu();

}


void librarian_signin()
{
    system("cls");
    char temp_id[25];
    char temp_pw[25];
    login = fopen("librarian_account_detail.dat","rb");

    draw_star_box(31,6,68,12);
    gotoxy(35,8);
    printf("Login_id: ");
    fflush(stdin);
    gets(temp_id);

    gotoxy(35,10);
    printf("Password: ");
    fflush(stdin);
    get_password(temp_pw);
    puts(temp_pw);

    while(fread(&lad, sizeof(lad),1,login)==1)
    {
        while(strcmp(temp_pw,lad.password)!=0  || strcmp(temp_id,lad.login_id)!=0)
        {
            system("cls");
            draw_star_box(24,6,75,14);
            gotoxy(27,8);
            printf("Password or Login_id did not match! ");
            printf("Enter Again");

            gotoxy(32,10);
            printf("Login_id: ");
            fflush(stdin);
            gets(temp_id);

            gotoxy(32,12);
            printf("Password: ");
            fflush(stdin);
            get_password(temp_pw);


        }
        system("cls");
        gotoxy(10,12);
        printf("Password and Id Match");
        break;
    }
    fclose(login);

    gotoxy(10,13);
    printf("Press any key...");
    getch();

    librarian_menu();
}


void student_signin()
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

    }

}


void librarian_menu()
{
    char ch;

    while(1)
    {
        system("cls");

        drawrectangle(32,3,65,5);
        gotoxy(41,4);
        printf("Librarian Menu");

        drawrectangle(32,7,65,17);
        gotoxy(37,9);
        printf("1. Manage books record");

        gotoxy(37,11);
        printf("2. Manage student record");

        gotoxy(37,13);
        printf("3. Manage books transactions");

        gotoxy(37,15);
        printf("4. Clear database");

        gotoxy(36,19);
        printf("A. Main menu");

        gotoxy(51,19);
        printf("Z. Exit");

        gotoxy(36,21);
        printf("Enter Your Choice: ");
        fflush(stdin);
        scanf("%c",&ch);
        //ch=getchar();

        switch(ch)
        {
            case '1':
                manage_book_record();
                break;

            case '2':
                manage_student_record();
                break;

            case '3':
                manage_books_transaction();
                break;

            case '4':
                delete_database();
                break;

            case 'a':
                delete_database();
                getch();
                break;

            case 'z':
                exit_screen();
                break;

            case 'A':
                delete_database();
                getch();
                break;

            case 'Z':
                exit_screen();
                break;

            default:
                gotoxy(32,23);
                set_text_color(12);
                printf("Invalid Entry Please Try Again !!");
                set_text_color(7);
                getch();
                break;
        }
    }

}


void manage_book_record()
{
    char ch;

    while(1)
    {

        system("cls");

        drawrectangle(32,3,65,5);
        gotoxy(37,4);
        printf("Book Record Management");

        drawrectangle(32,7,65,17);
        gotoxy(37,9);
        printf("1. Create Book Record");

        gotoxy(37,11);
        printf("2. Delete Book Record");

        gotoxy(37,13);
        printf("3. Modify book record");

        gotoxy(37,15);
        printf("4. View book record");

        gotoxy(36,19);
        printf("A. Main menu");

        gotoxy(51,19);
        printf("Z. Exit");

        gotoxy(36,21);
        printf("Enter Choice: ");

        fflush(stdin);
        ch=getchar();

        switch(ch)
        {
            case '1':
                add_book_record();
                getch();
                break;

            case '2':
                delete_book_record();
                getch();
                break;

            case '3':
                modify_book_record();
                getch();
                break;

            case '4':
                view_book_record();
                getch();
                break;

            case 'a':
                librarian_menu();
                break;

            case 'z':
                exit_screen();
                break;

            case 'A':
                librarian_menu();
                break;

            case 'Z':
                exit_screen();
                break;

            default :
                gotoxy(32,23);
                set_text_color(12);
                printf("Invalid Entry Please Try Again !!");
                set_text_color(7);
                getch();
                break;
        }
    }
}


void add_book_record()
{
    int ch,counter;
    char chs;
    FILE *ft;
    system("cls");

    while(1)
    {
        l1:
        ft = fopen("book_record.dat","ab+");
        ch=select_stream();
        switch(ch)
        {

            case 1:
                fflush(stdin);
                book.stream="cs";
                add_book_data();
                book.id=(ch*100000)+(book.qty*100)+book_counter(ch);
                break;

            case 2:
                book.stream="ee";
                add_book_data();
                book.id=(ch*100000)+(book.qty*100)+book_counter(ch);
                break;

            case 3:
                book.stream="ec";
                add_book_data();
                book.id=(ch*100000)+(book.qty*100)+book_counter(ch);
                break;

            case 4:
                book.stream="civil";
                add_book_data();
                book.id=(ch*100000)+(book.qty*100)+book_counter(ch);
                break;

            case 5:
                book.stream="mech";
                add_book_data();
                book.id=(ch*100000)+(book.qty*100)+book_counter(ch);
                break;

            case 6:
                book.stream="ic";
                add_book_data();
                book.id=(ch*100000)+(book.qty*100)+book_counter(ch);
                break;

            case 7:
                book.stream="maths";
                add_book_data();
                book.id=(ch*100000)+(book.qty*100)+book_counter(ch);
                break;

            case 8:
                book.stream="ic";
                add_book_data();
                book.id=(ch*100000)+(book.qty*100)+book_counter(ch);
                break;

            default:
                printf("Invalid Entry please try again!");
                getch();
                goto l1;
                break;
        }

        fseek(ft,0,SEEK_END);
        fwrite(&book,sizeof(book),1,ft);
        fclose(ft);
        printf("Record saved successfully\n\n");

        printf("want to add more record (y/n)?: ");
        chs=getch();
        fflush(stdin);
        if(chs=='n')
            break;
    }
}


int select_stream()
{
        int ch;
        system("cls");
        gotoxy(28,4);
        printf("* * * * * * select book stream * * * * * *");
        gotoxy(28,6);
        printf("1. Computer science engineering");
        gotoxy(28,7);
        printf("2. Electrical Engineering");
        gotoxy(28,8);
        printf("3. Electronic & communication engineering");
        gotoxy(28,9);
        printf("4. civil engineering");
        gotoxy(28,10);
        printf("5. Mechanical engineering");
        gotoxy(28,11);
        printf("6. Instrumental & control engineering");
        gotoxy(28,12);
        printf("7. Mathematics");
        gotoxy(28,13);
        printf("8. Other Non Academic book");
        gotoxy(30,15);
        printf("Enter Choice: ");
        scanf("%d",&ch);
        return ch;
}


void add_book_data()
{
    system("cls");
    fflush(stdin);

    printf("\nBook Name: ");
    fflush(stdin);
    gets(book.name);

    printf("\nAutor: ");
    gets(book.author);

    printf("\nPublication: ");
    fflush(stdin);
    gets(book.publicaton);

    printf("\nPrice: ");
    scanf("%f",&book.price);

    printf("\nQuantity:");
    scanf("%d",&book.qty);
    book.avlbl_qty=book.qty;
}


int book_counter(int ch)
{
    FILE *fp;
    int temp;

    bc.civil=0;
    bc.cs=0;
    bc.ec=0;
    bc.ee=0;
    bc.ic=0;
    bc.mech=0;
    bc.maths=0;
    bc.others=0;

    switch(ch)
    {
    case 1:
        fp=fopen("book_counter.dat","ab+");
        fread(&bc,sizeof(bc),1,fp);
        temp=bc.cs;
        fclose(fp);

        fp=fopen("book_counter.dat","rb+");
        if(temp>100)
        {
            bc.cs++;
        }
        else
        {
            bc.cs=100;
            bc.cs++;
        }

        fseek(fp,ftell(fp)-sizeof(bc),0);
        fwrite(&bc,sizeof(bc),1,fp);
        fclose(fp);

        return bc.cs;
        break;

    case 2:
        fp=fopen("book_counter.dat","ab+");
        fread(&bc,sizeof(bc),1,fp);
        temp=bc.ee;
        fclose(fp);

        fp=fopen("book_counter.dat","rb+");
        if(temp>100)
        {
            bc.ee++;
        }
        else
        {
            bc.ee=100;
            bc.ee++;
        }

        fseek(fp,ftell(fp)-sizeof(bc),0);
        fwrite(&bc,sizeof(bc),1,fp);
        fclose(fp);

        return sc.ee;
        break;

    case 3:
        fp=fopen("book_counter.dat","ab+");
        fread(&bc,sizeof(bc),1,fp);
        temp=bc.ec;
        fclose(fp);

        fp=fopen("student_counter.dat","rb+");
        if(temp>100)
        {
            bc.ec++;
        }
        else
        {
            bc.ec=100;
            bc.ec++;
        }

        fseek(fp,ftell(fp)-sizeof(bc),0);
        fwrite(&bc,sizeof(bc),1,fp);
        fclose(fp);
        return bc.ec;
        break;

        case 4:
        fp=fopen("book_counter.dat","ab+");
        fread(&bc,sizeof(bc),1,fp);
        temp=bc.civil;
        fclose(fp);

        fp=fopen("book_counter.dat","rb+");
        if(temp>100)
        {
            bc.civil++;
        }
        else
        {
            bc.civil=100;
            bc.civil++;
        }

        fseek(fp,ftell(fp)-sizeof(bc),0);
        fwrite(&bc,sizeof(bc),1,fp);
        fclose(fp);
        return bc.civil;
        break;

        case 5:
        fp=fopen("book_counter.dat","ab+");
        fread(&bc,sizeof(bc),1,fp);
        temp=bc.mech;
        fclose(fp);

        fp=fopen("book_counter.dat","rb+");
        if(temp>100)
        {
            bc.mech++;
        }
        else
        {
            bc.mech=100;
            bc.mech++;
        }

        fseek(fp,ftell(fp)-sizeof(bc),0);
        fwrite(&bc,sizeof(bc),1,fp);
        fclose(fp);
        return bc.mech;
        break;

        case 6:
        fp=fopen("book_counter.dat","ab+");
        fread(&bc,sizeof(bc),1,fp);
        temp=bc.ic;
        fclose(fp);

        fp=fopen("book_counter.dat","rb+");
        if(temp>100)
        {
            bc.ic++;
        }
        else
        {
            bc.ic=100;
            bc.ic++;
        }

        fseek(fp,ftell(fp)-sizeof(bc),0);
        fwrite(&bc,sizeof(bc),1,fp);
        fclose(fp);
        return bc.ic;
        break;

        case 7:
        fp=fopen("book_counter.dat","ab+");
        fread(&bc,sizeof(bc),1,fp);
        temp=bc.maths;
        fclose(fp);

        fp=fopen("book_counter.dat","rb+");
        if(temp>100)
        {
            bc.maths++;
        }
        else
        {
            bc.maths=100;
            bc.maths++;
        }

        fseek(fp,ftell(fp)-sizeof(bc),0);
        fwrite(&bc,sizeof(bc),1,fp);
        fclose(fp);
        return bc.maths;
        break;

        case 8:
        fp=fopen("book_counter.dat","ab+");
        fread(&bc,sizeof(bc),1,fp);
        temp=bc.others;
        fclose(fp);

        fp=fopen("book_counter.dat","rb+");
        if(temp>100)
        {
            bc.others++;
        }
        else
        {
            bc.others=100;
            bc.others++;
        }

        fseek(fp,ftell(fp)-sizeof(bc),0);
        fwrite(&bc,sizeof(bc),1,fp);
        fclose(fp);
        return bc.others;
        break;

        default:
            printf("invalid entery");
            return 0;
    }
}


void delete_book_record()
{
    FILE *ft,*fp;
    int d,findBook = 0;
    char another='y';

	system("cls");

    while(another=='y')
	{
        system("cls");

        printf("Enter the Book ID to  delete:");
        scanf("%d",&d);

        fp = fopen("book_record.dat","rb+");

		while(fread(&book,sizeof(book),1,fp)==1)
		{
            if(book.id==d)
			{
                printf("The book record is available");
                printf("Book name is %s",book.name);
                findBook = 1;
                printf("Do you want to delete it?(Y/N):");

                if(getch()=='y')
				{
                    ft=fopen("temp.dat","wb");  //temporary file for delete
                    rewind(fp);

                    while(fread(&book,sizeof(book),1,fp)==1)
					{
                        if(book.id!=d)
						{
                            fwrite(&book,sizeof(book),1,ft);//write all in tempory file except that
                        }                              //we want to delete
                    }

                    fclose(fp);
                    fclose(ft);

                    remove("book_record.dat");
                    rename("temp.dat","book_record.dat"); //copy all item from temporary file to fp except that
                                        //we want to delete
                    printf("The record is sucessfully deleted");
                }
            }
        }

		if(findBook == 0)
		{
            printf("No record is found");
            getch();
        }
        printf("Delete another record?(Y/N)");
        fflush(stdin);
        another=getch();
    }

}


void modify_book_record()
{
    FILE *fp;
	int c=0,d;
	char another='y',ch;
	system("cls");
	printf("****Edit Books Section****\n");

    while(another=='y')
	{
		system("cls");
		printf("Enter Book Id to be edited: ");
		scanf("%d",&d);
		printf("\n");

		fp=fopen("book_record.dat","rb+");

        while(fread(&book,sizeof(book),1,fp)==1)
		{
			if(book.id==d)
			{

				printf("The book is availble\n");
				printf("The Book ID:%d\n",book.id);
				printf("The Current data is:\n");

				printf("Id: %d\n Name: %s\n Author: %s\n",book.id,book.name,book.author);
				printf("Publication: %s\n Price: %5.0f\n qty: %d\n",book.publicaton,book.price,book.qty);

                printf("want to modify Name (y/n)?");
                if(ch=getch()=='y')
                {
                    printf("\nEnter new name:");
                    fflush(stdin);
                    gets(book.name);
                }

                printf("\nWant to modify Author (y/n)?");
				if(ch=getch()=='y')
                {
                    printf("\nEnter new Author:");
                    gets(book.author);
                }

                printf("\nWant to modify publication (y/n)?");
				if(ch=getch()=='y')
                {
                    printf("\nEnter new publication:");
                    gets(book.publicaton);
                }

                printf("\nWant to modify price (y/n)?");
				if(ch=getch()=='y')
                {
                    printf("\nEnter new price: ");
                    scanf("%f",&book.price);
                }

                printf("\nWant to modify quantity (y/n)?: ");
				if(ch=getch()=='y')
                {
                    printf("\nEnter new quantity:");
                    scanf("%d",&book.qty);
                    book.avlbl_qty=book.qty;
                }

                printf("\nThe record is modified");

				fseek(fp,ftell(fp)-sizeof(book),0);
				fwrite(&book,sizeof(book),1,fp);
				fclose(fp);
				c=1;
			}
			if(c==0)
			{
				printf("\nNo record found");
			}
		}
		printf("\nModify another Record?(Y/N)?: ");
		fflush(stdin);
		another=getch() ;
	}
}


void view_book_record()
{
    int i=0,j;
    FILE *fp;

    system("cls");

    gotoxy(1,1);
    printf("* * * * * * * * * * * * * * * * * * * * Book List * * * * * * * * * * * * * * * * * * * * * * * *");

    gotoxy(2,3);
    printf("ID                NAME             Author      Publication      Price     qty   Available_Qty");
    j=5;
    fp=fopen("book_record.dat","rb");

    while(fread(&book,sizeof(book),1,fp)==1)
    {
        gotoxy(2,j);
        printf("%d",book.id);

        gotoxy(8,j);
        printf("%s",book.name);

        gotoxy(37,j);
        printf("%s",book.author);

        gotoxy(52,j);
        printf("%s",book.publicaton);

        gotoxy(66,j);
        printf("%6.2f",book.price);

        gotoxy(77,j);
        printf("%d",book.qty);

        gotoxy(85,j);
        printf("%d",book.avlbl_qty);

        printf("\n\n");
        j++;
        i=i+book.qty;
    }
        gotoxy(3,j+2);
        printf("Total boooks: %d",i);
        fclose(fp);
        gotoxy(90,25);

}


void manage_student_record()
{
    char ch;

    while(1)
    {
        system("cls");

        drawrectangle(32,3,65,5);
        gotoxy(36,4);
        printf("Student Record Management");

        drawrectangle(32,7,65,17);
        gotoxy(37,9);
        printf("1. Add Student Record");

        gotoxy(37,11);
        printf("2. Delete student record");

        gotoxy(37,13);
        printf("3. Modify student record");

        gotoxy(37,15);
        printf("4. View student record");

        gotoxy(36,19);
        printf("A. Main menu");

        gotoxy(51,19);
        printf("Z. Exit");

        gotoxy(36,21);
        printf("Enter your choice: ");
        fflush(stdin);
        scanf("%c",&ch);

        switch(ch)
        {
            case '1':
                add_student_record();
                getch();
                break;

            case '2':
                delete_student_record();
                getch();
                break;

            case '3':
                modify_student_record();
                getch();
                break;

            case '4':
                view_student_record();
                getch();
                break;

            case 'a':
                librarian_menu();
                break;

            case 'z':
                exit_screen();
                break;

            case 'A':
                librarian_menu();
                break;

            case 'Z':
                exit_screen();
                break;

            default :
                gotoxy(32,23);
                set_text_color(12);
                printf("Invalid Entry Please Try Again !!");
                set_text_color(7);
                getch();
                break;
        }
    }
}


void add_student_record()
{
    int ch,counter;
    char chs;
    FILE *ft;
    system("cls");

    while(1)
    {
        l1:
        ft = fopen("student_record.dat","ab+");
        ch=select_branch();
        switch(ch)
        {

            case 1:
                fflush(stdin);
                studnt.branch="cs";
                add_studnt_data();
                studnt.id=(ch*1000)+studnt_counter(ch);;
                break;

            case 2:
                studnt.branch="ee";
                add_studnt_data();
                studnt.id=(ch*1000)+studnt_counter(ch);
                break;

            case 3:
                studnt.branch="ec";
                add_studnt_data();
                studnt.id=(ch*1000)+studnt_counter(ch);
                break;

            case 4:
                studnt.branch="civil";
                add_studnt_data();
                studnt.id=(ch*1000)+studnt_counter(ch);
                break;

            case 5:
                studnt.branch="mech";
                add_studnt_data();
                studnt.id=(ch*1000)+studnt_counter(ch);
                break;

            case 6:
                studnt.branch="ic";
                add_studnt_data();
                studnt.id=(ch*1000)+studnt_counter(ch);
                break;

            default :
                printf("Invalid Entry please try again!");
                getch();
                goto l1;
                break;
        }

        fseek(ft,0,SEEK_END);
        fwrite(&studnt,sizeof(studnt),1,ft);
        fclose(ft);
        printf("Record saved successfully\n\n");

        printf("want to add more record (y/n)?: ");
        chs=getch();
        fflush(stdin);
        if(chs=='n')
            break;
    }
}


int select_branch()
{
        int ch;
        system("cls");
        printf("\t*******select your branch*******\n");
        printf("1. Computer science engineering\n");
        printf("2. Electrical Engineering\n");
        printf("3. Electronic & communication engineering\n");
        printf("4. civil engineering\n");
        printf("5. Mechanical engineering\n");
        printf("6. Instrumental & control engineering\n");
        printf("\n\nEnter Choice: ");
        scanf("%d",&ch);
        return ch;
}


void add_studnt_data()
{
    char temp[25];
    printf("\nFname: ");
    fflush(stdin);
    gets(studnt.fname);

    printf("\nMname: ");
    fflush(stdin);
    gets(studnt.mname);

    printf("\nLname: ");
    fflush(stdin);
    gets(studnt.lname);

    studnt.issued_books=0;


    printf("\nPassword: ");
    get_password(studnt.password);

    printf("\nRe Enter Password: ");
    get_password(temp);

    while(strcmp(studnt.password,temp)!=0)
    {
        printf("\nPassword did not matched! Enter again");

        printf("Enter password: ");

        get_password(studnt.password);

        printf("Re Enter Password: ");

        get_password(temp);
        system("cls");
    }
}


int studnt_counter(int ch)
{
    FILE *fp;
    int temp;

    sc.civil=0;
    sc.cs=0;
    sc.ec=0;
    sc.ee=0;
    sc.ic=0;
    sc.mech=0;
    switch(ch)
    {
    case 1:
        fp=fopen("student_counter.dat","ab+");
        fread(&sc,sizeof(sc),1,fp);
        temp=sc.cs;
        fclose(fp);

        fp=fopen("student_counter.dat","rb+");
        if(temp>100)
        {
            sc.cs++;
        }
        else
        {
            sc.cs=100;
            sc.cs++;
        }

        fseek(fp,ftell(fp)-sizeof(sc),0);
        fwrite(&sc,sizeof(sc),1,fp);
        fclose(fp);

        return sc.cs;
        break;

    case 2:
        fp=fopen("student_counter.dat","ab+");
        fread(&sc,sizeof(sc),1,fp);
        temp=sc.ee;
        fclose(fp);

        fp=fopen("student_counter.dat","rb+");
        if(temp>100)
        {
            sc.ee++;
        }
        else
        {
            sc.ee=100;
            sc.ee++;
        }

        fseek(fp,ftell(fp)-sizeof(sc),0);
        fwrite(&sc,sizeof(sc),1,fp);
        fclose(fp);

        return sc.ee;
        break;

    case 3:
        fp=fopen("student_counter.dat","ab+");
        fread(&sc,sizeof(sc),1,fp);
        temp=sc.ec;
        fclose(fp);

        fp=fopen("student_counter.dat","rb+");
        if(temp>100)
        {
            sc.ec++;
        }
        else
        {
            sc.ec=100;
            sc.ec++;
        }

        fseek(fp,ftell(fp)-sizeof(sc),0);
        fwrite(&sc,sizeof(sc),1,fp);
        fclose(fp);
        return sc.ec;
        break;

        case 4:
        fp=fopen("student_counter.dat","ab+");
        fread(&sc,sizeof(sc),1,fp);
        temp=sc.civil;
        fclose(fp);

        fp=fopen("student_counter.dat","rb+");
        if(temp>100)
        {
            sc.civil++;
        }
        else
        {
            sc.civil=100;
            sc.civil++;
        }

        fseek(fp,ftell(fp)-sizeof(sc),0);
        fwrite(&sc,sizeof(sc),1,fp);
        fclose(fp);
        return sc.civil;
        break;

        case 5:
        fp=fopen("student_counter.dat","ab+");
        fread(&sc,sizeof(sc),1,fp);
        temp=sc.mech;
        fclose(fp);

        fp=fopen("student_counter.dat","rb+");
        if(temp>100)
        {
            sc.mech++;
        }
        else
        {
            sc.mech=100;
            sc.mech++;
        }

        fseek(fp,ftell(fp)-sizeof(sc),0);
        fwrite(&sc,sizeof(sc),1,fp);
        fclose(fp);
        return sc.mech;
        break;

        case 6:
        fp=fopen("student_counter.dat","ab+");
        fread(&sc,sizeof(sc),1,fp);
        temp=sc.ic;
        fclose(fp);

        fp=fopen("student_counter.dat","rb+");
        if(temp>100)
        {
            sc.ic++;
        }
        else
        {
            sc.ic=100;
            sc.ic++;
        }

        fseek(fp,ftell(fp)-sizeof(sc),0);
        fwrite(&sc,sizeof(sc),1,fp);
        fclose(fp);
        return sc.ic;
        break;

        default:
            printf("invalid entery");
            return 0;
    }
}



void delete_student_record()
{
    FILE *ft,*fp;
    int d,found = 0;
    char another='y';

	system("cls");

    while(another=='y')
	{
        system("cls");

        printf("Enter the Student ID to  delete:");
        scanf("%d",&d);

        fp = fopen("student_record.dat","rb+");

		while(fread(&studnt,sizeof(studnt),1,fp)==1)
		{
            if(studnt.id==d)
			{
                printf("The Student record is available");
                printf("studnet name is %s %s",studnt.fname,studnt.lname);
                found = 1;
                printf("Do you want to delete it?(Y/N):");

                if(getch()=='y')
				{
                    ft=fopen("test.dat","wb");  //temporary file for delete
                    rewind(fp);

                    while(fread(&studnt,sizeof(studnt),1,fp)==1)
					{
                        if(studnt.id!=d)
						{
                            fwrite(&studnt,sizeof(studnt),1,ft);//write all in tempory file except that
                        }                              //we want to delete
                    }

                    fclose(fp);
                    fclose(ft);

                    remove("student_record.dat");
                    getch();
                    rename("test.dat","student_record.dat"); //copy all item from temporary file to fp except that
                                        //we want to delete
                    printf("The record is sucessfully deleted");
                }
            }
        }

		if(found== 0)
		{
            printf("No record is found");
            getch();
        }
        printf("Delete another record?(Y/N)");
        fflush(stdin);
        another=getch();
    }

}


void modify_student_record()
{
    FILE *fp;
	int c=0,d,flag=0;
	char another='y',ch;
	char temp_pw[25],*fname,*lname,*mname;
	system("cls");
	printf("****Edit Students Section****\n");

    while(another=='y')
	{
		system("cls");
		printf("Enter student Id to be edited: ");
		scanf("%d",&d);
		printf("\n");

		fp=fopen("student_record.dat","rb+");

        while(fread(&studnt,sizeof(studnt),1,fp)==1)
		{
			if(studnt.id==d)
			{

				printf("The Student record is availble\n");
				printf("The Student ID:%d\n",studnt.id);
				printf("The Current data is:\n");

				printf("Id: %d\n Name: %s %s %s\n Password: %s\n",studnt.id,studnt.fname,studnt.mname,studnt.lname,studnt.password);

                printf("want to modify Name (y/n)?");
                if(ch=getch()=='y')
                {
                    printf("\nEnter new name");
                    fflush(stdin);
                    printf("\nFname: ");
                    gets(studnt.fname);
                    printf("\nMname: ");
                    gets(studnt.mname);
                    printf("\nLname: ");
                    gets(studnt.lname);
                    flag=1;
                }

                printf("\nWant to modify Password (y/n)?: ");
				if(ch=getch()=='y')
                {
                    printf("\nEnter new Password :");
                    get_password(studnt.password);

                    printf("\nRenter Password: ");
                    get_password(temp_pw);
                }

                printf("\nThe record is modified: ");

				fseek(fp,ftell(fp)-sizeof(studnt),0);
				fwrite(&studnt,sizeof(studnt),1,fp);
				fclose(fp);
				c=1;
			}
			if(c==0)
			{
				printf("\nNo record found");
			}
		}
		printf("\nModify another Record?(Y/N)?: ");
		fflush(stdin);
		another=getch() ;
	}
}


void view_student_record()
{
    int i=0,j;
    FILE *fp;

    system("cls");

    gotoxy(1,1);
    printf("*********************************Student List*****************************");

    gotoxy(2,2);
    printf("ID       NAME             Branch               Password");
    j=4;
    fp=fopen("student_record.dat","rb");

    while(fread(&studnt,sizeof(studnt),1,fp)==1)
    {
        gotoxy(3,j);
        printf("%d",studnt.id);

        gotoxy(15,j);
        printf("%s %s %s",studnt.fname,studnt.mname,studnt.lname);

        gotoxy(60,j);
        printf("%s",studnt.branch);

        gotoxy(70,j);
        printf("%s",studnt.password);

        printf("\n\n");
        j++;
        i++;
    }
        gotoxy(3,25);
        printf("Total Students: %d",i);
        fclose(fp);
        gotoxy(85,25);
}


void manage_books_transaction()
{
    char ch;

    while(1)
    {
        system("cls");

        system("cls");

        drawrectangle(28,3,70,5);
        gotoxy(36,4);
        printf("Book Transaction Management");

        drawrectangle(28,7,70,17);
        gotoxy(33,9);
        printf("1. Issue Books");

        gotoxy(33,11);
        printf("2. Return Books");

        gotoxy(33,13);
        printf("3. View Issued Books");

        gotoxy(33,15);
        printf("4. View Who not returned in time");

        gotoxy(36,19);
        printf("A. Main menu");

        gotoxy(51,19);
        printf("Z. Exit");

        gotoxy(36,21);
        printf("Enter your choice: ");
        fflush(stdin);
        scanf("%c",&ch);

        switch(ch)
        {
            case '1':
                issue_book();
                getch();
                break;

            case '2':
                return_book();
                getch();
                break;

            case '3':
                view_issued_book();
                getch();
                break;

            case '4':
                view_not_retunt_in_time();
                getch();
                break;

            case '5':
                view_avlbl_book();
                getch();
                break;

            case 'a':
                librarian_menu();
                break;

            case 'z':
                exit_screen();
                break;

            case 'A':
                librarian_menu();
                break;

            case 'Z':
                exit_screen();
                break;

            default :
                gotoxy(32,23);
                set_text_color(12);
                printf("Invalid Entry Please Try Again !!");
                set_text_color(7);
                getch();
                break;
        }
    }
}


void issue_book()
{
    FILE *fp,*ft;
    int temp1,temp2;
    char ch1,ch2;
    int find1,find2;

    while(1)
    {
            system("cls");

            printf("Enter book id: ");
            scanf("%d",&ibrf.b_id);

            ft=fopen("book_record.dat","rb");
            find1=0;
            while(fread(&book,sizeof(book),1,ft)==1)
            {   //printf("\nibrf.b_id: %d",ibrf.b_id);
                //printf("\nblist.id: %d",blist.id);
                if(ibrf.b_id==book.id)
                {
                    printf("\nBook Name: %s",book.name);
                    printf("\n\nAuthor: %s",book.author);
                    printf("\n\nPublicaation: %s",book.publicaton);
                    temp1=book.avlbl_qty;
                    find1=1;
                    if(book.avlbl_qty<2)
                    {
                        printf("\n\nThis book will not be issued because of only 1 copy remaining");
                        goto l2;
                    }
                }

            }
            if(find1==0)
                {
                    printf("\n\nno record found for this id number\n");
                    goto l2;
                }
            fclose(ft);


            printf("\n\nEnter student id: ");
            scanf("%d",&ibrf.s_id);
            fp=fopen("student_record.dat","rb");
            find2=0;
            while(fread(&studnt,sizeof(studnt),1,fp)==1)
            {
                if(ibrf.s_id==studnt.id)
                {
                    printf("\nName: %s %s %s",studnt.fname,studnt.mname,studnt.lname);
                    printf("\nBranch: %s",studnt.branch);
                    temp2=studnt.issued_books;

                    find2=1;

                    if(2-studnt.issued_books==0)
                    {
                        printf("%s cannot issue this book");
                        goto l2;
                    }
                    else if(studnt.issued_books>3)
                    {
                        printf("%s cannot issue this book");
                        goto l2;
                    }

                }

            }
            if(find2==0)
                {
                    printf("no redord found for this student id");
                    goto l2;
                }
            fclose(fp);

            printf("\n\nDo want to issue this book(y/n)?: ");
            fflush(stdin);
            scanf("%c",&ch1);

            if(ch1=='y')
            {
                fp=fopen("student_record.dat","rb+");
                while(fread(&studnt,sizeof(studnt),1,fp)==1)
                {
                    if(ibrf.s_id==studnt.id)
                    {
                        temp2++;
                        studnt.issued_books=temp2;
                        fseek(fp,ftell(fp)-sizeof(studnt),0);
                        fwrite(&studnt,sizeof(studnt),1,fp);
                        fclose(fp);
                    }
                }

                ft=fopen("book_record.dat","rb+");
                while(fread(&book,sizeof(book),1,ft)==1)
                {
                    if(ibrf.b_id==book.id)
                    {
                        temp1--;
                        book.avlbl_qty=temp1;

                        fseek(ft,ftell(ft)-sizeof(book),0);
                        fwrite(&book,sizeof(book),1,ft);
                        fclose(ft);

                    }
                }


                fp=fopen("issued_record.dat","ab+");
                //ft=fopen("issued_record_2.dat","ab+");
                fseek(fp,0,SEEK_END);
                //current time
                time(&ibrf.stm);
                ibrf.t1=localtime(&ibrf.stm);
                ibrf.t2=NULL;
                ibrf.if_return='n';
                fwrite(&ibrf,sizeof(ibrf),1,fp);
                //fwrite(&ibrf,sizeof(ibrf),1,ft);
                fclose(fp);
                //fclose(ft);

        }
l2:
            printf("\nWant to issue more books(y/n)? :" );
            fflush(stdin);
            scanf("%c",&ch2);
            if(ch2=='n')
                break;
    }

}


void return_book()
{
        FILE *fp,*ft;
        int bk_id;
        int stdnt_id;
        int find1=0;
        char ch2;
        struct tm *t3;
        time_t curnt;
        double d_time;
        int late,fine;

        while(1)
        {
            system("cls");
            printf("\nBook id: ");
            scanf("%d",&bk_id);
            printf("\nStudent id: ");
            scanf("%d",&stdnt_id);

            fp=fopen("issued_record.dat","rb+");
            //ft=fopen("issued_record.dat","rb+");
            while(fread(&ibrf,sizeof(ibrf),1,fp)==1)
            {
                piyu:
                if(ibrf.b_id==bk_id && ibrf.s_id==stdnt_id)
                {
                    if(ibrf.if_return=='y')
                    {
                        //continue;
                        goto piyu;

                    }
                    ibrf.if_return='y';
                    //current time
                    time(&ibrf.stm2);
                    ibrf.t2=localtime(&ibrf.stm);
                    fseek(fp,ftell(fp)-sizeof(ibrf),0);
                    fwrite(&ibrf,sizeof(ibrf),1,fp);
                    fclose(fp);

                    fp=fopen("book_record.dat","rb+");
                    while(fread(&book,sizeof(book),1,fp)==1)
                    {
                        if(bk_id==book.id)
                        {
                            book.avlbl_qty++;
                            fseek(fp,ftell(fp)-sizeof(book),0);
                            fwrite(&book,sizeof(book),1,fp);
                            fclose(fp);
                        }
                    }

                    fp=fopen("student_record.dat","rb+");
                    while(fread(&studnt,sizeof(studnt),1,fp)==1)
                    {
                        if(stdnt_id==studnt.id)
                        {
                            studnt.issued_books--;
                            fseek(fp,ftell(fp)-sizeof(studnt),0);
                            fwrite(&studnt,sizeof(studnt),1,fp);
                            fclose(fp);
                        }
                    }

                    time(&curnt);
                    t3=localtime(&curnt);

                    d_time = difftime(curnt,ibrf.stm);

                    if(d_time>=1296000)
                    {
                        late=d_time/86400;
                        printf("\n\nYou Returned this Book %d days late So",late+1);
                        fine=(late+1)*2;
                        printf("you have to pay Rs. %d\n\n",fine);
                    }

                    find1=1;
                }

            }
            if(find1==0)
            {
                    printf("Book Id or Student Id may be Wrong or No such book issued");
                    goto l3;
            }

l3:
        printf("\n\nWant to Return more books(y/n)? :" );
        fflush(stdin);
        scanf("%c",&ch2);
        if(ch2=='n')
            break;

        }
}


void view_issued_book()
{
    FILE *fp;
    system("cls");
    char str[25],str2[25];

    printf("*********************************Issued Book List*****************************\n\n");
    printf("S_id     B_id             Issue date    Return date\n\n");

    fp=fopen("issued_record.dat","rb");
    while(fread(&ibrf,sizeof(ibrf),1,fp)==1)
	{

        printf("%d\t",ibrf.s_id);
        printf("%d\t",ibrf.b_id);

        ibrf.t1=localtime(&ibrf.stm);
        strftime(str,25,"%x",ibrf.t1);
        printf("\t%s",str);

        if(ibrf.if_return=='y')
        {
        ibrf.t2=localtime(&ibrf.stm2);
        strftime(str2,25,"%x",ibrf.t2);
        printf("\t%s",str2);
        //printf("\t%c",ibrf.if_return);

        }
        printf("\n");
    }
    fclose(fp);
}


void view_not_retunt_in_time()
{
    FILE *fp;
    system("cls");
    char str[25],str2[25];
    struct tm *t3;
    time_t curnt;
    double d_time;
    int late,fine;

    printf("*********************************not return i time*****************************\n\n");
    printf("S_id     B_id             Issue date        late_day     fine \n\n");

    fp=fopen("issued_record.dat","rb");
    while(fread(&ibrf,sizeof(ibrf),1,fp)==1)
    {
        if(ibrf.if_return=='n')
        {

            printf("%d\t",ibrf.s_id);
            printf("%d\t",ibrf.b_id);

            ibrf.t1=localtime(&ibrf.stm);
            strftime(str,25,"%x",ibrf.t1);
            printf("\t%s",str);

            time(&curnt);
            t3=localtime(&curnt);

            d_time = difftime(curnt,ibrf.stm);

            if(d_time>=1296000)
            {
                late=d_time/86400;
                printf("\t%d",late+1);
                fine=(late+1)*2;
                printf("\t%d",fine);
            }

            printf("\n");
        }
    }
    fclose(fp);
}


void delete_database()
{
    int ch;
    char ch2;

    while(1)
    {
        system("cls");
        printf("1. Delete Student Database\n");
        printf("2. Delete Book Database\n");
        printf("3. Delete Whole Database\n");
        printf("4. Delete Book Transaction Record\n");
        printf("5. Goto Main Menu\n");
        printf("\n\n Enter Your choice: ");
        scanf("%d",&ch);

        switch(ch)
        {
            case 1:
                remove("student_counter.dat");
                remove("student_record.dat");
                printf("\n\n Record is successfully deleted");
                getch();
                break;

            case 2:
                remove("book_counter.dat");
                remove("book_record.dat");
                printf("\n\n Record is successfully deleted");
                getch();
                break;

            case 3:
                remove("issued_record.dat");
                remove("librarian_account_detail.dat");
                remove("student_counter.dat");
                remove("student_record.dat");
                remove("book_counter.dat");
                remove("book_record.dat");
                printf("\n\n Record is successfully deleted");
                getch();
                break;

            case 4:
                remove("issued_record.dat");
                printf("\n\n Record is successfully deleted");
                getch();
                break;

            default:
                printf("\nInvalid Choice!! Please Try Again");
                getch();
                break;
        }

        printf("\nWant to Delete more records(y/n)? :" );
        fflush(stdin);
        scanf("%c",&ch2);
        if(ch2=='n')
            break;
    }
}


void student_menu()
{
    int ch;

    while(1)
    {
        system("cls");

        gotoxy(10,10);
        printf("1. Issue book");

        gotoxy(10,11);
        printf("2. Return Book");

        gotoxy(10,12);
        printf("3. View available books");

        gotoxy(10,13);
        printf("4.Search books");

        gotoxy(10,14);
        printf("5. Logout");

        gotoxy(10,15);
        printf("99. Exit");

        gotoxy(10,16);
        printf("Enter Your Choice: ");
        scanf("%d",&ch);

        switch(ch)
        {
            case 1:
                issue_book_stdnt();
                break;

            case 2:
                return_book_stdnt();
                break;

            case 3:
                view_avlbl_book();
                break;

            case 4:
                search_book();
                break;

            case 5:
                logout();
                break;

            case 99:
                exit_screen();
                break;

            default:
                gotoxy(10,17);
                printf("Invalid Entry Please Try Again !!");
                getch();
                break;
        }
    }
}

void issue_book_stdnt()
{
    FILE *fp,*ft;
    int temp1,temp2;
    char ch1,ch2;
    int find1,find2;

    while(1)
    {
            system("cls");

            printf("Enter book id: ");
            scanf("%d",&ibrf.b_id);

            ft=fopen("book_record.dat","rb");
            find1=0;
            while(fread(&book,sizeof(book),1,ft)==1)
            {   //printf("\nibrf.b_id: %d",ibrf.b_id);
                //printf("\nblist.id: %d",blist.id);
                if(ibrf.b_id==book.id)
                {
                    printf("\nBook Name: %s",book.name);
                    printf("\n\nAuthor: %s",book.author);
                    printf("\n\nPublicaation: %s",book.publicaton);
                    temp1=book.avlbl_qty;
                    find1=1;
                    if(book.avlbl_qty<2)
                    {
                        printf("\n\nThis book will not be issued because of only 1 copy remaining");
                        goto l2;
                    }
                }

            }
            if(find1==0)
                {
                    printf("\n\nno record found for this id number\n");
                    goto l2;
                }
            fclose(ft);


            ft=fopen("student_signin.dat","rb");
            fread(&ss,sizeof(ss),1,ft);
            //ibrf.s_id=ss.id;
            ibrf.s_id=s_login;
            fclose(ft);

            fp=fopen("student_record.dat","rb");
            find2=0;
            while(fread(&studnt,sizeof(studnt),1,fp)==1)
            {
                if(ibrf.s_id==studnt.id)
                {
                    printf("\nName: %s %s %s",studnt.fname,studnt.mname,studnt.lname);
                    printf("\nBranch: %s",studnt.branch);
                    temp2=studnt.issued_books;

                    find2=1;

                    if(2-studnt.issued_books==0)
                    {
                        printf("%s cannot issue this book");
                        goto l2;
                    }
                    else if(studnt.issued_books>3)
                    {
                        printf("%s cannot issue this book");
                        goto l2;
                    }

                }

            }
            if(find2==0)
                {
                    printf("no redord found for this student id");
                    goto l2;
                }
            fclose(fp);

            printf("\n\nDo want to issue this book(y/n)?: ");
            fflush(stdin);
            scanf("%c",&ch1);

            if(ch1=='y')
            {
                fp=fopen("student_record.dat","rb+");
                while(fread(&studnt,sizeof(studnt),1,fp)==1)
                {
                    if(ibrf.s_id==studnt.id)
                    {
                        temp2++;
                        studnt.issued_books=temp2;
                        fseek(fp,ftell(fp)-sizeof(studnt),0);
                        fwrite(&studnt,sizeof(studnt),1,fp);
                        fclose(fp);
                    }
                }

                ft=fopen("book_record.dat","rb+");
                while(fread(&book,sizeof(book),1,ft)==1)
                {
                    if(ibrf.b_id==book.id)
                    {
                        temp1--;
                        book.avlbl_qty=temp1;

                        fseek(ft,ftell(ft)-sizeof(book),0);
                        fwrite(&book,sizeof(book),1,ft);
                        fclose(ft);

                    }
                }


                fp=fopen("issued_record.dat","ab+");
                //ft=fopen("issued_record_2.dat","ab+");
                fseek(fp,0,SEEK_END);
                //current time
                time(&ibrf.stm);
                ibrf.t1=localtime(&ibrf.stm);
                ibrf.t2=NULL;
                ibrf.if_return='n';
                fwrite(&ibrf,sizeof(ibrf),1,fp);
                //fwrite(&ibrf,sizeof(ibrf),1,ft);
                fclose(fp);
                //fclose(ft);

        }
l2:
            printf("\nWant to issue more books(y/n)? :" );
            fflush(stdin);
            scanf("%c",&ch2);
            if(ch2=='n')
                break;
    }
}

void return_book_stdnt()
{
    FILE *fp,*ft;
        int bk_id;
        int stdnt_id;
        int find1=0;
        char ch2;
        struct tm *t3;
        time_t curnt;
        double d_time;
        int late,fine;

        while(1)
        {
            system("cls");
            printf("\nBook id: ");

            scanf("%d",&bk_id);
            //printf("\nStudent id: ");
            //scanf("%d",&stdnt_id);
            ft=fopen("student_signin.dat","rb");
            fread(&ss,sizeof(ss),1,ft);
            //bk_id=ss.id;
            stdnt_id=s_login;
            fclose(ft);

            fp=fopen("issued_record.dat","rb+");
            //ft=fopen("issued_record.dat","rb+");
            while(fread(&ibrf,sizeof(ibrf),1,fp)==1)
            {
                if(ibrf.b_id==bk_id && ibrf.s_id==stdnt_id)
                {
                    /*if(ibrf.if_return=='y')
                    {
                        continue;
                    }*/
                    ibrf.if_return='y';
                    //current time
                    time(&ibrf.stm2);
                    ibrf.t2=localtime(&ibrf.stm);
                    fseek(fp,ftell(fp)-sizeof(ibrf),0);
                    fwrite(&ibrf,sizeof(ibrf),1,fp);
                    fclose(fp);

                    fp=fopen("book_record.dat","rb+");
                    while(fread(&book,sizeof(book),1,fp)==1)
                    {
                        if(bk_id==book.id)
                        {
                            book.avlbl_qty++;
                            fseek(fp,ftell(fp)-sizeof(book),0);
                            fwrite(&book,sizeof(book),1,fp);
                            fclose(fp);
                        }
                    }

                    fp=fopen("student_record.dat","rb+");
                    while(fread(&studnt,sizeof(studnt),1,fp)==1)
                    {
                        if(stdnt_id==studnt.id)
                        {
                            studnt.issued_books--;
                            fseek(fp,ftell(fp)-sizeof(studnt),0);
                            fwrite(&studnt,sizeof(studnt),1,fp);
                            fclose(fp);
                        }
                    }

                    time(&curnt);
                    t3=localtime(&curnt);

                    d_time = difftime(curnt,ibrf.stm);

                    if(d_time>=1296000)
                    {
                        late=d_time/86400;
                        printf("You returned this Book %d days late so",late+1);
                        fine=(late+1)*2;
                        printf("You Have to Pay Fine RS.%d",fine);
                    }

                    find1=1;
                }

            }
            if(find1==0)
                {
                    printf("no such book issued");
                    goto l3;
                }

l3:
        printf("\nWant to Return more books(y/n)? :" );
        fflush(stdin);
        scanf("%c",&ch2);
        if(ch2=='n')
            break;

        }
}

void view_avlbl_book()
{
    int i=0,j;
    FILE *fp;

    system("cls");

    gotoxy(1,1);
    printf("*********************************Book List*****************************");

    gotoxy(2,2);
    printf("ID   NAME        Author      Publication       Available_Qty");
    j=4;
    fp=fopen("book_record.dat","rb");

    while(fread(&book,sizeof(book),1,fp)==1)
    {
        gotoxy(3,j);
        printf("%d",book.id);

        gotoxy(15,j);
        printf("%s",book.name);

        gotoxy(40,j);
        printf("%s",book.author);

        gotoxy(50,j);
        printf("%s",book.publicaton);

        //gotoxy(60,j);
        //printf("%d",book.price);

        //gotoxy(70,j);
        //printf("%d",book.qty);

        gotoxy(80,j);
        printf("%d",book.avlbl_qty);

        printf("\n\n");
        j++;
        i=i+book.avlbl_qty;
    }
        gotoxy(3,25);
        printf("Total Students: %d",i);
        fclose(fp);
        gotoxy(90,25);
        getch();
}

void search_book()
{
    int ch;

    while(1)
    {
        system("cls");
        printf("1. Search by id\n");
        printf("2. Search by name\n");
        printf("3. return to main menu\n");
        printf("4. exit");

        printf("Enter your Choice: ");
        scanf("%d",&ch);

        switch(ch)
        {
            case 1:
                search_by_id();
                break;

            case 2:
                search_by_name();
                break;

            case 3:
                student_menu();
                break;

            case 4:
                exit_screen();
                break;

            default:
                printf("Invalid Entry, Please try again!!");
                getch();
                break;
            }
    }
}


void logout()
{
    s_login=0;
    //remove("student_signin.dat");
    login_menu();
}


void search_by_id()
{
    system("cls");
    int id; FILE *fp;
    gotoxy(25,4);
    printf("****Search Books By Id****");
    gotoxy(20,5);
    printf("Enter the book id:");
    scanf("%d",&id);
    int findBook = 0;
    fp = fopen("book_record.dat","rb");
    while(fread(&book,sizeof(book),1,fp)==1)
        {
        if(book.id==id)
        {
            Sleep(2);
            gotoxy(20,7);
            printf("The Book is available");
            gotoxy(20,9);
            printf("ID:%d",book.id);
            gotoxy(20,10);
            printf("Name:%s",book.name);
            gotoxy(20,11);
            printf("Author:%s ",book.author);
            gotoxy(20,12);
            printf("Qantity:%d ",book.qty);
            gotoxy(20,13);
            printf("Price:Rs.%.2f",book.price);
            gotoxy(20,14);
            findBook = 1;
        }
    }
    if(findBook == 0){  //checks whether conditiion enters inside loop or not
        gotoxy(22,9);
        printf("\aNo Record Found");
    }
    fclose(fp);
    gotoxy(20,17);
    printf("Try another search?(Y/N)");
    if(getch()=='y')
        search_by_id();
    else
        student_menu();
}


void search_by_name()
{

}

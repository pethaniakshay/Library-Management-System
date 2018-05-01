#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

void add_book();
void delete_book();
//void return_book();
//void issue();
void add_window();
void get_data();
int main_menu();
void view_book();
void edit_book();
void add_student();
void getbranch();
void add_stdnt_data();
void view_stdnt();
int stdnt_counter(int ch);

struct book
{
    int id;
    int sub_id;
    //char *branch;
    char name[10];
    char Author[20];
    char publicaton[20];
    int quantity;
    float Price;

    //int rackno;
    //char *cat;
};

struct student
{
    long long int id;
    char fname[12];
    char mname[12];
    char lname[12];
    //char branch[15];
    char *branch;
};

struct student_counter
{
    int cs;
    int ee;
    int ec;
    int civil;
    int mech;
    int ic;
};

struct student stdnt;
struct book blist;
struct student_counter sc;

int main()
{
    main_menu();

    return 0;
}

int main_menu()
{
    int ch;
    while(1)
    {
        system("cls");

        printf("1. Add Book\n");
        printf("2. Delete book\n");
        printf("3. issue book\n");
        printf("4. return book\n");
        printf("5. view book list\n");
        printf("6. Edit book record\n");
        printf("7. Create student account\n");
        printf("8. View student record\n");
        printf("99. exit\n");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
                add_book();
                getch();
                break;

            case 2:
                delete_book();
                getch();
                break;

            /*case 3:
                issue();
                getch();
                break;
            case 4:
                return_book();
                getch();
                break;*/
            case 5:
                view_book();
                getch();
                break;
            case 6:
                edit_book();
                getch();
                break;
            case 7:
                add_student();
                getch();
                break;
            case 8:
                view_stdnt();
                getch();
                break;
            case 99:
                exit(0);
                getch();
                break;
            default:
                printf("invalid choice");
                getch();
                break;

        }
    }
    return 0;
}

/*void issue()
{
    system("cls");
    //FILE *mast_record;



}

void return_book()
{

}*/

void add_book()
{
    FILE *fp;
    int i,ch;

    system("cls");

    fp=fopen("master_record.dat","ab+");

    l1:
    system("cls");
    add_window();
    printf("\n\nEnter your choice: ");
    scanf("%d",&ch);
    printf("\n\n");
        switch(ch)
        {
            case 1:
                //blist.branch="cs";
                get_data();
                blist.id=((ch*1000000)+(ch*100000)+(100*blist.sub_id)+(blist.quantity));
                getch();
                break;
            case 2:
                //blist.branch="ec";
                get_data();
                blist.id=((ch*1000000)+(ch*100000)+(100*blist.sub_id)+(blist.quantity));
                getch();
                break;
            case 3:
                //blist.branch="ee";
                get_data();
                blist.id=((ch*1000000)+(ch*100000)+(100*blist.sub_id)+(blist.quantity));
                getch();
                break;
            case 4:
                //blist.branch="civil";
                get_data();
                blist.id=((ch*1000000)+(ch*100000)+(100*blist.sub_id)+(blist.quantity));
                getch();
                break;
            case 5:
                //blist.branch="mech";
                get_data();
                blist.id=((ch*1000000)+(ch*100000)+(100*blist.sub_id)+(blist.quantity));
                getch();
                break;
            case 6:
                //blist.branch="maths";
                get_data();
                blist.id=((ch*1000000)+(ch*100000)+(100*blist.sub_id)+(blist.quantity));
                getch();
                break;
            case 7:
                main_menu();
                getch();
                break;
            default:
                printf("Invalid choice! Try again");
                goto l1;
                getch();
                break;
        }

    fseek(fp,0,SEEK_END);
    fwrite(&blist,sizeof(blist),1,fp);
    fclose(fp);

    printf("The record is sucessfully saved");
    printf("\nSave any more?(Y / N):");

    if(getch()=='n')
        main_menu();
    else
    {
        system("cls");
        add_book();
    }
}

void delete_book()
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

        fp = fopen("master_record.dat","rb+");

		while(fread(&blist,sizeof(blist),1,fp)==1)
		{
            if(blist.id==d)
			{
                printf("The book record is available");
                printf("Book name is %s",blist.name);
                findBook = 1;
                printf("Do you want to delete it?(Y/N):");

                if(getch()=='y')
				{
                    ft=fopen("test.dat","wb");  //temporary file for delete
                    rewind(fp);

                    while(fread(&blist,sizeof(blist),1,fp)==1)
					{
                        if(blist.id!=d)
						{
                            fwrite(&blist,sizeof(blist),1,ft);//write all in tempory file except that
                        }                              //we want to delete
                    }

                    fclose(fp);
                    fclose(ft);

                    remove("master_record.dat");
                    rename("test.dat","master_record.dat"); //copy all item from temporary file to fp except that
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

void add_window()
//function for choosing a book in which it related
{

	printf("1. Computer\n");
    printf("2. Electronics\n");
    printf("3. Electrical\n");
	printf("4. Civil\n");
	printf("5. Mechanical\n");
	printf("6. Mathematics\n");
	printf("7. Back to main menu\n");
}

void get_data()
//for adding redord of books
{
    system("cls");

    printf("\nSubject_id: ");
    scanf("%d",&blist.sub_id);

    fflush(stdin);


    //printf("%s",&blist.name);

    printf("\nAutor: ");
    gets(blist.Author);

    fflush(stdin);

    printf("\nPublication: ");
    gets(blist.publicaton);

    printf("\nBook Name: ");
    fflush(stdin);
    gets(blist.name);

    printf("\nPrice: ");
    scanf("%f",&blist.Price);

    printf("\nQuantity:");
    scanf("%d",&blist.quantity);
}

void view_book()
{
    FILE *fp;
    system("cls");

    printf("*********************************Book List*****************************\n\n");
    printf("ID       BOOKNAME     AUTHOR       QTY      PRICE      PUBLICATION\n\n");

    fp=fopen("master_record.dat","rb");
    while(fread(&blist,sizeof(blist),1,fp)==1)
	{
        printf("%d\t  ",blist.id);
        printf("%s\t\t",blist.name);
        printf("%s\t   ",blist.Author);
        printf("%d\t  ",blist.quantity);
        printf("%5.0f\t\t",blist.Price);
        printf("%s\n",blist.publicaton);
        printf("\n");
        //j++;
    }
    fclose(fp);
}

void edit_book()
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

		fp=fopen("master_record.dat","rb+");

		//while(fread(&blist,sizeof(blist,1,fp)==1)
        while(fread(&blist,sizeof(blist),1,fp)==1)
		{
			if(blist.id==d)
			{

				printf("The book is availble\n");
				printf("The Book ID:%d\n",blist.id);
				printf("The Current data is:\n");

				printf("Id: %d\n Name: %s\n Author: %s\n",blist.id,blist.name,blist.Author);
				printf("Publication: %s\n Price: %5.0f\n qty: %d\n",blist.publicaton,blist.Price,blist.quantity);

                printf("want to modify Name (y/n)?");
                if(ch=getch()=='y')
                {
                    printf("\nEnter new name:");
                    fflush(stdin);
                    //scanf("%s",blist.name);
                    gets(blist.name);
                }

                printf("\nWant to modify Author (y/n)?");
				if(ch=getch()=='y')
                {
                    printf("\nEnter new Author:");
                    //scanf("%s",blist.Author);
                    gets(blist.Author);
                }

                printf("\nWant to modify publication (y/n)?");
				if(ch=getch()=='y')
                {
                    printf("\nEnter new publication:");
                    //scanf("%s",&blist.publicaton);
                    gets(blist.publicaton);
                }

                printf("\nWant to modify price (y/n)?");
				if(ch=getch()=='y')
                {
                    printf("\nEnter new price: ");
                    scanf("%f",&blist.Price);
                }

                printf("\nWant to modify quantity (y/n)?: ");
				if(ch=getch()=='y')
                {
                    printf("\nEnter new quantity:");
                    scanf("%d",&blist.quantity);
                }

                printf("\nThe record is modified");

				fseek(fp,ftell(fp)-sizeof(blist),0);
				fwrite(&blist,sizeof(blist),1,fp);
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
		main_menu();

}

/*int checkid(int t)  //check whether the book is exist in library or not
{
    FILE *temp;
	temp = fopen("master_record.dat","rb+");
	while(fread(&blist,sizeof(blist),1,temp)==1)
        if(blist.id == t)
		{
            fclose(temp);
            return 0;
        }
        fclose(temp);
        return 1;

}*/

void add_student()
{

    FILE *fp,*ft;
    int ch,counter;
    system("cls");

    fp = fopen("stdnt_record.dat","ab+");


    while(1)
    {
        l1:
        ch=select_branch();
        switch(ch)
        //switch(select_branch())
        {
            case 1:
                stdnt.branch="cs";
                add_stdnt_data();
                counter=stdnt_counter(ch);
                stdnt.id=(ch*1000)+counter;
                //getch();
                break;
            case 2:
                stdnt.branch="ee";
                add_stdnt_data();
                counter=stdnt_counter(ch);
                stdnt.id=(ch*1000)+counter;
                //getch();
                break;
            case 3:
                stdnt.branch="ec";
                add_stdnt_data();
                counter=stdnt_counter(ch);
                stdnt.id=(ch*1000)+counter;
                //getch();
                break;
            case 4:
                stdnt.branch="civil";
                add_stdnt_data();
                counter=stdnt_counter(ch);
                stdnt.id=(ch*1000)+counter;
                //getch();
                break;
            case 5:
                stdnt.branch="mech";
                add_stdnt_data();
                counter=stdnt_counter(ch);
                stdnt.id=(ch*1000)+counter;
                //getch();
                break;
            case 6:
                stdnt.branch="ic";
                add_stdnt_data();
                counter=stdnt_counter(ch);
                stdnt.id=(ch*1000)+counter;
                //getch();
                break;
            default :
                printf("Invalid Entry please try again!");
                //getch();
                goto l1;
                break;
        }
        fseek(fp,0,SEEK_END);
        fwrite(&stdnt,sizeof(stdnt),1,fp);
        fclose(fp);
        printf("Record saved successfuluy\n\n");

        printf("want to add more record (y/n)?: ");
        if(getch()=='n')
            break;

    }
}

int select_branch()
{
        int ch;
        printf("\t*******select your branch*******\n");
        printf("1. Computer science engineering\n");
        printf("2. Electrical Enggineering\n");
        printf("3. Electronic & communication enginnering\n");
        printf("4. civil engineering\n");
        printf("5. Mechanical engineering\n");
        printf("6. Instrumental & control engineering\n");
        scanf("%d",&ch);
        return ch;
}

void add_stdnt_data()
{
        printf("\nFname: ");
        fflush(stdin);
        gets(stdnt.fname);
        printf("\nMname: ");
        fflush(stdin);
        gets(stdnt.mname);
        printf("\nLname: ");
        fflush(stdin);
        gets(stdnt.lname);
}

void view_stdnt()
{
    FILE *fp;
    system("cls");

    printf("********************************* student list *****************************\n\n");
    printf("ID       fname mname lname   branch\n\n");

    fp=fopen("stdnt_record.dat","rb");
    while(fread(&stdnt,sizeof(stdnt),1,fp)==1)
	{
        printf("%lld\t",stdnt.id);
        printf("%s %s %s\t",stdnt.fname,stdnt.mname,stdnt.lname);
        printf("%s\n",stdnt.branch);
    }
    fclose(fp);
}

int stdnt_counter(int ch)
{
    int counter=100,ap;
    FILE *fp;

    sc.civil=0;
    sc.cs=0;
    sc.ec=0;
    sc.ee=0;
    sc.ic=0;
    sc.mech=0;
    switch(ch)
    {
    case 1:
        fp=fopen("stdnt_counter.dat","rb");
        sc.cs=getw(fp);
        ap=sc.cs;
        fclose(fp);

        fp=fopen("stdnt_counter.dat","ab+");

        if(ap>=100)
            sc.cs++;

        else
        {
            sc.cs=100;
            sc.cs++;
        }

        putw(sc.cs,fp);
        fclose(fp);
        return sc.cs;
        break;

        case 2:
        fp=fopen("stdnt_counter.dat","rb");
        sc.ee=getw(fp);
        ap=sc.ee;
        fclose(fp);

        fp=fopen("stdnt_counter.dat","w");

        if(ap>=100)
            sc.ee++;

        else
        {
            sc.ee=100;
            sc.ee++;
        }

        putw(sc.ee,fp);
        fclose(fp);
        return sc.ee;
        break;

        case 3:
        fp=fopen("stdnt_counter.dat","rb");
        sc.ec=getw(fp);
        ap=sc.ec;
        fclose(fp);

        fp=fopen("stdnt_counter.dat","ab+");

        if(ap>=100)
            sc.ec++;

        else
        {
            sc.ec=100;
            sc.ec++;
        }

        putw(sc.ec,fp);
        fclose(fp);
        return sc.ec;
        break;

        case 4:
        fp=fopen("stdnt_counter.dat","rb");
        sc.civil=getw(fp);
        ap=sc.civil;
        fclose(fp);

        fp=fopen("stdnt_counter.dat","ab+");

        if(ap>=100)
            sc.civil++;

        else
        {
            sc.civil=100;
            sc.civil++;
        }

        putw(sc.civil,fp);
        fclose(fp);
        return sc.civil;
        break;

        case 5:
        fp=fopen("stdnt_counter.dat","rb");
        sc.mech=getw(fp);
        ap=sc.mech;
        fclose(fp);

        fp=fopen("stdnt_counter.dat","ab+");

        if(ap>=100)
            sc.mech++;

        else
        {
            sc.mech=100;
            sc.mech++;
        }

        putw(sc.mech,fp);
        fclose(fp);
        return sc.mech;
        break;

        case 6:
        fp=fopen("stdnt_counter.dat","rb");
        sc.ic=getw(fp);
        ap=sc.ic;
        fclose(fp);

        fp=fopen("stdnt_counter.dat","ab+");

        if(ap>=100)
            sc.ic++;

        else
        {
            sc.ic=100;
            sc.ic++;
        }

        putw(sc.ic,fp);
        fclose(fp);
        return sc.ic;
        break;

        default:
            printf("invalid entery");
            return 0;
    }

}

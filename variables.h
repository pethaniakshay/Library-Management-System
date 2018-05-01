#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<windows.h>




COORD coord = {0, 0};
FILE *login;


void welcome_screen();

void exit_screen();

void gotoxy(int x, int y);

void get_password(char* pass);

void login_menu();
void librarian_signup();
void librarian_signin();
void student_signin();

void librarian_menu();

void manage_book_record();
void add_book_record();
int select_stream();
void add_book_data();
int book_counter(int ch);
void delete_book_record();
void modify_book_record();
void view_book_record();

void manage_student_record();
void add_student_record();
int select_branch();
void add_studnt_data();
int studnt_counter(int ch);
void delete_student_record();
void modify_student_record();
void view_student_record();

void manage_books_transaction();
void issue_book();
void return_book();
void view_issued_book();
void view_not_retunt_in_time();

void student_menu();
void issue_book_stdnt();
void return_book_stdnt();
void view_avlbl_book();
void search_book();
void search_by_id();
void search_by_name();
void logout();

void delete_database();

void drawrectangle(int x1, int y1, int x2, int y2);
void draw_star_box(int x1, int y1, int x2, int y2);


void set_text_color(int color);



struct librarian_account_detail
{
    char login_id[25];
    char password[25];
};
struct librarian_account_detail lad;


struct student_signin
{
    int id;
};
struct student_signin ss;

struct student_record
{
    int id;
    char fname[15];
    char mname[15];
    char lname[15];
    char *branch;
    char password[25];
    int issued_books;
};
struct student_record studnt;


struct student_counter
{
    int cs;
    int ee;
    int ec;
    int civil;
    int mech;
    int ic;
};
struct student_counter sc;


struct book_record
{
    int id;
    char *stream;
    char name[25];
    char author[20];
    char publicaton[20];
    int qty; // for total books qty in main database
    float price;
    int avlbl_qty;  //return value of available books in library
};
struct book_record book;


struct book_counter
{
    int cs;
    int ee;
    int ec;
    int civil;
    int mech;
    int ic;
    int maths;
    int others;
};
struct book_counter bc;


struct issue_book_record_file
{
    int b_id;
    int s_id;
    //for issue book date
    struct tm *t1;
    time_t stm;
    //for return book date
    struct tm *t2;
    time_t stm2;
    char if_return;
};
struct issue_book_record_file ibrf;


double diff_of_time;
int s_login=0;

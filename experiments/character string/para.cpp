#include<stdio.h>
#define MAX 500

int main(){

    char arr[MAX];

    printf("Enter any paragraph which can include spaces or new line.\n");
    printf("To exit press the tab key.\n");
    scanf("%[^\t]s",arr);

    printf("You had entered: \n");
    printf("%s",arr);

    return 0;
}

#include<stdio.h>
#include<time.h>

int main()
{
    time_t now;
    struct tm *tm;
    now=time(0);
    tm=localtime(&now);
    if((tm==NULL))
    {
        printf("error extracting time\n");
        return 1;
    }
    printf("Date: %04d - %02d - %02d \n",tm->tm_year+1900,tm->tm_mon+1,tm->tm_mday);
    printf("Time: %02d : %02d : %02d\n",tm->tm_hour,tm->tm_min,tm->tm_sec);

    return 0;
}

#include <stdio.h>
#include <time.h>
#include <sys/time.h>

void getTime()
{
    FILE* fp = fopen("Time.txt","w+");
    struct timeval usec_time;
    time_t now = time(0);
    gettimeofday(&usec_time,NULL);
    // format time
    struct tm *current = localtime(&now);
    printf("%d:%d:%d\n",current->tm_hour, current->tm_min, current->tm_sec);
    fprintf(fp,"%d:%d:%d\n",current->tm_hour, current->tm_min, current->tm_sec);
}



int main(int argc,char* argv[])
{
    getTime();
    return
}

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<limits.h>

int main(void) {

	time_t start_time;
	time_t end_time;
	time_t convert_back_example1;
	time_t convert_back_example2;
	struct tm start_str_time;
	struct tm end_str_time;

	// Fill our starting structure
	start_str_time.tm_sec = 0;
	start_str_time.tm_min = 0;
	start_str_time.tm_hour = 0;
	start_str_time.tm_mday = 1;
	start_str_time.tm_mon = 0;
	start_str_time.tm_year = 2010-1900;
	start_str_time.tm_isdst = 0;

        // Fill our end structure
	end_str_time.tm_sec = 61;
	end_str_time.tm_min = 59;
	end_str_time.tm_hour = 23;
	end_str_time.tm_mday = 31;
	end_str_time.tm_mon = 11;
	end_str_time.tm_year = 2019-1900;
	end_str_time.tm_isdst = 0;

	start_time = mktime(&start_str_time);
	end_time = mktime(&end_str_time);

	printf("The difference was %f seconds.\n", difftime(end_time, start_time));

	// - Seconds to date/time examples
        // Example one
	start_str_time.tm_sec += difftime(end_time, start_time);
	convert_back_example1 = mktime(&start_str_time);
	printf("%s", asctime(localtime(&convert_back_example1)));

	// Example two shows string to date / time conversion, since epoch time.
	const char diff_time[] = "315532801";
	// Ignore milliseconds
	convert_back_example2 = atoi(diff_time);
	printf("Since epoch time: %s", asctime(localtime(&convert_back_example2)));

	return 0;
}

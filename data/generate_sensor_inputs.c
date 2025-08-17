/* Script that generates random parameters to simulate sensors. */

#include <stdio.h>
#include <time.h>

void print_datetime();

int main() {
    print_datetime();
    return 0;
}

void print_datetime(){
    /* Get date and time, supposing the system has an initialized system clock.
    The date and time have been set via a hardware Real-Time Clock or Network Time Protocol sync */

    time_t rawdt = time(NULL); // get timelapse in seconds starting from 1/1/1970 until now
    struct tm *now = localtime(&rawdt); // convert the seconds in years, months, days, hours, minutes, seconds

    // print the current date and time (YYYY-MM-DD HH:MM:SS)
    printf("%04d-%02d-%02d %02d:%02d:%02d\n",
           now->tm_year + 1900, now->tm_mon + 1, now->tm_mday,
           now->tm_hour, now->tm_min, now->tm_sec);
}
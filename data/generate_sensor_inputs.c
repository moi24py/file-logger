/* Script that generates random parameters to simulate sensors. */

#include <stdio.h>
#include <time.h>

void print_datetime();

int main() {
    print_date();
    return 0;
}

void print_datetime(){
        /* Get date and time, supposing the system has an initialized system clock.
    The date and time have been set via a hardware Real-Time Clock or Network Time Protocol sync */
    time_t now = time(NULL); // get timelapse starting from 1/1/1970 until now
    struct tm *t = localtime(&now); // convert the number in time

    // print the current date and time (YYYY-MM-DD HH:MM:SS)
    printf("%04d-%02d-%02d %02d:%02d:%02d\n",
           t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
           t->tm_hour, t->tm_min, t->tm_sec);
}
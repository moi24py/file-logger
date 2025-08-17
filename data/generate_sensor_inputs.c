/* Script that generates random parameters to simulate sensors. */

#include <stdio.h>
#include <time.h>

int formatted_datetime(char *buffer);

int main() {
    char str[20];
    formatted_datetime(str);
    return 0;
}

int formatted_datetime(char *buffer){
    /* Get date and time, supposing the system has an initialized system clock.
    The date and time have been set via a hardware Real-Time Clock or Network Time Protocol sync */
    time_t rawdt = time(NULL); // get timelapse in seconds starting from 1/1/1970 until now
    struct tm *now = localtime(&rawdt); // convert the seconds in years, months, days, hours, minutes, seconds

    /* Print the current date and time (YYYY-MM-DD HH:MM:SS) */
    //printf("%04d-%02d-%02d %02d:%02d:%02d\n",
    //       now->tm_year + 1900, now->tm_mon + 1, now->tm_mday,
    //       now->tm_hour, now->tm_min, now->tm_sec);
    
    /* If current date and time have not been retrieved */
    if (!now){
        perror("Error in retrieving current date and time");
        return 1;
    }

    /* Create a formatted string with current date and time (YYYY-MM-DD HH:MM:SS) */
    int written_bytes = snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d %02d:%02d:%02d",
                                  now->tm_year + 1900, now->tm_mon + 1, now->tm_mday,
                                  now->tm_hour, now->tm_min, now->tm_sec);
    
    /* If snprintf() had an error, returned an empty string, or a truncated string */
    if (written_bytes < 0 || written_bytes >= sizeof(buffer)) {
        perror("Error in generating the formatted string");
        return 1;
    }
    
    /* DEBUG: print formatted string */
    printf("%s\n", buffer);

    return 0;
}
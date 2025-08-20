#include <stdio.h>
#include <time.h>
#include <stdlib.h>

struct tm* get_datetime();
int formatted_datetime(char *buffer, size_t size, struct tm *now);

/* Structure for random parameters */
typedef struct Parameters{
    float temp;
    unsigned short hr;
    unsigned short spo2;
} params;

int main() {
    srand(time(NULL));
    int i;
    for (i = 0; i < 50; i++){

    /* Array that will store current date and time */
    char datetime[20];
    size_t len = sizeof(datetime);

    /* Get current date and time */
    struct tm* current_datetime = get_datetime();
    if (!current_datetime) {
        fprintf(stderr, "Failed to get current datetime\n");
        return 1;
    }

    /* Check if the date and time have been stored in the datetime array */
    int actually_written = formatted_datetime(datetime, len, current_datetime);
    if (actually_written < 0) {
        fprintf(stderr, "Formatting error\n");
        return 1;
    }

    /* Struct that stores one temperature, one heart rate, one spO2 */
    params *ths = malloc(sizeof(params));
    if (ths == NULL){
        perror("Cannot allocate memory for ths pointer");
    }
    ths->temp = rand() % 44;
    ths->hr = rand() % 121;
    ths->spo2 = rand() % 101;

    /* Open sensors_data.csv */
    FILE *fp = fopen("sensors_data.csv", "a");
    if (fp == NULL){
        perror("Error in opening sensors_data.csv");
        return 1;
    }
    printf("sensors_data.csv opened\n");

    /* Write to sensors_data.csv*/
    size_t written = fprintf(fp, "%s", datetime); // write current date and time
    if (written < 0) {
        perror("Error writing to file");
        fclose(fp);
        return 1;
    }
    fflush(fp); // clean buffer, force write in file
    printf("date and time successfully written to sensors_data.csv\n");

    written = fprintf(fp, ",%.1f,%d,%d\n", ths->temp, ths->hr, ths->spo2); // write temp, hr, spo2
    if (written < 0) {
        perror("Error writing to file");
        fclose(fp);
        return 1;
    }
    fflush(fp); // clean buffer, force write in file
    printf("params successfully written to sensors_data.csv\n");

    /* Close sensors_data.csv */
    if (fclose(fp) != 0){
        perror("Error closing sensors_data.csv");
        return 1;
    }
    printf("sensors.csv closed\n");

    free(ths);

    }
    return 0;
}

/* Function that gets current date and time */
struct tm* get_datetime(){
    time_t rawdt = time(NULL);
    struct tm *now = localtime(&rawdt);
    if (!now){
        perror("Error retrieving current date and time");
        return NULL;
    }
    return now;
}

/* Function that stores in the datetime array the formatted date and time string */
int formatted_datetime(char *buffer, size_t size, struct tm *now){
    int written_bytes = snprintf(buffer, size, "%04d-%02d-%02d %02d:%02d:%02d",
                                 now->tm_year + 1900, now->tm_mon + 1, now->tm_mday,
                                 now->tm_hour, now->tm_min, now->tm_sec);
    if (written_bytes < 0 || (size_t)written_bytes >= size) {
        return -1;
    }
    return written_bytes;
}
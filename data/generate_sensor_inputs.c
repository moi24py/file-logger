#include <stdio.h>
#include <time.h>

struct tm* get_datetime();
int formatted_datetime(char *buffer, size_t size, struct tm *now);

int main() {
    char str[20];
    size_t len = sizeof(str);

    struct tm* current = get_datetime();
    if (!current) {
        fprintf(stderr, "Failed to get current datetime\n");
        return 1;
    }

    int actually_written = formatted_datetime(str, len, current);
    if (actually_written < 0) {
        fprintf(stderr, "Formatting error\n");
        return 1;
    }

    FILE *fp = fopen("sensors_data.csv", "a");
    if (fp == NULL){
        perror("Error in opening sensors_data.csv");
        return 1;
    }
    printf("sensors_data.csv opened\n");

    size_t written = fwrite(str, 1, actually_written, fp);
    if (written != (size_t)actually_written) {
        perror("Error writing to file");
        fclose(fp);
        return 1;
    }

    fflush(fp);
    printf("date and time successfully written to sensors_data.csv\n");

    if (fclose(fp) != 0){
        perror("Error closing sensors_data.csv");
        return 1;
    }

    return 0;
}

struct tm* get_datetime(){
    time_t rawdt = time(NULL);
    struct tm *now = localtime(&rawdt);
    if (!now){
        perror("Error retrieving current date and time");
        return NULL;
    }
    return now;
}

int formatted_datetime(char *buffer, size_t size, struct tm *now){
    int written_bytes = snprintf(buffer, size, "%04d-%02d-%02d %02d:%02d:%02d",
                                 now->tm_year + 1900, now->tm_mon + 1, now->tm_mday,
                                 now->tm_hour, now->tm_min, now->tm_sec);
    if (written_bytes < 0 || (size_t)written_bytes >= size) {
        return -1;
    }
    return written_bytes;
}
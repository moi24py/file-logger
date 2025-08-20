#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINE_LEN 256

int log_if_out_of_range(FILE *log_file, const char *datetime, float temp, int hr, int spo2);

int main() {
    // Open sensors_data.csv
    FILE *fp = fopen("../data/sensors_data.csv", "r");
    if (!fp) {
        perror("Cannot open sensors_data.csv");
        return 1;
    }
    // Open system.log
    FILE *log = fopen("../system.log", "a");
    if (!log) {
        perror("Cannot open system.log");
        fclose(fp);
        return 1;
    }
   
    char line[LINE_LEN]; // String buffer
    fgets(line, sizeof(line), fp); // Skip .csv header

    // Parse sensors_data.csv
    while (fgets(line, sizeof(line), fp)) {
        char *token;
        char datetime[25];
        float temp;
        int hr, spo2;

        // Get timestamp
        token = strtok(line, ",");
        if (!token) continue;
        strncpy(datetime, token, sizeof(datetime));
        datetime[sizeof(datetime) - 1] = '\0';

        // Get temperature
        token = strtok(NULL, ",");
        if (!token) continue;
        temp = atof(token);

        // Get heart rate
        token = strtok(NULL, ",");
        if (!token) continue;
        hr = atoi(token);

        // Get SpO2
        token = strtok(NULL, ",");
        if (!token) continue;
        spo2 = atoi(token);

        // Verify and log potential errors when writing to system.log
        if (log_if_out_of_range(log, datetime, temp, hr, spo2) < 0) {
            perror("Error writing to system.log");
            fclose(fp);
            fclose(log);
            return 1;
        }
    }

    fclose(fp);
    fclose(log);
    return 0;
}

// Function that logs errors when writing to system.log
int log_if_out_of_range(FILE *log_file, const char *datetime, float temp, int hr, int spo2) {
    // Stores the return value of fprintf to verify successful write
    int written;
    int error_flag = 0;
    // Check temperature
    if (temp < 37.7 || temp > 39.2) {
        written = fprintf(log_file, "%s Temperature out of range: %.1f\n", datetime, temp);
        if (written < 0) return -1;
        error_flag = 1;
    }
    // Check heart rate
    if (hr < 60 || hr > 100) {
        written = fprintf(log_file, "%s Heart rate out of range: %d\n", datetime, hr);
        if (written < 0) return -1;
        error_flag = 1;
    }
    // Check spO2
    if (spo2 < 97) {
        written = fprintf(log_file, "%s SpO2 low: %d%%\n", datetime, spo2);
        if (written < 0) return -1;
        error_flag = 1;
    }

    if (error_flag) {
        fflush(log_file);
    }

    return 0;
}

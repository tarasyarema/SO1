#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *passenger_count;
    int *trip_time_in_secs;
} Data;

int get_column_int(char* line, int num) {
    char new_line[256];
    char* tok;
    int retvalue;

    strncpy(new_line, line, 256);
    for (tok = strtok(new_line, ",\n"); tok; tok = strtok(NULL, ",\n")) {
        if (!--num) {
            retvalue = (int) strtol(tok, (char **)NULL, 10);
            return retvalue;
        }
    }

    printf("ERROR: get_column_int\n");
    exit(1); 
}

int get_data(Data *data, FILE *file, int max) {
    char line[256];
    int temp, pos;

    // If we are at the beginning of the file, we ignore
    // the header of the file.
    if (ftell(file) == 0)
        fgets(line, sizeof(line), file);

    pos = 0;
    while (pos < max && fgets(line, sizeof(line), file)) {
        temp = get_column_int(line, 8);
        data->passenger_count[pos] = temp;
        temp = get_column_int(line, 9);
        data->trip_time_in_secs[pos] = temp;
        pos++;
    }

    return pos;
}

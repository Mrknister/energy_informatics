#include "save_data.h"
#include <stdio.h>
#include <string.h>

int save_float_array(const char* file_name, float* buffer, int buffer_size, int num_data, int offset)
{
    FILE * f = fopen(file_name,"w");
    if(f==NULL) {
        perror("Could not sve to file\n");
        return 0;
    }
    int counter = 0;
    for(; counter < num_data; ++counter) {
        if(fprintf(f, "%f\n", buffer[(offset+ counter) % buffer_size]) < 9) {
            fclose(f);
            return 0;
        }
    }
    fclose(f);
    return 1;
}


int log_event(const char* log_folder, int event_time, float* buffer, int buffer_size, int num_data, int event_pos)
{
    char path_buffer[1024];
    if(strlen(log_folder) == 0) {
        log_folder = "./";
    }
    sprintf(path_buffer, "%sevent_%i.dat", log_folder, event_time);
    printf("logging event to %s\n", path_buffer);
    return save_float_array(path_buffer, buffer, buffer_size,num_data, event_pos);
}


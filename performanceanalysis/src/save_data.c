#include "save_data.h"
#include <stdio.h>
#include <string.h>

int save_float_array(const char* file_name, float* buffer, int buffer_size, int num_data, int offset)
{
    FILE* f = fopen(file_name, "w");
    if (f == NULL) {
        perror("Could not sve to file\n");
        return 0;
    }
    int counter = 0;
    for (; counter < num_data; ++counter) {
        int pos = (offset + counter) % buffer_size;
        float val = buffer[pos];
        if (fprintf(f, "%f\n", val) < 0) {
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
    if (strlen(log_folder) == 0) {
        log_folder = "./";
    }
    int bytes_written = snprintf(path_buffer, 1024, "%sevent_%i.dat", log_folder, event_time);
    if (bytes_written >= 1024) {
        printf("path too long %s\n", log_folder);
        return 0;
    }
    printf("logging event to %s\n", path_buffer);
    return save_float_array(path_buffer, buffer, buffer_size, num_data, event_pos);
}

int log_rms_feature(const char* log_folder, int event_time, RootMeanSquareFeature* feature)
{
    char path_buffer[1024];
    if (strlen(log_folder) == 0) {
        log_folder = "./";
    }

    int bytes_written = snprintf(path_buffer, 1024, "%srms_feature_%i.dat", log_folder, event_time);
    if (bytes_written >= 1024) {
        printf("path too long %s\n", log_folder);
        return 0;
    }
    printf("logging root mean square feature to %s\n", path_buffer);
    return save_float_array(path_buffer,
                            feature->data,
                            ANALYZED_FEATURES_PER_WAVE,
                            ANALYZED_FEATURES_PER_WAVE,
                            0
                           );
}
int log_fft_feature(const char* log_folder, int event_time, FastFourierFeature* feature)
{
    char path_buffer[1024];
    if (strlen(log_folder) == 0) {
        log_folder = "./";
    }

    int bytes_written = snprintf(path_buffer, 1024, "%sfft_feature_%i.dat", log_folder, event_time);
    if (bytes_written >= 1024) {
        printf("path too long %s\n", log_folder);
        return 0;
    }
    printf("logging fast fourier transform feature to %s\n", path_buffer);
    FILE* f = fopen(path_buffer, "w");
    if (f == NULL) {
        perror("Could not sve to file\n");
        return 0;
    }
    int counter = 0;
    for (; counter < DATA_POINTS_PER_FEATURE; ++counter) {
        if (fprintf(f, "%f\n", feature->data[counter].r) < 0) {
            fclose(f);
            return 0;
        }
    }
    fclose(f);
    return 1;
}


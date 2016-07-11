#include "file_loader.h"
#include "data_loader_config.h"

#include <sndfile.h>


static int file_ok(SF_INFO* file_info, SNDFILE* file);

int open_uk_dale_file(const char* fname, UkDaleFile* file)
{
    SF_INFO file_info;
    file->snd_file = sf_open(fname, SFM_READ, &file_info);
    long int time = 0, garbage;
    char garbage_2;
    sscanf(fname,"%ld_%ld.fla%[c]", &time, &garbage,&garbage_2);
    file->start_time = time;

    if (! file_ok(&file_info, file->snd_file)) {
        if (file->snd_file != NULL) {
            sf_close(file->snd_file);
        }
        return 0;
    }
    return 1;
}

static int file_ok(SF_INFO* file_info, SNDFILE* file)
{
    if (file == NULL) {
        printf("Could not load the file\n");
        printf("%s\n", sf_strerror(NULL));
        return 0;
    }
    if (sf_error(file) != SF_ERR_NO_ERROR) {
        printf("Could not load the file\n");
        printf("%s\n", sf_strerror(file));
        return 0;
    }
    if (file_info->channels != 2) {
        printf("The file should have 2 channels. 1 for voltage and 1 for current.\n");
        return 0;
    }

    return 1;
}

int read_uk_dale_to_ring_buffer(UkDaleFile* file, Calibration* calib, float* voltage, float* current, int buffer_length, int bytes_read, int offset)
{
    float buffer[DATA_LOADER_FILE_BUFFER_LEN];

    int read_frames = DATA_LOADER_FILE_BUFFER_LEN / 2 > bytes_read ? bytes_read : DATA_LOADER_FILE_BUFFER_LEN / 2;

    int total_count = 0;
    float voltage_multiplyer = calib->volts_per_adc_step * calib->number_of_adc_steps;
    float amp_multiplyer = calib->amps_per_adc_step * calib->number_of_adc_steps;


    do {
        if (read_frames > bytes_read - total_count) {
            read_frames = bytes_read - total_count;
        }
        sf_count_t count = sf_readf_float(file->snd_file, buffer, read_frames);
        if (count != read_frames) {
            return -1;
        }

        int buffer_count = 0;

        for (; buffer_count < read_frames * 2; ++buffer_count) {
            voltage[(total_count + offset) % buffer_length] = buffer[buffer_count] * voltage_multiplyer;
            ++buffer_count;
            current[(total_count + offset) % buffer_length] = buffer[buffer_count] * amp_multiplyer;

            ++total_count;

            if (total_count >= bytes_read) {
                return (total_count + offset) % buffer_length;
            }
        }
    } while (1);
}



int close_uk_dale_file(UkDaleFile* file)
{
    sf_close(file->snd_file);
    return 1;
}






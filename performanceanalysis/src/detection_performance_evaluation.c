#include "file_config_loader.h"
#include "file_loader.h"
#include "smart_meter_channels.h"

#include "performance_analysis_config.h"

#include "analyze.h"

#include <time.h>

static int do_measurements(Calibration* calib, UkDaleFile* file,ChannelProgress* progress );

int analyze_algorithm_performance(const char *path_to_sound_file, const char *path_to_calibration_file, const char *path_to_channel_folder)
{
    Calibration calib;
    if (!parse_calibration(path_to_calibration_file, &calib)) {
        printf("Could not parse calibration file");
        return -1;
    }
    UkDaleFile file;
    if (!open_uk_dale_file(path_to_sound_file, &file)) {
        printf("Could not open sound file.");
        return -2;
    }

    ChannelProgress progress;
    if(!init_channel_progress(path_to_channel_folder, &progress)) {
        printf("Failed to initialize the channel progress.");
        close_uk_dale_file(&file);
        return -3;
    }

    int success = do_measurements(&calib, &file, &progress);

    close_channel_progress(&progress);
    close_uk_dale_file(&file);

    return success;


}


static int do_measurements(Calibration* calib, UkDaleFile* file,ChannelProgress* progress ) {
    float amps[PERFORMANCE_ANALYSIS_DATA_BUFFER_LEN];
    float volts[PERFORMANCE_ANALYSIS_DATA_BUFFER_LEN];

    printf("Evaluating %d values each second:\n\n", PERFORMANCE_ANALYSIS_DATA_BUFFER_LEN);


    clock_t start_time = clock();
    clock_t time_taken = 0;

    int counter = 0;

    int t0 = 1363392000;
    int offset = 0;
    for(; counter < 60; ++counter) {

        fetch_states_after_time(progress, t0);
        print_channel_changes(progress);
        adopt_channel_changes(progress);
        ++t0;

        fflush(stdout);
        offset = read_uk_dale_to_ring_buffer(file, calib,volts,amps,PERFORMANCE_ANALYSIS_DATA_BUFFER_LEN, PERFORMANCE_ANALYSIS_DATA_BUFFER_LEN / 2, offset);
        if(offset == -1) {
            printf("Can not read any more data from the sound file.");
        }
        start_time = clock();
        time_taken += clock() - start_time;
    }


    printf("total clocks since start of event evaluation: %li\n", time_taken);
    return 1;


}

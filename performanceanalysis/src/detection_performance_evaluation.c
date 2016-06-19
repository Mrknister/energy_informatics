
#include <time.h>

#include "file_config_loader.h"
#include "file_loader.h"
#include "smart_meter_channels.h"

#include "performance_analysis_config.h"

#include "analyze.h"

#include "save_data.h"

static int do_measurements(Calibration* calib, UkDaleFile* file, ChannelProgress* progress);

int analyze_algorithm_performance(const char* path_to_sound_file, const char* path_to_calibration_file, const char* path_to_channel_folder)
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
    if (!init_channel_progress(path_to_channel_folder, &progress)) {
        printf("Failed to initialize the channel progress.");
        close_uk_dale_file(&file);
        return -3;
    }

    int success = do_measurements(&calib, &file, &progress);

    close_channel_progress(&progress);
    close_uk_dale_file(&file);

    return success;
}
void print_buffer(float* buffer, const char* intersect, int num_vals)
{
    int counter = 0;
    for (; counter < num_vals - 1; ++counter) {
        printf("%f%s", buffer[counter], intersect);
    }
    printf("%f", buffer[counter]);
}

static int do_measurements(Calibration* calib, UkDaleFile* file, ChannelProgress* progress)
{
    float amps[PERFORMANCE_ANALYSIS_DATA_BUFFER_LEN];
    float volts[PERFORMANCE_ANALYSIS_DATA_BUFFER_LEN];

    printf("Evaluating %d values each second:\n\n", PERFORMANCE_ANALYSIS_DATA_BUFFER_LEN / 2);


    clock_t start_time = clock();
    clock_t time_taken = 0;

    int counter = 0;

    int t0 = 1363392000;
    int next_offset = 0;
    int offset = 0;
    int event = -1;
    for (; counter < 6000; ++counter) {

        fetch_states_after_time(progress, t0);
        //print_channel_changes(progress);
        adopt_channel_changes(progress);
        ++t0;

        fflush(stdout);
        
        next_offset = read_uk_dale_to_ring_buffer(file, calib, volts, amps, PERFORMANCE_ANALYSIS_DATA_BUFFER_LEN, PERFORMANCE_ANALYSIS_DATA_BUFFER_LEN / 2, next_offset);
        if (next_offset == -1) {
            printf("Can not read any more data from the sound file. After %i ticks\n", counter);
            return -1;
        }
        // we check if the event happened here because we want to buffer the next data to make sure that there is enough data in the buffer
        if(event >=0 ) {
            printf("Event at tick %i\n", counter);
            log_event("", t0, amps, PERFORMANCE_ANALYSIS_DATA_BUFFER_LEN, DATA_POINTS_PER_FEATURE, event - DATA_POINTS_PER_WAVE_LENGTH);
            FastFourierFeature feature;
            fast_fourier_transform(&feature,volts, amps, PERFORMANCE_ANALYSIS_DATA_BUFFER_LEN, event);
        }
        
        start_time = clock();
        event = analyze(volts, amps, PERFORMANCE_ANALYSIS_DATA_BUFFER_LEN, PERFORMANCE_ANALYSIS_DATA_BUFFER_LEN / 2, offset);
        time_taken += clock() - start_time;
        offset = next_offset;
    }

    printf("total clocks since start of event evaluation: %li\n", time_taken);
    return 1;
}





#include <time.h>
#include <stdint.h>
#include "timing.h"

#include "file_config_loader.h"
#include "file_loader.h"
#include "smart_meter_channels.h"

#include "performance_analysis_config.h"

#include "analyze.h"

#include "save_data.h"

static int do_measurements(Calibration* calib, UkDaleFile* file, ChannelProgress* progress);

static clock_t time_elapsed, start_time;


float amps[PERFORMANCE_ANALYSIS_DATA_BUFFER_LEN];
float volts[PERFORMANCE_ANALYSIS_DATA_BUFFER_LEN];
int buffer_offset = 0;



static void reset_timer();
static void pause_timer();
static void resume_timer();
static int do_event_evaluation(int event, int event_time);
static int evaluate_once(int* second_time_stamp, UkDaleFile* file, Calibration* calib);



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

/**
 * @brief Evaluates one hour of power data. It sums the time used to do the calculations without loading the sound file.
 *
 *
 */
static int do_measurements(Calibration* calib, UkDaleFile* file, ChannelProgress* progress)
{
    printf("Evaluating %d values each second:\n\n", PERFORMANCE_ANALYSIS_DATA_BUFFER_LEN / 2);


    int counter = 0;
    int t0 = 1363392000;
    int t = t0;

    reset_timer();

    for (; evaluate_once(&t, file, calib) != -1; ++counter) {
        fflush(stdout);
    }

    printf("total clocks since start of event evaluation: %li. In total we need %li clocks to evaluate a second\n", time_elapsed, time_elapsed / (t - t0));
    return 1;
}

/**
 * @brief Detects events within one second at most.
 *
 * We dont specify how much time we need exactly because when an event is detected we buffer another half a second to make sure that there is enough data to analyze an event.
 * When one second passes we will increase the time stamp variable.
 */
static int evaluate_once(int* second_time_stamp, UkDaleFile* file, Calibration* calib)
{
    static int time_offset_counter = 0;


    const int read_data = PERFORMANCE_ANALYSIS_DATA_BUFFER_LEN / 4;
    int next_offset =  read_uk_dale_to_ring_buffer(file, calib, volts, amps, PERFORMANCE_ANALYSIS_DATA_BUFFER_LEN, read_data, buffer_offset);
    if (next_offset == -1) {
        return -1;
    }

    time_offset_counter += next_offset;

    // If we passed a second, increase the time stamp
    if (time_offset_counter > DATA_POINTS_PER_SECOND) {
        time_offset_counter -= DATA_POINTS_PER_SECOND;
        ++(*second_time_stamp);
    }



    resume_timer();
    int event = detect_event(volts, amps, PERFORMANCE_ANALYSIS_DATA_BUFFER_LEN, read_data, buffer_offset);
    pause_timer();


    //An event was detected. Now we will analyze features on this event and also log some data.
    if (event != -1) {

        buffer_offset = read_uk_dale_to_ring_buffer(file, calib, volts, amps, PERFORMANCE_ANALYSIS_DATA_BUFFER_LEN, read_data, next_offset);
        time_offset_counter += buffer_offset;

        if (buffer_offset == -1) {
            return -1;
        }
        return do_event_evaluation(event, *second_time_stamp);
    }
    return 1;
}

static int do_event_evaluation(int event, int event_time)
{
    printf("Event at second %i\n", event_time);

    // Start analyzing features.
    resume_timer();
    FastFourierFeature fft_feature;
    fast_fourier_transform(&fft_feature, amps, PERFORMANCE_ANALYSIS_DATA_BUFFER_LEN, event);
    RootMeanSquareFeature rms_feature;
    root_mean_square_feature(&rms_feature, volts, amps, PERFORMANCE_ANALYSIS_DATA_BUFFER_LEN, event);
    pause_timer();


    // Log data related to the features.
    const int data_points_logged =  DATA_POINTS_PER_FEATURE + DATA_POINTS_PER_WAVE_LENGTH;
    const int log_start = event - DATA_POINTS_PER_WAVE_LENGTH;

    log_event("", event_time, amps, PERFORMANCE_ANALYSIS_DATA_BUFFER_LEN, data_points_logged, log_start);

    log_rms_feature("", event_time, &rms_feature);
    log_fft_feature("", event_time, &fft_feature);

    return 0;
}



//  Windows
#ifdef _WIN32

#include <intrin.h>
uint64_t rdtsc()
{
    return __rdtsc();
}

#endif

static void reset_timer()
{
    time_elapsed = 0;
    start_time = cpucycles();
}

static void pause_timer()
{
    time_elapsed += cpucycles() - start_time;
}

void resume_timer()
{
    start_time = cpucycles();
}



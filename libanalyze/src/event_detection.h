/** @file */

#ifndef _EVENT_DETECTION_H_
#define _EVENT_DETECTION_H_



#if defined(__cplusplus)
extern "C" {
#endif

#include "libanalyze_config.h"
#include "root_mean_square_feature.h"


float establish_current_amplitude(float* buffer, int buffer_size, int offset)
{
    float max = -123456678.0;
    int counter = 0;
    for (; counter < DATA_POINTS_PER_WAVE_LENGTH; ++counter) {
        if (buffer[(counter + offset) % buffer_size] > max) {
            max = buffer[(counter + offset) % buffer_size];
        }
    }

    return max;
}

int analyze(float* voltage, float* current, int buffer_size, int bytes_to_analyze, int offset)
{
    static float prev_rms = -1234523456345;

    int counter = 0;

    if (prev_rms == -1234523456345) {
        prev_rms = root_mean_square(voltage, current, buffer_size, counter + offset);
    }

    for (; counter < bytes_to_analyze - DATA_POINTS_PER_WAVE_LENGTH; counter += DATA_POINTS_PER_WAVE_LENGTH) {

        float current_rms = root_mean_square(voltage, current, buffer_size, counter + offset);

        if (prev_rms < current_rms - CURRENT_DIFFERENCE_EVENT_TRIGGER) {
            printf("old rms: %f current rms: %f, buffer_pos: %i\n", prev_rms,current_rms, (counter + offset) % buffer_size);
            prev_rms = current_rms ;
            return (counter + offset) % buffer_size;
        }

        prev_rms = current_rms * 0.1 + prev_rms * 0.9;
    }

    return -1;
}



#if defined(__cplusplus)
} /* extern "C" */
#endif


#endif // ANALYZE_H

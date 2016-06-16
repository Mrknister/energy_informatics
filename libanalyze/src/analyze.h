/** @file */

#ifndef ANALYZE_H
#define ANALYZE_H



#if defined(__cplusplus)
extern "C" {
#endif

#include "libanalyze_config.h"
#include "mean_square_root_feature.h"



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
    static float prev_max = -1234523456345;

    int counter = 0;

    if (prev_max == -1234523456345) {
        prev_max = establish_current_amplitude(current, buffer_size, offset);
    }

    for (; counter < bytes_to_analyze - DATA_POINTS_PER_WAVE_LENGTH; counter += DATA_POINTS_PER_WAVE_LENGTH) {

        float current_amplitude = establish_current_amplitude(current, buffer_size, counter + offset);

        if (prev_max < current_amplitude - CURRENT_DIFFERENCE_EVENT_TRIGGER) {
            return counter + offset % buffer_size;
        }
        prev_max = current_amplitude;
    }

    return -1;
}



#if defined(__cplusplus)
} /* extern "C" */
#endif


#endif // ANALYZE_H

#ifndef _FEATURES_H_
#define _FEATURES_H_

#include "libanalyze_config.h"
#include <math.h>

#if defined(__cplusplus)
extern "C" {
#endif


typedef struct {
    float data[ANALYZED_FEATURES_PER_WAVE];
} MeanSquareRootFeature;


int mean_square_root(MeanSquareRootFeature* feature, float voltage[], float current[], int buffer_size, int offset)
{

    int msq_counter = 0;
    for (; msq_counter < ANALYZED_FEATURES_PER_WAVE; msq_counter++) {
        feature->data[msq_counter] = 0;
    }


    msq_counter = 0;

    int bytes_counter = 0;
    while (bytes_counter < DATA_POINTS_PER_FEATURE) {

        feature->data[msq_counter] += current[(bytes_counter + offset) % buffer_size] * current[(bytes_counter + offset) % buffer_size];
        bytes_counter++;

        if (bytes_counter % DATA_POINTS_PER_WAVE_LENGTH == 0) {
            feature->data[msq_counter] = sqrt(feature->data[msq_counter] / DATA_POINTS_PER_WAVE_LENGTH);
            ++msq_counter;
            if (msq_counter >= ANALYZED_FEATURES_PER_WAVE) {
                return 0 ;
            }
        }
    }
    return 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#endif


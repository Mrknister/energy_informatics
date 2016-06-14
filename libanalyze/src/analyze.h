/** @file */

#ifndef ANALYZE_H
#define ANALYZE_H


#if defined(__cplusplus)
extern "C" {
#endif

#include "libanalyze_config.h"

int naive_event_processing(float* voltage, float* current, int num_data_points) {
    int counter = 0;
    static float sum = 0;

    float current_sum = 0;


    for(; counter < num_data_points; ++counter) {
        current_sum  += voltage[counter] * current[counter];

    }

    printf("old watt: %f  current watt: %f\n", sum / num_data_points, current_sum / num_data_points);

    sum = current_sum;

    return 1;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif


#endif // ANALYZE_H

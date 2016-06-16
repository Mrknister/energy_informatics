/** @file */

#ifndef ANALYZE_H
#define ANALYZE_H



#if defined(__cplusplus)
extern "C" {
#endif

#include "libanalyze_config.h"
#include "mean_square_root_feature.h"

int analyze(float* voltage, float* current, int buffer_size, int bytes_to_analyze, int offset) {
    static int prev_event = -1;
    static int prev_max = 0;

    int counter = 0;

    if(prev_event != -1) {
        // analyze event which needed some more buffering
    }
    int time_since_prev_max;
    for(; counter < bytes_to_analyze; ++counter) {
        if(prev_max < current[(counter+offset) % buffer_size]) {
            int diff =  current[(counter+offset) % buffer_size] - prev_max;
            if(diff > CURRENT_DIFFERENCE_EVENT_TRIGGER ) {
                // trigger event
            }
        }
        ++time_since_prev_max;
    }
    return 0;
}



#if defined(__cplusplus)
} /* extern "C" */
#endif


#endif // ANALYZE_H

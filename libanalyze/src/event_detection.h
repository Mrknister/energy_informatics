/** @file */

#ifndef _EVENT_DETECTION_H_
#define _EVENT_DETECTION_H_



#if defined(__cplusplus)
extern "C" {
#endif

#include "libanalyze_config.h"
#include "root_mean_square_feature.h"


float establish_current_amplitude(float* buffer, int buffer_size, int offset);

int analyze(float* voltage, float* current, int buffer_size, int bytes_to_analyze, int offset);



#if defined(__cplusplus)
} /* extern "C" */
#endif


#endif // ANALYZE_H

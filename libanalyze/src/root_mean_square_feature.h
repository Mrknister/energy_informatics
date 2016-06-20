#ifndef _FEATURES_H_
#define _FEATURES_H_

#include "libanalyze_config.h"

#if defined(__cplusplus)
extern "C" {
#endif


typedef struct {
    float data[ANALYZED_FEATURES_PER_WAVE];
} RootMeanSquareFeature;

float root_mean_square(float voltage[], float current[], int buffer_size, int offset);

int root_mean_square_feature(RootMeanSquareFeature* feature, float voltage[], float current[], int buffer_size, int offset);

#if defined(__cplusplus)
} /* extern "C" */
#endif

#endif


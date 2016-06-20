#ifndef _FFT_FEATURE_H_
#define _FFT_FEATURE_H_

#if defined(__cplusplus)
extern "C" {
#endif

#include <kiss_fft.h>
#include "libanalyze_config.h"

typedef struct {
    kiss_fft_cpx data[DATA_POINTS_PER_FEATURE];
} FastFourierFeature;

int fast_fourier_transform(FastFourierFeature* feature,  float voltage[], float current[], int buffer_size, int offset);


#if defined(__cplusplus)
} /* extern "C" */
#endif

#endif

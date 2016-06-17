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

int fast_fourier_transform(FastFourierFeature* feature,  float voltage[], float current[], int buffer_size, int offset)
{
    kiss_fft_cpx buffer[DATA_POINTS_PER_FEATURE];
    size_t lenmem = 1024 + sizeof(FastFourierFeature);
    char cfg_buffer[lenmem];
    kiss_fft_cfg cfg =  kiss_fft_alloc(DATA_POINTS_PER_FEATURE,0,(void *) cfg_buffer,&lenmem); 

    
    
    
    int counter = 0;
    for (; counter < DATA_POINTS_PER_FEATURE; ++counter) {
        buffer[counter].i = 0;
        buffer[counter].r = current[(counter + offset) % buffer_size];
    }
    
    kiss_fft(cfg, buffer, feature->data);
    
    return 1;
}


#if defined(__cplusplus)
    } /* extern "C" */
#endif

#endif

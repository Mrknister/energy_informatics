#ifndef _CONFIG_LOADER_H_
#define _CONFIG_LOADER_H_

#if defined(__cplusplus)
extern "C" {
#endif

#include <stdio.h>

typedef struct {
    float volts_per_adc_step;
    float phase_difference;
    float amps_per_adc_step;
} Calibration;


typedef struct {
    FILE* channel_file;
} MeterReadingsChannel;

typedef struct {
    int time_stamp;
    int state;
} ChannelState;

int parse_calibration(const char* filepath, Calibration* calib);

int open_meter_readings_channel(const char* filepath, MeterReadingsChannel* channel);

int fetch_next_channel_state(MeterReadingsChannel* channel, ChannelState* state);

int close_meter_readings_channel(MeterReadingsChannel* channel);

#if defined(__cplusplus)
} /* extern "C" */
#endif

#endif

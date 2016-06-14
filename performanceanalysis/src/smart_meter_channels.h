/** @file */


#ifndef SMART_METER_CHANNELS_H
#define SMART_METER_CHANNELS_H
#if defined(__cplusplus)
extern "C" {
#endif
#include <stdio.h>

/**
  *@brief This struct is used to access a power meter channel. A power meter channel gives us information whether a specific device is turned on or not.
  */
typedef struct {
    FILE* channel_file;
    char* path;
} MeterReadingsChannel;


/**
  *@brief This struct can be directly accessed to retrieve information about the state in which a specific device is right now.
  */
typedef struct {

    int time_stamp; /**< A unix time stamp. The seconds are really the only interesting part. */
    int state; /**< The state is 1 if the device is on, 0 otherwise. */
} ChannelState;

typedef struct {
    MeterReadingsChannel* channels;
    ChannelState* channel_states;
    ChannelState* old_channel_states;
    int num_channels;
} ChannelProgress;

/**
 * @brief open_meter_readings_channel opens one of the files that specify the readings of the power meters, which tell us, whether a device is actually on or off.
 * @param filepath The path to the file.
 * @param channel The structure which will be initialised.
 * @returns 1 on success, 0 on failure.
 */
int open_meter_readings_channel(const char* filepath, MeterReadingsChannel* channel);

/**
 * @brief fetch_next_channel_state reads one channel state from the channel.
 * @param channel The channel from which the information will be retrieved.
 * @param state The ChannelState struct in which the state will be stored.
 * @returns 1 on success, 0 on failure.
 */
int fetch_next_channel_state(MeterReadingsChannel* channel, ChannelState* state);

/**
 * @brief close_meter_readings_channel closes the channel.
 * @param channel
 * @return 1 on success, 0 on failure.
 */
int close_meter_readings_channel(MeterReadingsChannel* channel);

/**
 * @brief open_all_channels_in_folder looks for all files in a folder and tries to open a channel for them.
 * @param path
 * @param channels a pointer to a pointer in which the allocated array will be stored.
 * @return
 */
int open_all_channels_in_folder(const char *path, MeterReadingsChannel** channels);

int init_channel_progress(const char* path, ChannelProgress* to_initialize);

int fetch_states_after_time(ChannelProgress* progress, int time_stamp);

int close_channel_progress(ChannelProgress* progress);

void print_channel_changes(ChannelProgress* progress);

void adopt_channel_changes(ChannelProgress* progress);


#if defined(__cplusplus)
} /* extern "C" */
#endif

#endif // SMART_METER_CHANNELS_H

#include "smart_meter_channels.h"
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

long count_files_in_directory(const char* path);
int is_meter_channel_file(struct dirent* file_ent);

int open_meter_readings_channel(const char* filepath, MeterReadingsChannel* channel)
{
    FILE* f = fopen(filepath, "r");
    if (f == NULL) {
        perror("Error");
        return 0;
    }
    channel->channel_file = f;

    return 1;
}


int fetch_next_channel_state(MeterReadingsChannel* channel, ChannelState* state)
{
    int result = fscanf(channel->channel_file, "%d %d\n", &state->time_stamp, &state->state);
    if (result != 2) {
        return 0;
    }
    return 1;
}

int close_meter_readings_channel(MeterReadingsChannel* channel)
{
    fclose(channel->channel_file);
    free(channel->path);
    return 1;
}

long count_files_in_directory(const char* path)
{
    DIR* dir;

    struct dirent* ent;
    if ((dir = opendir(path)) == NULL) {
        return -1;

    }

    long counter = 1;

    while ((ent = readdir(dir)) != NULL) {
        if (is_meter_channel_file(ent)) {
            ++counter;
        }
    }
    closedir(dir);
    return counter;
}

int open_all_channels_in_folder(const char* path, MeterReadingsChannel** channels)
{
    long num_files = count_files_in_directory(path);
    if (num_files <= 0) {
        return -1;
    }
    *channels = malloc(sizeof(MeterReadingsChannel) * (num_files));
    channels[num_files] = NULL;

    DIR* dir;

    struct dirent* ent;
    if ((dir = opendir(path)) == NULL) {
        return -1;
    }

    int counter = 0;
    int path_length = strlen(path);

    while ((ent = readdir(dir)) != NULL && counter < num_files) {
        if (is_meter_channel_file(ent)) {
            int name_length = strlen(ent->d_name) ;

            char* full_path = malloc(name_length + path_length + 1);
            strncpy(full_path, path,  path_length);
            strncpy(full_path + path_length, ent->d_name, name_length + 1);
            if (!open_meter_readings_channel(full_path, &channels[0][counter])) {
                printf("%s dows not seem to be a valid channel. Ignoring it for now.\n", ent->d_name);
                free(full_path);
                continue;
            }
            channels[0][counter].path = full_path;


            counter++;
        }
    }
    closedir(dir);
    return counter;
}

int is_meter_channel_file(struct dirent* file_ent)
{
    int channel_number = 0;
    char c;
    int scanned = sscanf(file_ent->d_name, "channel_%d.da%[t]", &channel_number, &c);
    return file_ent->d_type == DT_REG && scanned == 2;
}

int init_channel_progress(const char* path, ChannelProgress* to_initialize)
{
    int num_channels = open_all_channels_in_folder(path, &to_initialize->channels);
    if (num_channels <= 0) {
        return 0;
    }
    to_initialize->num_channels = num_channels;
    to_initialize->channel_states = malloc(sizeof(ChannelState) * num_channels);
    to_initialize->old_channel_states = malloc(sizeof(ChannelState) * num_channels);

    memset(to_initialize->channel_states, 0, sizeof(ChannelState) * num_channels);
    memset(to_initialize->old_channel_states, 0, sizeof(ChannelState) * num_channels);

    return 1;
}

int fetch_states_after_time(ChannelProgress* progress, int time_stamp)
{
    int counter = 0;
    int success = progress->num_channels;
    for (; counter < progress->num_channels; ++counter) {

        while (progress->channel_states[counter].time_stamp < time_stamp) {
            if (!fetch_next_channel_state(&progress->channels[counter], &progress->channel_states[counter])) {
                success--;
            }
        }
    }
    return success;
}

int close_channel_progress(ChannelProgress* progress)
{
    int counter = 0;
    for (; counter < progress->num_channels; ++counter) {
        close_meter_readings_channel(&progress->channels[counter]);
    }
    free(progress->channels);
    free(progress->channel_states);
    free(progress->old_channel_states);

    return 1;
}

void print_channel_changes(ChannelProgress* progress)
{
    int counter = 0;
    for (; counter < progress->num_channels; ++counter) {
        if (progress->old_channel_states[counter].state != progress->channel_states[counter].state) {
            printf("%s: State changed at %i from %i to %i\n",
                   progress->channels[counter].path,
                   progress->channel_states[counter].time_stamp,
                   progress->old_channel_states[counter].state,
                   progress->channel_states[counter].state);

        }
    }
    fflush(stdout);

}

void adopt_channel_changes(ChannelProgress* progress)
{
    memcpy(progress->old_channel_states, progress->channel_states, sizeof(ChannelState) * progress->num_channels);
}

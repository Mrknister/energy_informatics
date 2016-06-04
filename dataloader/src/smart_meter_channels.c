#include "smart_meter_channels.h"
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

long count_files_in_directory(const char *path);
int is_meter_channel_file(struct dirent *file_ent);

int open_meter_readings_channel(const char* filepath, MeterReadingsChannel* channel)
{
    FILE* f = fopen(filepath, "r");
    if ( f == NULL ) {
        return 0;
    }
    channel->channel_file = f;

    return 1;
}


int fetch_next_channel_state(MeterReadingsChannel* channel, ChannelState* state)
{
    int result = fscanf(channel->channel_file, "%d %d\n", &state->time_stamp, &state->state);
    if ( result != 2 ) {
        return 0;
    }
    return 1;
}

long count_files_in_directory(const char *path) {
    DIR *dir;

    struct dirent *ent;
    if ((dir = opendir (path)) == NULL) {
        return -1;

    }

    long counter = 1;

    while ((ent = readdir (dir)) != NULL) {
        if (is_meter_channel_file (ent)) {
            ++counter;
        }
    }
    closedir (dir);
    return counter;
}

int open_all_channels_in_folder(const char *path, MeterReadingsChannel** channels)
{
    long num_files = count_files_in_directory(path);
    if( num_files <= 0) {
        return -1;
    }
    *channels = malloc(sizeof(MeterReadingsChannel) * (num_files) );
    channels[num_files] = NULL;

    DIR *dir;

    struct dirent *ent;
    if ((dir = opendir (path)) == NULL) {
        return -1;
    }

    int counter = 0;

    while ((ent = readdir (dir)) != NULL && counter < num_files) {
        if (is_meter_channel_file (ent)) {
            if(!open_meter_readings_channel(ent->d_name, &channels[0][counter])) {
                printf("%s dows not seem to be a valid channel. Ignoring it for now.", ent->d_name);
                continue;
            }
            int length = strlen(ent->d_name) + 1;
            channels[0][counter].path = malloc(length);
            strncpy(channels[0][counter].path,ent->d_name,  length);
            counter++;
        }
    }
    closedir (dir);
    return num_files;
}

int is_meter_channel_file(struct dirent* file_ent) {
    return file_ent->d_type == DT_REG && strncmp(file_ent->d_name, "channel", strlen("channel")) == 0;
}

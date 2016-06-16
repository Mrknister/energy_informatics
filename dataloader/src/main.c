#include <stdio.h>


#include "file_loader.h"
#include "file_config_loader.h"
#include "smart_meter_channels.h"

void test_channels() {
    const char* path = "/media/users/Shared/Seminar/uk-power-data-zip-download/house_1/";
    MeterReadingsChannel* channels = 0;
    int num_channels = open_all_channels_in_folder(path, &channels);
    int counter = 0;

    for(; counter < num_channels; ++counter) {
        ChannelState state;
        if(!fetch_next_channel_state(&channels[counter], &state)) {
            printf("Could not read file. %s\n", channels[counter].path);
            return;
        }
        printf("%s: %i %i\n",channels[counter].path,  state.time_stamp, state.state);
    }

}


int main(int argc, char** argv)
{
    printf("%i", -1 % 50);
    return 0;
    test_channels();
    return 0;
    if (argc < 3) {
        return -1;
    }
    Calibration calib;
    if (!parse_calibration(argv[1], &calib)) {
        printf("Could not parse calibration file");
        return -1;
    }
    UkDaleFile file;
    if (!open_uk_dale_file(argv[2], &file)) {
        return -1;
    }

    float volts [4096];
    float amps [4096];

    while (read_uk_dale(&file, &calib, volts, amps, 4096)) {
        int counter = 0;
        for (; counter < 4096; ++counter) {
            printf("volts: %f  amps: %f\n", volts[counter], amps[counter]);
            
        }
    }

    return 0;
}

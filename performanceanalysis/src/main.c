#include <stdio.h>


#include "detection_performance_evaluation.h"

void print_usage()
{
    printf("usage: performanceanalysis <path_to_sound_file> <path_to_calibration> <path_to_channel_folder>\n");
}


int main(int argc, char** argv)
{

    if (argc < 4) {
        print_usage();
        return -1;
    }
    analyze_algorithm_performance(argv[1], argv[2], argv[3]);


    return 0;
}

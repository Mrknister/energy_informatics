#ifndef DETECTION_PERFORMANCE_EVALUATION_H
#define DETECTION_PERFORMANCE_EVALUATION_H
#if defined(__cplusplus)
extern "C" {
#endif

int analyze_algorithm_performance(const char* path_to_sound_file, const char* path_to_calibration_file, const char* path_to_channel_folder);

#if defined(__cplusplus)
} /* extern "C" */
#endif

#endif // DETECTION_PERFORMANCE_EVALUATION_H

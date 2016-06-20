#ifndef _SAVE_DATA_H_
#define _SAVE_DATA_H_


#if defined(__cplusplus)
//extern "C" {
#endif
#include "analyze.h"

int save_float_array(const char* file_name, float* buffer, int buffer_size, int num_data, int offset);

int log_event(const char* log_folder, int event_time, float* buffer, int buffer_size, int num_data, int event_pos);


#if defined(__cplusplus)
//} /* extern "C" */
#endif

#endif

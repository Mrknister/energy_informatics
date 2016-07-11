/** @file */

#ifndef _FILELOADER_H_
#define _FILELOADER_H_

#if defined(__cplusplus)
extern "C" {
#endif

#include <sndfile.h>
#include "file_config_loader.h"



/**
  * @brief Stores data to work with the UK-Dale data set. The content of this struct should not be accessed directly by a user.
  *
  *
  **/
typedef struct {
    SNDFILE* snd_file;
    long int start_time;
} UkDaleFile;


/**
 * @brief open_uk_dale_file opens the specified audio file and prints an error to the console if the file can't be loaded.
 * @param fname The path to the file that should be opened.
 * @param file A pointer to a UkDaleFile which will be used in subsequend calls to read_uk_dale.
 * @returns 1 on success, 0 on failure.
 */
int open_uk_dale_file(const char* fname, UkDaleFile* file);

/**
 * @brief read_uk_dale reads a data points from the audio file and stores them within the specified buffers.
 * @param file A file which has been already opened with open_uk_dale_file
 * @param calib A calibration for the recorded data set. This should be within the house folder.
 * @param voltage A buffer which can hold at least buffer_length floats. The voltages will be stored here.
 * @param current See voltage parameter
 * @param buffer_length The number of values the buffer can hold.
 * @param bytes_read The number of values that will be read from the buffer.
 * @returns the new offset on success, -1 on failure.
 */
int read_uk_dale_to_ring_buffer(UkDaleFile* file, Calibration* calib, float* voltage, float* current, int buffer_length, int bytes_read, int offset);

/**
 * @brief close_uk_dale_file closes the file.
 * @param file
 * @return 1 on success, 0 on failure. Not that you can do anything about it if it fails.
 */
int close_uk_dale_file(UkDaleFile* file);


#if defined(__cplusplus)
} /* extern "C" */
#endif

#endif

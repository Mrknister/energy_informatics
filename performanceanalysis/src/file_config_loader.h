/** @file */

#ifndef _CONFIG_LOADER_H_
#define _CONFIG_LOADER_H_

#if defined(__cplusplus)
extern "C" {
#endif


/**
  *@brief This struct holds the calibration which should be located within the house* folders.
  */
typedef struct {
    double volts_per_adc_step;
    double phase_difference;
    double amps_per_adc_step;
    double number_of_adc_steps;
} Calibration;

/**
 * @brief parse_calibration parses the calibration located within the house* folders.
 * @param filepath The path to the calibration.
 * @param calib This structure will be filled with values on success.
 * @returns 1 on success, 0 on failure.
 *
 * @note The number of adc steps is not  specified within the calibration file. In the docs of the data set, one can see that for the houses 1 and 2 the value is 2^31. Thus this value will be used. For house 5 it is 2^15. I f you want to load data from house 5, please change this value later within your soure code to the right one.
 */
int parse_calibration(const char* filepath, Calibration* calib);


#if defined(__cplusplus)
} /* extern "C" */
#endif

#endif

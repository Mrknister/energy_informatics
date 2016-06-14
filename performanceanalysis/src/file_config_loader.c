#include "ini.h"
#include "file_config_loader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ctype.h>
#include <math.h>


static int handler(void* user, const char* section, const char* name,
                   const char* value)
{
    Calibration* calib = (Calibration*) user;
    printf("Parsing value '%s' '%s'\n", name, value);
    if (strcmp(name, "volts_per_adc_step") == 0) {
        calib->volts_per_adc_step =  atof(value);
    } else if (strcmp(name, "phase_difference") == 0) {
        calib->phase_difference =  atof(value);
    } else if (strcmp(name, "amps_per_adc_step") == 0) {
        calib->amps_per_adc_step =  atof(value);
    } else {
        return 0;  /* unknown section/name, error */
    }
    return 1;
}

int parse_calibration(const char* filepath, Calibration* calib)
{

    if (ini_parse(filepath, handler, calib) < 0) {
        printf("Can't load '%s'\n", filepath);
        return 0;
    }
    calib->number_of_adc_steps = 0x80000000;
    printf("Config loaded from %s: amps_per_adc_step=%.10e, phase_difference=%.10e, volts_per_adc_step=%.10e\n",
           filepath, calib->amps_per_adc_step, calib->phase_difference, calib->volts_per_adc_step);
    return 1;
}





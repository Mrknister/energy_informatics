#include <stdio.h>


#include "file_loader.h"
#include "file_config_loader.h"





int main ( int argc, char **argv )
{
    if ( argc<2 ) {
        return -1;
    }
    Calibration calib;
    parse_calibration ( argv[1], &calib );
    return 0;
}

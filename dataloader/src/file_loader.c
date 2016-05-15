#include "file_loader.h"
#include "data_loader_config.h"

#include <sndfile.h>




char file_ok ( SF_INFO* file_info, SNDFILE * file );

void read_file ( const char * fname )
{
    static short buffer [DATA_LOADER_FILE_BUFFER_LEN] ;

    SF_INFO file_info;
    SNDFILE * file;

    file = sf_open ( fname,SFM_READ,&file_info );
    if ( file_ok ( &file_info, file ) ) {
        printf ( "file is perfectly fine\n" );
    }

    sf_close ( file );
}

char file_ok ( SF_INFO* file_info, SNDFILE * file )
{
    if ( file == 0 ) {
        printf ( "Could not load the file\n" );
        printf ( "%s\n",sf_strerror ( NULL ) );
        return 0;
    }
    if ( sf_error ( file ) != SF_ERR_NO_ERROR ) {
        printf ( "Could not load the file\n" );
        printf ( "%s\n",sf_strerror ( file ) );
        return 0;
    }
    if ( file_info->channels != 2 ) {
        printf ( "The file should have 2 channels. 1 for voltage and 1 for current.\n" );
        return 0;
    }

    return 1;
}

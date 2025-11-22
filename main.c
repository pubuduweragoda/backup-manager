#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <inttypes.h>
#include <sys/types.h>
#include "luks.h"
#include "disk_manage.h"

int main(int argc, char **argv){

    const char *LUKS_VOL;
    const char *KEY_FILE;
    const char *MNT_POINT;
    const char *FILES;

    // Accept user arguments for 
    // -> luks vol location | key file | files to backup
    int opt;
    while (true){
        opt = getopt(argc, argv, "klf");
        if ( argc > 1 && opt == -1){
            break;
        }

        switch(opt){
            case 'k':
                KEY_FILE = argv[optind];
                break;
            case 'f':
                FILES = argv[optind];
                break;
            case 'l':
                LUKS_VOL = argv[optind];
                break;
            default: /* '?' */
                printf("Usage: [-l LUKS_VOLUME] [-k KEYFILE] [-f FILE_TO_BACKUP] \n" );
                exit(EXIT_FAILURE);
        }
    }


    
    return 0;
}

#include <libcryptsetup.h>
#include <stdio.h>
#include "luks.h"

int open_luks_vol(const char *PATH, const char *KEY_PATH){
    struct crypt_device *cd;

    if (crypt_init(&cd, PATH) < 0){
        perror("Warning: crypt_init() failed\n");
        return 1;
    }
    printf("Initialized crypt volume\n");

    if(crypt_load(cd, CRYPT_LUKS, NULL) < 0){
        perror("Warning: failed to load the header from LUKS volume\n");
        crypt_free(cd);
        return 1;
    }
    if(crypt_activate_by_keyfile(cd, "tmp_luks_vol", CRYPT_ANY_SLOT, "/root/usb.key", 0, 0) < 0){
        perror("Warning: failed to open Luks volume\n");
        crypt_free(cd);
        return 1;
    }
    printf("crypt device mounted\n");

    crypt_free(cd);
    return 0;
}

int close_luks_vol(const char *DEVICE_NAME){
    struct crypt_device *cd;

    if (crypt_init_by_name(&cd, DEVICE_NAME)< 0){
        perror("Warning: crypt_init_by_name() failed\n");
        return 1;
    }

    if ( crypt_status(cd, DEVICE_NAME) == CRYPT_ACTIVE ){
        printf("Device is active\n");
    }else{
        perror("Warning: device may not be active\n");
        crypt_free(cd);
        return 1;
    }

    if ( crypt_deactivate(cd, DEVICE_NAME) < 0){
        perror("Warning: failed to close crypt device\n");
        crypt_free(cd);
        return 1;
    }

    printf("Device deactivated\n");

    crypt_free(cd);
    return 0;
}


#include <sys/mount.h>
#include <stdio.h>
#include "disk_manage.h"

int mount_device(const char *DEV, const char *MNT_POINT) {
    if (mount(DEV, MNT_POINT, "ext4", 0, NULL ) == -1){
        perror("Mount error\n");
        return 1;
    }
    printf("Device mounted\n");
    return 0;
}

int umount_device(const char *MNT_POINT){
    if ( umount( MNT_POINT ) == -1 ){
        perror("Unmount failed\n");
        return 1;
    }
    printf("Unmounted device\n");
    return 0;
}


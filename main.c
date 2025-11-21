#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <inttypes.h>
#include <sys/types.h>
#include "luks.h"
#include "disk_manage.h"

int main(){
    const char *DEV = "/dev/sdb1";
    const char *MNT_POINT = "/media/luks_crypt";
    const char *KEY = "/root/usb.key";

    if(open_luks_vol(DEV, KEY) == 1){
        perror("Warning: failed to open luks volume\n");
    }
    if(mount_device(DEV, MNT_POINT) == 1){
        perror("Warning: failed to mount mapped device\n");
    }
    sleep(10);
    if(umount_device(MNT_POINT) == 1){
        perror("Warning: failed to umount mapped device\n");
    }
    if (close_luks_vol("tmp_luks_vol") == 1) {
        perror("Warning: failed to close luks volume\n");
    }
    return 0;
}

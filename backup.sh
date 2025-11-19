#!/bin/bash

UUID="894bd20c-5ed8-49b2-8efd-58ff9c828f79"
KEY_FILE=/root/usb.key
MAPPER="/dev/mapper/luks-$UUID"
MNT_POINT="/media/luks-$UUID"


set -euo pipefail

# Cleanup function will handle 
#   unmounting the disk, 
#   removing mount point and 
#   closing the luks container
cleanup() {
    # unmount the disk
    if mountpoint -q $MNT_POINT; then
        if ! sudo umount "$MNT_POINT"; then
            echo "Warning: failed to unmount mount point" >&2
        else
            echo "Unmounted mount point"
        fi
    fi

    # remove mount point
    if [ -d "$MNT_POINT" ]; then
        if sudo rmdir "$MNT_POINT"; then
            echo "Removing mount point"
        else
            echo "Warning: mount point not empty" >&2
        fi
    fi

    # close luks
    if [ -e "$MAPPER" ]; then
        if sudo cryptsetup luksClose "$MAPPER"; then
            echo "Luks container closed"
        else
            echo "Warning: failed to close luks container" >&2
        fi
    fi

}

trap cleanup EXIT


# Check if luks container is open
sudo cryptsetup luksOpen "/dev/disk/by-uuid/$UUID" "luks-$UUID" --key-file "$KEY_FILE"

# Check if mountpoint already exist
if [ ! -d "$MNT_POINT" ]; then
    sudo mkdir -p $MNT_POINT
fi

echo "Mounting drive"
sudo mount "$MAPPER" "$MNT_POINT"

echo "Performing backup process"
if sudo rsync -a "/home/algonotion/notes" "$MNT_POINT"; then
    echo "File backup successful"
    ls "$MNT_POINT"
else
    echo "Backup error" >&2
    exit 1
fi

echo "Script executed successfully"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Must handle errors incase wrong no file, wrong file, missing UUID(return value)
char *get_part_uuid(char *PATH){

    FILE *file_ptr;
    file_ptr = fopen(PATH, "r");

    char file_line[100];
    while(fgets(file_line, 100, file_ptr)){
        char *string_ptr = strtok(file_line, "=");
        if (strcmp(string_ptr, "PARTUUID") == 0){
            char *uuid = strtok(NULL, "\n");

            char *UUID;
            UUID = malloc(37);
            strcpy(UUID, uuid);
            
            fclose(file_ptr);
            return UUID;
        }
    }
    fclose(file_ptr);

    return NULL;
}

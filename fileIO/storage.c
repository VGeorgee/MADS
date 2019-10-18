#include "storage.h"
#include <string.h>



char *getfilename(char *username){
    char *buffer = calloc(sizeof(char), DEFAULT_FILENAME_LENGTH + BUFFER_LENGTH + 1);
    strcpy(buffer, DEFAULT_DATA_PATH);
    generatestring(buffer + DEFAULT_DATA_PATH_LENGTH - 1, username, DEFAULT_FILENAME_LENGTH);
    strcat(buffer, DEFAULT_DATA_EXTENSION);
    return buffer;
};


FILE *openfile(char *username, char *password){
    char *buffer = getfilename(username);
    FILE *fp = fopen(buffer, "r");
    free(buffer);
    return fp;
};


FILE *createfile(char *username, char *password){
    char *buffer = getfilename(username);
    puts(buffer);
    FILE *fp = fopen(buffer, "w+");
    free(buffer);
    return fp;
};

#include <stdio.h>
#include <stdlib.h>
#include "../utils.h"

#define DEFAULT_DATA_PATH "./data/"
#define DEFAULT_DATA_PATH_LENGTH sizeof(DEFAULT_DATA_PATH)
#define DEFAULT_DATA_EXTENSION ".dt"
#define DEFAULT_DATA_EXTENSION_LENGTH sizeof(DEFAULT_DATA_EXTENSION)
#define BUFFER_LENGTH DEFAULT_DATA_PATH_LENGTH + DEFAULT_DATA_EXTENSION_LENGTH
#define DEFAULT_FILENAME_LENGTH 60

char *getfilename(char *username);
FILE *openfile(char *username, char *password);
FILE *createfile(char *username, char *password);

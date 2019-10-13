
#include <string.h>

typedef struct tokens{
    int array_size;
    char **array;
}TOKENS;

TOKENS *string_tokenizer(char *string, char *delimit);
void free_tokens(TOKENS *token);

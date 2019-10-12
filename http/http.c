
#include "http.h"


void send_response(int socket, char *response){
    write(socket, response, strlen(response));
};

TOKENS *string_tokenizer(char *string, char *delimit){
    char *string_copy = calloc(sizeof(char), strlen(string) + 1);
    strcpy(string_copy, string);
    char delimiter = delimit[0];

    TOKENS *tokens = calloc(sizeof(TOKENS), 1);
    tokens->array = calloc(sizeof(char *), 20);
    int size = 0, i;
    char *pointer = string_copy;

    for(i = 0; string_copy[i]; i++){
        if(string_copy[i] == delimiter){
            tokens->array[size++] = pointer;
            string_copy[i] = '\0';
            pointer = string_copy + i + 1;
        }
    }
    tokens->array[size++] = pointer;
    tokens->array_size = size;
    return tokens;
}

void free_tokens(TOKENS *token){
    free(token->array[0]);
    free(token->array);
    free(token);
}

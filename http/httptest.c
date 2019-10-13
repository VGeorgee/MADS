#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "http.h"

char *test_request_get_verified =   "GET /verified-path HTTP/1.1\nauth-token: auth\n\nkey: value";
char *test_request_get_unverified = "GET /verified-path HTTP/1.1\nauth: auth\n\nkey: value";
char *test_request_post_login =  "POST /verified-path HTTP/1.1\ntype: login\n\nkey: value";
char *test_request_post_register =  "POST /verified-path HTTP/1.1\ntype: register\n\nkey: value";


int main(){

   printf("ASD\n");
    /*
    send_response(stdout->_fileno, test_request_get_verified);
    TOKENS *tokens = string_tokenizer(test_request_get_verified, "\n");
    printf("\n\nsize: %d\n\n", tokens->array_size);
    int i;
    for(i = 0; i < tokens->array_size; i++){
        puts(tokens->array[i]);
    }
    free_tokens(tokens);
    */

    REQUEST *request = parse_request(test_request_get_verified);

    printf("method: |%s|\nurl: |%s|\ntoken: |%s|\nbody: |%s|\n", request->type, request->url, request->token, request->body);
    return 0;
}
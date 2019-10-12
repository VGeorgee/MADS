#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct request{

    char *type;
    char *url;
    char *token;
    char *header;
    char *body;

}REQUEST;

typedef struct response{

    char *header;
    char *body;
    int statuscode;

}RESPONSE;

typedef struct tokens{
    int array_size;
    char **array;
}TOKENS;

/*
    parse_request must parse incoming request for further process
*/

REQUEST *parse_request(char *request);
TOKENS *string_tokenizer(char *string, char *delimit);
void free_tokens(TOKENS *token);
/*
    process_request must:
        - throw back bad requests, if required
        - verify auth
        - make further calls to prepare responses from valid requests
    
*/

void process_request(REQUEST *request);


RESPONSE *get_request(char *header, char *body);
RESPONSE *post_request(char *header, char *body);
RESPONSE *put_request(char *header, char *body);

/*
    write response to specified socket
*/
void send_response(int socket, char *response);

//GET POST PUT
/*
    valid request contain: GET|POST|PUT & must request specified url
    GET  
        send stored data back

        header must hold auth token


    
    POST
        login and register

        request:
            header must specify request type:

                type: login|register

                body: 
                {
                    username: username, 
                    password: password
                }
        
        response:
            authenticated:
                header: 
                    auth-token: token
            error:
                header:
                    error: errorcode

        
    
    PUT
        store data on server, auth required
            header:
                auth-token: token
            body:
            {
                key: value
            }

*/

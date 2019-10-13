#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <io.h>
#else
#include <unistd.h>
#endif


/**
 * RESPONSE_HEADER_LENGTH sets the maximal length of response header (http_version + statuscode + message)
 * */
#define RESPONSE_HEADER_LENGTH 100

/**
 * REQUEST_URL_LENGTH sets the maximal length of url used for requests
 * */
#define REQUEST_URL_LENGTH  60

/**
 * AUTH_TOKEN_LENGTH sets the maximal length of the auth-token used for authorization
 * */
#define AUTH_TOKEN_LENGTH 15

/**
 * AUTH_TOKEN_FIELD sets auth-token field naming in headers
 * */
#define AUTH_TOKEN_FIELD "auth-token"

/**
 * BODY_LENGHT sets the maximal length of request body
 * */
#define BODY_LENGHT 500

#define OK 200
#define OK_MESSAGE "OK"
#define UNAUTHORIZED 403
#define UNAUTHORIZED_MESSAGE "Invalid or missing auth-token"
#define MISSING 404
#define MISSING_MESSAGE "Could not found requested resource"
#define ERROR_MESSAGE "Something went wrong"


typedef struct request{

    char type[5];
    char url[REQUEST_URL_LENGTH];
    char token[AUTH_TOKEN_LENGTH];

    char *header;
    char body[BODY_LENGHT];

}REQUEST;
/*
    parse_request must parse incoming request for further process
*/
REQUEST *parse_request(char *buffer);


typedef struct response{

    char *body;
    int statuscode;

}RESPONSE;
RESPONSE *__GET(char *body);
RESPONSE *__POST(char *auth_type, char *body);
RESPONSE *__PUT(char *body);







/*
    process_request must:
        - throw back bad requests, if required
        - verify auth
        - make further calls to prepare responses from valid requests
    
*/
void process_request(REQUEST *request);



/**
 * 
 * HTTP/1.1 {status code} {message}
 * 
 * {body}
 * 
 * */

char *get_response(RESPONSE *response);


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



int skip_line(char *a);
int string_copy(char *a, char *b, char delimit);
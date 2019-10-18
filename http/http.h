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
 * AUTH_TOKEN_LENGTH sets the maximal length of the AUTH_TOKEN_FIELD field used for authorization
 * */
#define AUTH_TOKEN_LENGTH 15

/**
 * AUTH_TOKEN_FIELD sets auth-token field naming in headers
 * */
#define AUTH_TOKEN_FIELD "auth-token"

/**
 * POST_REASON_FIELD_LENGTH sets the maximal length of the POST_REASON_FIELD field used for post reasoning
 * */
#define POST_REASON_FIELD_LENGTH 20

/**
 * POST_REASON_FIELD sets reason field naming in post headers
 * */
#define POST_REASON_FIELD "auth-reason"

/**
 * BODY_LENGHT sets the maximal length of request body
 * */
#define BODY_LENGHT 500


#define LOGIN 1
#define REGISTER 2

#define OK 200
#define OK_MESSAGE "OK"
#define UNAUTHORIZED 403
#define UNAUTHORIZED_MESSAGE "Invalid or missing auth-token"
#define MISSING 404
#define MISSING_MESSAGE "Could not found requested resource"
#define ERROR_MESSAGE "Something went wrong"
#define INVALID_REQUEST 500
#define INVALID_REQUEST_TYPE_MESSAGE "Invalid Request Type"


typedef struct request{

    char type[5];
    char url[REQUEST_URL_LENGTH];
    char token[AUTH_TOKEN_LENGTH];
    char reason[POST_REASON_FIELD_LENGTH];

    char *header;
    char body[BODY_LENGHT];

}REQUEST;
/*
    parse_request must parse incoming request for further process
*/
REQUEST *parse_request(char *buffer);


typedef struct response{

    char token[AUTH_TOKEN_LENGTH];
    char body[BODY_LENGHT];
    int statuscode;

}RESPONSE;
RESPONSE *__GET(char *user, char *body);
RESPONSE *__POST(int auth_reason, char *user, char *body);
RESPONSE *__PUT(char *user, char *body);







/*
    process_request must:
        - throw back bad requests, if required
        - verify auth
        - make further calls to prepare responses from valid requests
    
*/
char *process_request(REQUEST *request);



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
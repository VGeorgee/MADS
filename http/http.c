
#include "http.h"


void send_response(int socket, char *response){
    write(socket, response, strlen(response));
};


/**
 * 
 * HTTP/1.1 {status code} {message}
 * 
 * {body}
 * 
 * */

char *get_response(RESPONSE *response){
    char *buffer = calloc(RESPONSE_HEADER_SIZE + strlen(response->body), 1);
    strcpy(buffer, "HTTP/1.1 ");
    char statuscode[10];
    itoa(response->statuscode, statuscode, 10);
    strcpy(buffer, statuscode);

    char *message = NULL;
    switch (response->statuscode)
    { 
        case OK:{message = OK_MESSAGE;} break;
        case UNAUTHORIZED:{message = UNAUTHORIZED_MESSAGE;} break;
        case MISSING:{message = MISSING_MESSAGE;} break;
        default: {message = ERROR_MESSAGE;} break;
    }
    strcpy(buffer, message);

    strcpy(buffer, "\n\n");
    if(response->body){
        strcpy(buffer, response->body);
    }
    return buffer;
};


#include "http.h"



REQUEST *parse_request(char *buffer){
    REQUEST *request = calloc(sizeof(REQUEST), 1);

    int offset = string_copy(request->type, buffer, ' ');
    offset += string_copy(request->url, buffer + offset, ' ');

    if(buffer[offset] == ' ')
        offset += skip_line(buffer);

    while(buffer[offset] && buffer[offset] != '\n'){
        if(strncmp(buffer + offset, AUTH_TOKEN_FIELD, strlen(AUTH_TOKEN_FIELD)) == 0){
            offset += string_copy(request->token, buffer + offset + strlen(AUTH_TOKEN_FIELD) + 2, ' '); // + 2 is ": " from "token: token" && token  MUST NOT contain spaces
        }
        offset += skip_line(buffer + offset);
    }

    offset++;
    //body started
    strcpy(request->body, buffer + offset);
    return request;
}

int string_copy(char *a, char *b, char delimit){
    int i;
    for(i = 0; b[i] && (b[i] != delimit) && (b[i] != '\n'); i++){
        a[i] = b[i];
    }
    a[i] = 0;

    if(b[i]) return i + 1; //skipping delimit and line feed
    return i;
}

int skip_line(char *a){
    int i;
    for(i = 0; a[i] && a[i] != '\n'; i++);
    if(a[i]) return i + 1; //skipping line feed if exist
    return i;
}


char *get_response(RESPONSE *response){
    char *buffer = calloc(RESPONSE_HEADER_LENGTH + strlen(response->body), 1);
    strcpy(buffer, "HTTP/1.1 ");
    char statuscode[10];
    sprintf(statuscode, "%d", response->statuscode);
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


void send_response(int socket, char *response){
    write(socket, response, strlen(response));
};


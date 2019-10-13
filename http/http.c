
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
        else if(strncmp(buffer + offset, POST_REASON_FIELD, strlen(POST_REASON_FIELD)) == 0){
            offset += string_copy(request->reason, buffer + offset + strlen(POST_REASON_FIELD) + 2, ' '); // + 2 is ": " from "reason: reason" && reason MUST BE login || register
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


RESPONSE *new_response(int statuscode){
    RESPONSE *response = calloc(sizeof(RESPONSE), 1);
    response->statuscode = statuscode;
}

#define AUTHENTICATED_USER 1



char *process_request(REQUEST *request){
    RESPONSE *response = NULL;
    if(strcmp(request->type, "GET") == 0){

        if(AUTHENTICATED_USER){
            response = __GET(request->token, request->body);
        } else{
            response = new_response(UNAUTHORIZED);
        }

    }

    else if(strcmp(request->type, "PUT") == 0){ 

        if(AUTHENTICATED_USER){
            response = __PUT(request->token, request->body);
        } else{
            response = new_response(UNAUTHORIZED);
        }

    }
    else if(strcmp(request->type, "POST") == 0){

        if(strcmp(request->reason, "login") == 0){
            response = __POST(LOGIN, request->token, request->body);
        } else if(strcmp(request->reason, "register") == 0){
            response = __POST(REGISTER, NULL, request->body);
        } else{
            response = new_response(INVALID_REQUEST);
        }

    }
    else{
        response = new_response(INVALID_REQUEST);
    }

    char *response_to_return = get_response(response);
    free(response);
    return response_to_return;
}

int skip_line(char *a){
    int i;
    for(i = 0; a[i] && a[i] != '\n'; i++);
    if(a[i]) return i + 1; //skipping line feed if exist
    return i;
}


char *get_response(RESPONSE *response){
    int body_length = response->body ? strlen(response->body) : 0;

    char *buffer = calloc(RESPONSE_HEADER_LENGTH + body_length, 1);
    strcpy(buffer, "HTTP/1.1 ");

    char statuscode[10];
    sprintf(statuscode, "%d", response->statuscode);
    strcat(buffer, statuscode);

    char *message = NULL;
    switch (response->statuscode)
    { 
        case OK:{message = OK_MESSAGE;} break;
        case UNAUTHORIZED:{message = UNAUTHORIZED_MESSAGE;} break;
        case MISSING:{message = MISSING_MESSAGE;} break;
        case INVALID_REQUEST: {message = INVALID_REQUEST_TYPE_MESSAGE;} break;
        default: {message = ERROR_MESSAGE;} break;
    }

    strcat(buffer, " ");
    strcat(buffer, message);
    if(response->token[0]){
        strcat(buffer, "\n");
        strcat(buffer, response->token);
    }
    if(response->body[0]){
        strcat(buffer, "\n\n");
        strcat(buffer, response->body);
    }
    return buffer;
};


void send_response(int socket, char *response){
    write(socket, response, strlen(response));
};


RESPONSE *__GET(char *user, char *body){
    RESPONSE *response = calloc(sizeof(RESPONSE), 1);
    response->statuscode = 200;
    strcpy(response->body, "ITT AZ ADAT");
    return response;
};

RESPONSE *__POST(int auth_reason, char *user, char *body){
    RESPONSE *response;

    if(auth_reason == LOGIN){
        ;
    } else if(auth_reason == REGISTER){
        ;
    }
    else {
        response = new_response(INVALID_REQUEST);
    }
    
    return response;
};

RESPONSE *__PUT(char *user, char *body){
    return NULL;
};


#include "utils.h"
#include <stdlib.h>

char chars[36] =  { 'A', 'B', 'C', 'D', 'E', 'F', 'G',
                    'H', 'I', 'J', 'K', 'L', 'M', 'N',
                    'O', 'P', 'Q', 'R', 'S', 'T', 'U',
                    'V', 'W', 'X', 'Y', 'Z', '0', '1',
                    '2', '3', '4', '5', '6', '7', '8',
                    '9'  };


char *generatestring(char *generated, char *seed, int desiredlength){
    unsigned int hash;
    int i;
    for(i = hash = 0; seed[i]; hash = (hash * 10) + seed[i++]);
    
    int seedlen = i;
    srand(hash);
    
    for(i = 0; i < desiredlength; i++){
        generated[i] = chars[((rand() + seed[i % seedlen]) % 36) ];
    }
    generated[i] = 0;
    return generated;
};

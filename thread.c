
#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details. 
#include <time.h>
  
  int rnd = 0;
  void * foglalt = 0;
// A normal C function that is executed as a thread  
// when its name is specified in pthread_create() 

void * foglal( void *pid){
    if(foglalt) 
        return foglalt;
    else 
        return foglalt = pid;
}

void *myThreadFun(void *vargp) 
{ 

    int iters = 0, foglalasid, rnd_thread;
    //sleep(((float)rand() / RAND_MAX) * 5); 
        usleep(((float)rand() / RAND_MAX) * 29);
    while(foglal(vargp) != vargp){
        usleep(((float)rand() / RAND_MAX) * 29);
        iters++;
    } 

    //usleep(500);
    foglalasid = foglalt;
    rnd_thread = rnd++;

    //usleep(((float)rand() / RAND_MAX) * 5);
    printf("threadID: %2lld\tfoglalt_thread: %3d\tallitott szam: %2d\t varakozasok:%4d\n", (long long)vargp, foglalasid, rnd_thread , iters);
    usleep(500);
    foglalt = 0;
    return NULL; 
}

int main() 
{ 
    srand(time(NULL));
    pthread_t thread_id; 
    printf("Before Thread\n"); 
    for(long long i = 0; i < 500; usleep(1), i++)
        pthread_create(&thread_id, NULL, myThreadFun, (void * restrict)i); 
    //pthread_join(thread_id, NULL); 
    printf("After Thread\n"); 
    sleep(2);
    exit(0); 
}

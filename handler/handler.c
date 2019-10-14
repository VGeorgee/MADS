
#include  <stdio.h>
#include  <signal.h>
#include "handler.h"








void  persist(int sig)
{
  printf("Files saved!\n");
  signal(SIGALRM, persist);
  alarm(DEFAULT_PERSIST_INTERVAL); 
}

int main(int argc, char *argv[])
{
    persist(0);
    while (1)
        ;
    printf("All done\n");
}
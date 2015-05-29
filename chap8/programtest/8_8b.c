#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define oops(s,x) { perror(s); exit(x);}
#define MAXDELAY 10

main( int ac, char *av[] )
{
    void child_code(int),parent_code(int);

    pid_t pid;
    int i,n;
    int delay;

    if(ac == 1 )
    {
        fprintf(stderr,"usage: number of children");
        exit(1);
    }
     n = atoi(av[1]);
     srand(getpid());

     printf("before :mypid is %d\n",getpid());

     for(i=0; i<n; i++)
     {
         delay = 1 + (rand() % MAXDELAY);
         pid = fork();
         if( pid == -1 )
             oops("fork",2);
         if( pid == 0 )
             child_code(delay);
     }
     parent_code(n);
     return 0;
}

void child_code( int delay )
{
    printf("child %d here.will  sleep for %d seconds\n", getpid(),delay);
    sleep(delay);
    printf("child done. about to exit\n");
    exit(17);

}

void parent_code(int n)
{
    int wait_rv;
    printf("waiting for %d children\n",n);

    while((wait_rv = wait(NULL)) != -1)
        printf("wait returned: %d. %d to go\n",wait_rv,--n);
}

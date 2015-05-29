#include <stdlib.h>
#include <signal.h>

int main( int ac, char * av[])
{
    int n,i;
    pid_t pid,newpid;

    void handler(pid_t);

    n = atoi(av[1]);
    printf("before fork(,pid = %d)",getpid());
    signal(SIGCHLD,handler);
    for( i=0; i<n; i++)
    {
        pid = fork();
        if(pid == 0 )
        {
            sleep(5);
            exit(17);
        }
        else
        {
            while(1)
            {
                sleep(1);
                printf("waiting...\n");
            }
            //signal(SIGCHLD,handler);
        }
    }

}

void handler(pid_t pid)
{
    int wait_rv;
    int count = 0;
    wait_rv = wait(NULL);
    
    printf("son pid is %d,wait for %d,",pid,wait_rv);

    count++;

    //if(count == pid )
        //break;
}

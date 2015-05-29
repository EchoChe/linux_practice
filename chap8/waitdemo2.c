#include <stdio.h>
#include <stdlib.h>
#include    <signal.h>

#define DELAY 5

main()
{
    int newpid;
    void child_code(),parent_code();

    printf("before: mypid is %d\n",getpid());

    if((newpid = fork()) == -1)
        perror("fork");
    else if( newpid == 0 )
        child_code(DELAY);
    else
        parent_code(newpid);

    //signal(SIGINT,SIG_IGN);
}

void child_code(int delay)
{
    printf("child %d here.will sleep for %d seconds\n",getpid(),delay);
    while(1)
    {
        printf("Hello\n");
        sleep(1);
    }
    sleep(delay);
    printf("child done.about to exit\n");
    exit(17);

}
void hander()
{
    printf("eixt~~~~%d\n",getpid());
}
void parent_code(int childpid)
{
    int wait_rv;
    int child_status;
    int high_8,low_7,bit_7;
    
    signal(SIGINT,hander);
    //printf("eeeeeeeeeeeeeee\n");
    printf("parent here,sleep until child exits...\n");
    //signal(SIGINT,hander);
    printf("ccccccccccccccccc\n");
   wait_rv = wait(&child_status);
   printf("done waiting for %d.Wait returned: %d\n",childpid,wait_rv);

    high_8 = child_status>>8;
    low_7 = child_status & 0x7F;
    bit_7 = child_status & 0x80;
    printf("status: exit = %d,sig = %d ,core = %d\n",high_8,low_7,bit_7);

}

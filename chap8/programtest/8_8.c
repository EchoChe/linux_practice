#include <stdio.h>

#define DELAY 2

main()
{
    int newpid,newpid2;
    void child_code(),parent_code();

    printf("before: mypid is %d\n",getpid());
    
    if((newpid = fork()) == -1)
    {
        perror("fork");
    }
    else if(newpid == 0)
    {
        child_code(DELAY);
    }
     if((newpid2 = fork()) == -1)
        perror("fork");
    else if(newpid2 == 0)
        child_code(DELAY);

    parent_code(newpid,newpid2);
    return 0;
}

void child_code(int delay)
{
    printf("child %d here.will sleep for %d seconds\n",getpid(),delay);
    sleep(delay);
    printf("child done.about to exit.\n");
    exit(17);
}

void parent_code(int childpid1,int childpid2)
{
    int wait_rv;

    wait_rv = wait(NULL);
    printf("Wait returned: %d\n",wait_rv);

    wait_rv = wait(NULL);
    printf("wait returned: %d\n",wait_rv);
}

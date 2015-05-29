#include <stdio.h>

#define DELAY 2

main()
{
    int pid1,pid2;
    
    printf("Before fork(),pid:%d\n",getpid());

    pid1 = fork();
    if( pid1 == 0 )
    {
        printf("child1:%d\n",getpid());
    }
    else
    {
        pid2 = fork();
        if( pid2 == 0)
            printf("child2 : %d\n",getpid());
        else
            printf("father: %d\n",getpid());
    }
}

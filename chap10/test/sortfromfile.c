#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

main()
{
    int pid;
    int fd;

    printf("About to run sort into a file\n");

    if(( pid = fork()) == -1 )
    {
        perror("fork");
        exit(1);
    }

    if( pid == 0 )
    {
        close(0);
        fd = open("xyz",O_RDONLY);
        execlp("sort","sort",NULL);
        perror("execlp");
        exit(1);
    }

    if(pid != 0)
    {
        wait(NULL);
        printf("Done running sort. result in userlist\n");
    }
}

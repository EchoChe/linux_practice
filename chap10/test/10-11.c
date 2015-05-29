#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

main()
{
    int pid;
    //int fd;
    char * file ="userlist";

    printf("About to run who into a file\n");

    if(( pid = fork()) == -1 )
    {
        perror("fork");
        exit(1);
    }

    if( pid == 0 )
    {
        close(1);
        open(file,O_WRONLY|O_CREAT|O_APPEND,0644);
        execlp("who","who",NULL);
        perror("execlp");
        exit(1);
    }

    if(pid != 0)
    {
        wait(NULL);
        printf("Done running who. result in userlist\n");
    }
}

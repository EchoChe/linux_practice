#include <stdio.h>
#include <signal.h>

#define READ 0
#define WRITE 1

FILE * popen(const char * commad, const char * mode)
{
    int pfp[2],pid;
    FILE * fdopen(), *fp;
    int parent_end,child_end;

    if( *mode == 'r' )
    {
        parent_end = READ;
        child_end = WRITE;
    } else if( *mode == 'w')
    {
        parent_end = WRITE;
        child_end = READ;
    }else return NULL;

    if( pipe(pfp) == -1)
        return NULL;
    if(( pid = fork()) == -1)
    {
        close(pfp[0]);
        close(pfp[1]);
        return NULL;
    }

    if( pid >0 )
    {

    }
}

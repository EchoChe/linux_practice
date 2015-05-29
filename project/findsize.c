#include <stdio.h>
#include <sys/stat.h>

int main( int ac,char * av[] )
{
    struct stat infobuf;

    if(stat(".",&infobuf) == -1 )
        perror(".");
    else
        printf("The size of current path  is %d\n",infobuf.st_size);
}

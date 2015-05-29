# include <stdio.h>
# include <sys/stat.h>
# include <dirent.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>


int main( int ac, char * av[] )
{
    if( ac != 3 )
    {
        fprintf(stderr, "usage : %s source destination\n", *av);
        exit(1);
    }
    return do_mv( av[1], av[2] );
}



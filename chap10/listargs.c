#include <stdio.h>

main( int ac, char *av[])
{
    int i;

    printf("Number of args: %d, Arg are :\n",ac);
    for(i=0; i<ac; i++)
        printf("args[%d]%s\n",i,av[i]);

    fprintf(stderr,"Thie message is sent to stderr.\n");
}

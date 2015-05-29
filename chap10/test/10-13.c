#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define oops(m,x) { perror(m);  exit(x);}

main( int ac, char ** av)
{
     int thepipe[2],newfd, pid;

     if( ac != 4) 
     {
         fprintf(stderr, "Usage: pipe cmd1 cmd2\n");
         exit(1);
     }

     if( pipe( thepipe) == -1 )
     {
         oops("cannot get a pipe",1);
     }

     if( (pid = fork()) == -1 )
         oops("cannot fork",2);
     if( pid > 0 )
     {
         close(thepipe[1]);
        if( dup2( thepipe[0],0) == -1 )
            oops("could not redirent stdin",3);
        close( thepipe[0]);
        execlp( av[3],av[3],NULL);
        oops( av[3],4);
     }
    else
    {
        close(thepipe[0]);

        if( dup2(thepipe[1],1) == -1 )
               oops("could not redirent stdout",4);
        
        close(thepipe[1]);

        do_child(ac-1,av);

        execlp( av[2], av[2], NULL);
        oops( av[2],5);

    }
}
void do_child( int ac, char * av[])
{

}

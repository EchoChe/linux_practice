#include <stdio.h>
#include <signal.h>

main()
{
    void f(int);
    int i;
    
    signal( SIGQUIT, f );
    for( i=0; i<5; i++ )
    {
        printf("Hello!\n");
        sleep(3);
    }
}

void f( int signum )
{
    printf(" OUCH! \n");
}

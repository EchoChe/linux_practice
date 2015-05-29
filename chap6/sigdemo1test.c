#include <stdio.h>
#include <signal.h>
int count = 0;
int quitnum ;
int main( int argc, char * argv[] )
{
    void f(int);
    int i;
   // int count = 0;
    quitnum = atoi( argv[1] );
    while(1)
    {
    
    signal( SIGINT, f );
    signal( SIGQUIT, SIG_IGN );
       
    for( i=0; i<5; i++ )
    {
        printf("Hello!\n");
        sleep(3);
    }
    }
}

void f( int signum )
{   
    int i;
    count++;
    if( quitnum == count )
        exit(0);
    printf(" OUCH!");
    for( i = 0; i < count; i++ )
    {
        printf("!");
        
    }
    
}

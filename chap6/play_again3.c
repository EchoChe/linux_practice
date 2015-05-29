#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include <string.h>
/* 
 * play_again3.c
 *
 *  purpose: ask if user wants another transaction
 *   method: set tty into chr-by-chr, no-echo mode
 *       set tty into no-delay mode
 *       read char, return result
 *  returns: 0=>yes, 1=>no, 2=>timeout
 *   better: reset terminal mode on Interrupt
 */
#define ASK     "Do you want another transaction"
#define TIMEOUT     3   /* in seconds   */
#define SLEEPTIME 4
#define BEEP putchar('\a');
int get_response( char *, int );
main()
{
    int response;
    tty_mode(0);
    set_cr_noecho_mode();           /* set -icanon, -echo   */
    set_nodelay_mode();         /* noinput => EOF   */
    response = get_response(ASK, 3);  /* get some answer  */
    tty_mode(1);           /* restore tty state    */
    return response;
}
get_response( char *question , int maxtries )
/*
 * purpose: ask a question and wait for a y/n answer or timeout
 *  method: use getchar and complain about non-y/n input
 * returns: 0=>yes, 1=>no
 */
{
    int input;



    printf("%s (y/n)?", question);          /* ask      */
    //fflush(stdout);                 /* force output */
    while ( 1 ){
        sleep(SLEEPTIME);               /* wait a bit   */
        printf("Waiting....");
        fflush(stdout);
        //input = tolower(get_ok_char());          /* getachar */
       input = getchar();
        if ( input == 'y') /* Y?       */
           { 
                printf("Yes\n");
                return 0;
            }
        if ( input == 'n') /* N?       */
           {
             printf("No\n");
             return 1;
           }
        if (( maxtries--) == 0 )       /* outatime?    */
                return 2;       /* sayso    */
            BEEP;
    }
}

get_ok_char()
{
    int c;
    
   // printf("waiting.......");
    while(( c = getchar()) != EOF && strchr( "yYnN", c ) == NULL )
    ;
    return c;
}
set_cr_noecho_mode()
/* 
 * purpose: put file descriptor 0 into chr-by-chr mode and noecho mode
 *  method: use bits in termios
 */
{
    struct  termios ttystate;

    tcgetattr( 0, &ttystate);       /* read curr. setting   */
    ttystate.c_lflag        &= ~ICANON; /* no buffering     */
    ttystate.c_lflag        &= ~ECHO;   /* no echo either   */
    ttystate.c_cc[VMIN]     =  1;       /* get 1 char at a time */
    tcsetattr( 0 , TCSANOW, &ttystate); /* install settings */
}

set_nodelay_mode()
/*
 * purpose: put file descriptor 0 into no-delay mode
 *  method: use fcntl to set bits
 *   notes: tcsetattr() will do something similar, but it is complicated
 */
{
    int termflags;

    termflags = fcntl(0, F_GETFL);      /* read curr. settings  */
    termflags |= O_NDELAY;          /* flip on nodelay bit  */
    fcntl(0, F_SETFL, termflags);       /* and install 'em  */
}

tty_mode( int how )
{
    static struct termios original_mode;
    static int original_flags;
    if( how == 0 )
    {
        tcgetattr( 0, &original_mode );
        original_flags = fcntl( 0, F_GETFL );
    }
    else
     {
        tcsetattr(0, TCSANOW, &original_mode);  /* undo -icanon, -echo  */
        fcntl( 0, F_SETFL, original_flags); /* undo NoDelay     */
    }
}

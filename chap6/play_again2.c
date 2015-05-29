#include <stdio.h>
#include <termios.h>

#define QUESTION "Do you want another transaction"

int main()
{
    int response;
    tty_mode();
    set_cr_noecho_mode();
    response = get_response( QUESTION );
    tty_mode(1);
    return response;
}

int get_response( char * question )
{
    printf("%s (y/n)?", question );
    while(1)
    {
        switch( getchar() )
        {
            case 'Y':
            case 'y':
                printf(" fun ! \n");
                return 0;
            case 'N':
            case 'n':
            case EOF:
                printf("Not !\n");
                return 1;
        }
    }
}

set_cr_noecho_mode()
{
    struct termios ttystate;
    tcgetattr( 0, &ttystate );
    ttystate.c_lflag &= ~ICANON;
    ttystate.c_lflag &= ~ECHO;
    ttystate.c_cc[VMIN] = 1;
    tcsetattr( 0, TCSANOW, &ttystate );
    
}

tty_mode( int how )
{
    static struct termios original_mode;
    
    if( how == 0 )
        tcgetattr( 0, &original_mode );
    else
        return tcsetattr( 0, TCSANOW, &original_mode );
}


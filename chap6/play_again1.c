#include <stdio.h>
#include <termios.h>

#define QUESTION "Do you want anoter transation"

int main()
{
    int response;
    tty_mode(0);
    set_crmode();
    response = get_response( QUESTION );
    tty_mode(1);
    return response;
}

int get_response( char * question )
{
    int input;
    printf("%s(Y/N)?", question );
    while(1)
    {
        switch(input = getchar())
        {
            case 'Y':
            case 'y':
                printf("fun");
                return 0;
            case 'N':
            case 'n':
            case EOF:
                printf("Not");
                return 1;
            default:
                printf("\n cannot understand %c", input);
                printf("Please type y or n \n");
        }
    }
}

set_crmode()
{
    struct termios ttystate;
    
    tcgetattr( 0, &ttystate );
    ttystate.c_lflag &= ~ICANON;
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

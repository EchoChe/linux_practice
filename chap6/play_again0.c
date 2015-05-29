#include <stdio.h>
#include <termios.h>

#define QUESTION "Do you want another transaction"

int get_response( char * );

int main()
{
    int response;
    
    response = get_response( QUESTION );
    return response;
}

int get_response( char * question )
{
    printf("%s (Y/N)?", question);
    while(1)
    {
        switch( getchar() )
        {
            case 'y':
            case 'Y': 
                 printf("Y");
                    break;
            case 'n':
            case 'N':
            case EOF:
                return 1;
        
        }
    }
}

#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <string.h>
int main( int argc, char * argv[] )
{
    int i;
    int len;
    char  s[13] = "Hello,world!";
    initscr();
    
    clear();
     if( argc == 2 )
        strcpy( s, argv[1] );
     len = strlen(s);
    while(1)
    {
        clear();
         move( LINES/2, (COLS-len)/2 );
         addstr(s);
         refresh();
        sleep(1); 
        clear();
        move( LINES-1, COLS-1 );
        refresh();
        endwin();
    }

}

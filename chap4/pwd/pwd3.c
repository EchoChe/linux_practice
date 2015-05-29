# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <stdlib.h>

typedef struct namelist
{
    char name[10];
    struct namelist * next;
}NL;

ino_t get_inode( char * );
NL * printpathto( ino_t , NL * );
void inum_to_name( ino_t, char *, int );
void print( NL * );

int main()
{
    NL * head;
    head = ( NL * )malloc(sizeof( NL ));
    head->next = NULL;
    head = printpathto(get_inode("."), head );
    putchar('\n');
    print( head );
    return 0;
}

void print( NL  * head )
{
    NL * p;
    
    p = head;
    while( p->next  )
    {    
        printf("/%s", p->name );
        p = p->next;
    }
    printf("\n");    
}

NL *  printpathto( ino_t this_inode , NL *  head )
{
    ino_t my_inode;
    char its_name[BUFSIZ];
    NL * p;
    p = head;

    while( get_inode("..") != this_inode )
    {
        chdir("..");
        inum_to_name( this_inode, its_name, BUFSIZ );
        my_inode = get_inode( "." );
        this_inode = my_inode ;
        printf(" /%s", its_name );
        p = ( NL * )malloc(sizeof( struct namelist ));
        strcpy( p->name, its_name);
        p->next = head;
        head = p;    
    }
    return head;
}

void inum_to_name( ino_t inode_to_find, char * namebuf, int buflen )
{
    DIR * dir_ptr;
    struct dirent * direntp;
    
    dir_ptr = opendir(".");
    if( dir_ptr == NULL )
    {
        perror(".");
        exit(1);
    }

    while(( direntp = readdir( dir_ptr)) != NULL )
        if( direntp->d_ino == inode_to_find )
        {
            strncpy( namebuf, direntp->d_name, buflen );
            namebuf[buflen - 1] = '\0';
            closedir( dir_ptr ); 
            return ;  
        }
    fprintf( stderr, "error looking for inum %d\n", inode_to_find );
    exit(1);
}

ino_t get_inode( char * fname )
{
    struct stat info;
    if( stat( fname, &info) == -1 )
    {
        fprintf( stderr,"Cannot stat ");
        perror( fname );
        exit(1);
    }
    return info.st_ino;
}

# include <stdio.h>
# include <sys/types.h>
# include <dirent.h>
# include <string.h>
# include <stdlib.h>

struct namelist
{
    char name[10];
    struct namelist *next;
};

struct namelist * do_ls( char [],struct namelist * );
void printlist( struct namelist *);
struct namelist * sortlistADD( struct namelist *);
struct namelist * sortlistDEC( struct namelist *);

int main( int ac, char * av[] )
{
    struct namelist *head;
    head = ( struct namelist *)malloc(sizeof(struct namelist));
    head->next = NULL;
    if( ac == 1)
       head = do_ls( ".",head );
    else
        while( --ac )
        {
            printf( "%s\n", *++av );
           head =  do_ls( *av, head );
        }
    printf("before sort:---------");    
    printlist( head );

    sortlistADD( head );
    printf("\nAfter  add sort:-==========");
    printlist( head );

    sortlistDEC( head );
    printf("\nAfter dec sort:~~~~~~~~~");
    printlist( head );    
}

struct namelist * do_ls( char dirname[] ,struct namelist * head )
{
    DIR * dir_ptr;
    struct dirent * direntp;
    struct namelist * p;
    
     strcpy(head->name,dirname);
    
    if(( dir_ptr = opendir( dirname)) == NULL )
        fprintf( stderr," ls1: cannot open %s \n",dirname );
    else
    {
        while(( direntp = readdir( dir_ptr)) != NULL )
        {
            // printf(" %s\n ",direntp->d_name );
             p = ( struct namelist *)malloc(sizeof(struct namelist));
             strcpy(p->name,direntp->d_name);
             p->next = head;
             head = p;

        }
        closedir( dir_ptr );
    }
    return head;
}

void printlist( struct namelist * head )
{
    struct namelist * p;
    
    for( p = head; p->next != NULL; p = p->next)
        printf("%s   ",p->name);
}

/*struct namelist * sortlist( struct namelist * head )
{
    struct namelist * first;
    struct namelist * tail;
    struct namelist * p_min;
    struct namelist * min;
    struct namelist * p;

    first = NULL;
    
    
    while( head != NULL  )
    {
        for( p = head,min = head; p->next != NULL ; p = p->next)
        {
            if( strcmp(p->next->name,min->name) < 0 )
            {
                p_min = p;
                min = p->next;
            }
        }
        if( first ==  NULL )
        {
            first = min;
            tail = min;
        }
        else
        {
            tail->next = min;
            tail = min;
        }
        
        if( min = head )
            head = head->next;
        else
            p_min->next = min->next;


        if( first != NULL )
            tail->next = NULL;

    }
        head = first;
        
        return head;
    
    
}*/

struct namelist * sortlistADD( struct namelist * head )
{
    struct    namelist *p,*q;
    char  temp[10];
    
    for( p = head; p!= NULL; p = p->next)
    {
        for( q = p->next; q != NULL; q = q-> next)
        {
            if(strcmp( p->name,q->name) > 0 )
            {
                strcpy(temp, q->name);
                strcpy(q->name,p->name);
                strcpy(p->name,temp);
            }
        } 
    }
        return head;
}

struct namelist * sortlistDEC( struct namelist * head )
{
    struct    namelist *p,*q;
    char  temp[10];

    for( p = head; p!= NULL; p = p->next)
    {
        for( q = p->next; q != NULL; q = q-> next)
        {
            if(strcmp( p->name,q->name) < 0 )
            {
                strcpy(temp, q->name);
                strcpy(q->name,p->name);
                strcpy(p->name,temp);
            }
        }
    }
        return head;
}


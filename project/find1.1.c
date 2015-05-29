#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

typedef struct info
{
    char name[20];    
    char dirname[10];
    struct stat statbuf;
    DIR * dir_ptr;
    int flag;

}INFO;

void do_save( INFO  inf[], int *n )
{
    DIR * dir_ptr;
    struct dirent * direntp;
    //int count = 0;

    if(( dir_ptr = opendir(".")) == NULL )
        fprintf(stderr,"cannnot open current dirent");
    else 
    {
        while(( direntp = readdir( dir_ptr)) != NULL )
        {
            if(( strcmp(".",direntp->d_name) == 0 ||strcmp("..",direntp->d_name) == 0 ))
                continue;
            stat(direntp->d_name, &(inf[count].statbuf));
            strcpy(inf[count].name, direntp->d_name);
            srcpy(dirname,".");          
            inf[n].dir_ptr = dir_ptr;
             inf[n].flag = 1;
             n++;
             if(isadir(direntp->d_name))
             {
                 putchar('\n');
                 do_save(inf,&n);
             }
        }
        //*n = count;
        closedir(dir_ptr);
    }
}

void change_nflag( INFO inf[], int n, char name[] )
{
    int i;

    for( i = 0; i < n; i++)
    if(strstr(inf[i].name,name) != NULL )//模糊匹配name
        inf[i].flag &= 1;
    else
        inf[i].flag &= 0;

    
}

void change_sflag( INFO inf[], int n, char size[])
{
    //char c = size[0];
    int stat_size = atoi(size);
    int i;
    
    for( i=0; i<n; i++ )
        if( inf[i].statbuf.st_size <= stat_size )
                    inf[i].flag &= 1;
        else 
            inf[i].flag &= 0;

      /* switch(c)
       {
           case '+':
               {
                   if( inf[i].statbuf.st_size > stat_size )
                           inf[i].flag &= 1;
               }break;
           case '-':
               {
                    if( inf[i].statbuf.st_size <= stat_size )
                            inf[i].flag &= 1;
               }break;
           default:
               {
                   if( inf[i].statbuf.st_size == stat_size )
                               inf[i].flag &= 1;
                   else
                          inf[i].flag &= 0;
               } break;

       } */
}

void change_gidflag( INFO inf[], int n, char gid[])
{
    int findgid = atoi(gid);
    int i;
    for( i=0; i<n; i++)
        if( inf[i].statbuf.st_gid == findgid )
            inf[i].flag &= 1;
        else
            inf[i].flag &= 0;
}

 void change_uidflag( INFO inf[], int n, char uid[])
{
    int finduid = atoi(uid);
    int i;
    for( i=0; i<n; i++)
        if( inf[i].statbuf.st_uid == finduid )
            inf[i].flag &= 1;
        else
            inf[i].flag &= 0;                         
}



void change_tflag( INFO inf[], int n, char type[] )
{
    int i;
    for( i=0; i<n; i++ )
    {
        switch(type[0])
        {
            case 'd':
                {
                    if( S_ISDIR(inf[i].statbuf.st_mode))
                        inf[i].flag &= 1;
                    else
                        inf[i].flag &= 0;

                }break;
            case 'c':
                {
                    if( S_ISCHR(inf[i].statbuf.st_mode))
                        inf[i].flag &= 1;
                    else
                        inf[i].flag &= 0;                    

                }break;
            case 'b':
                {
                    if( S_ISBLK(inf[i].statbuf.st_mode))
                        inf[i].flag &= 1;
                    else
                        inf[i].flag &= 0;                    

                }break;
            case 'l':
                {
                    if( S_ISLNK(inf[i].statbuf.st_mode))
                        inf[i].flag &= 1;
                    else
                       inf[i].flag &= 0;

                }break;
            case 'f':
                {
                     if( S_ISREG(inf[i].statbuf.st_mode))
                         inf[i].flag &= 1; 
                     else
                         inf[i].flag &= 0;
                }
            default: 
               inf[i].flag &= 0; 
                break;
        }
    }
}

void mode_to_letters ( int mode, char str[] )
{

        strcpy( str, "----------" );
        if( S_ISDIR( mode ))
            str[0] = 'd';
        if( S_ISCHR( mode ))
            str[0] = 'c';
        if( S_ISBLK( mode ))
            str[0] = 'd';

        if( mode & S_IRUSR )
            str[1] = 'r';
        if( mode & S_IWUSR )
            str[2] = 'w';
        if( mode & S_IXUSR )
            str[3] = 'x';
                                    
        if( mode & S_IRGRP )
            str[4] = 'r';
        if( mode & S_IWGRP )
            str[5] = 'w';
        if( mode & S_IXGRP )
            str[6] = 'x';

        if( mode & S_IROTH )
            str[7] = 'r';
        if( mode & S_IWOTH )
            str[8] = 'w';
        if( mode & S_IXOTH )
            str[9] = 'x';


}
void do_print( INFO inf)
{
    char str[10]; 
    printf("\nname          mode   user   group  size");
    printf("\n ./%s", inf.name);
    mode_to_letters(inf.statbuf.st_mode, str);
    printf(" %s",str); 
    printf(" %d",inf.statbuf.st_uid);
    printf(" %d",inf.statbuf.st_gid);
    printf(" %ld",inf.statbuf.st_size);
    
}


void do_print_afterflag( INFO inf[], int n )
{
    int i;
    for( i=0; i<n; i++)
    {
        if( inf[i].flag == 1 )
            do_print(inf[i]);
    }
    printf("\n");
}
int main( int ac, char * av[])
{
    INFO  inf[40];
    int n = 0;
    int i  = 0;

    do_save( inf, &n );
    

    for( i = 1; i < ac; i=i+2 )
       switch( av[i][0] )
       {
         case 'n'://name
            change_nflag( inf,n,av[i+1] );  break;
        case 't'://type
            change_tflag( inf,n,av[i+1]);   break;
        case 's'://size
            change_sflag( inf,n,av[i+1] );  break;
        case 'g':
            change_gidflag( inf, n, av[i+1]);  break;
        case 'u':
            change_uidflag( inf, n, av[i+1]);  break;
        }
    printf("\n------------------------------------");
    printf("\nafter choise:");
    do_print_afterflag(inf,n);
}


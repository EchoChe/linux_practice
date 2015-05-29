#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>


isadir(char *str)
{

        struct stat info;

        return ( lstat(str,&info) != -1 && S_ISDIR(info.st_mode) );

}

void do_find( char dirname[])
{
    DIR * dir_ptr;
    struct dirent * direntp;
    char * fullpath;

    if(( dir_ptr = opendir( dirname)) == NULL )
    {
        fprintf( stderr, "cannot open %s\n", dirname);
        return ;
    }
    

    printf("%s\n",dirname);
    fullpath = (char *)malloc(strlen(dirname)+1+20+1);

    while(( direntp = readdir( dir_ptr)) != NULL)
    {
        if(strcmp(".", direntp->d_name)== 0 || strcmp("..", direntp->d_name) == 0)
            continue;
        sprintf(fullpath,"%s/%s",dirname,direntp->d_name);
        printf("%s\n",direntp->d_name);
        if( isadir(fullpath) )
        {
            putchar('\n');
            do_find(fullpath);
        }
    }

    closedir(dir_ptr);
    free(fullpath);
}

main( int ac, char * av[])
{
    do_find(".");
}

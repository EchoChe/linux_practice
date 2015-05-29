#include <stdlinb.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

typedef struct info{
    int flag;
    char name[20];
}INFO;

void do_save( INFO inf[], int *n)
{
    DIR * dir_ptr;
    struct dirent * direntp;
    int count = 0;

    if(( dir_ptr = opendir(".")) == NULL )
        fprintf(stderr, "cannot open current dirent");
    else
    {
        while(( direntp = readdir( dir_ptr)) != NULL )
        {
            strcpy(inf[count].name, direntp->d_name); 
            falg = 0;
            count++;
        }
    }
    *n = count;
    closedir(dir_ptr);
}

int main( int ac, char * argv[] )
{
    INFO inf[40];
    int n = 0;

    do_save( inf, &n);
}

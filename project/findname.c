#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

void find_namedir(char[],char[]);

int main( int ac, char * av[] )
{
    find_namedir(".",av[2]);
}

void find_namedir(char dirname[],char av[])
{
    DIR * dir_ptr;
    struct dirent * direntp;
    int flag = 0;

    if((dir_ptr = opendir(dirname)) == NULL )
        fprintf( stderr,"findname: cannot open %s\n",dirname);
    else
    {
        while((direntp = readdir(dir_ptr)) != NULL )
            if(strcmp(direntp->d_name,av) == 0 )
            {
                printf("./%s\n",direntp->d_name);
                flag = 1;

             }
        if( flag = 0 )
            printf("not find this dirname");
        close(dir_ptr);

    }

}

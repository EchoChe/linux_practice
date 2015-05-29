#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define  ERR_EXIT do{perror(nsg); exit(EXIT_FALURE)} while(0)

int main()
{
    //创建socket套接字
    int socketfd = socket(PF_INT,SOCK_STREAM,0);

    //bind

}

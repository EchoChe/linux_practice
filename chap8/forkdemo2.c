#include <stdio.h>

int main()
{
    printf("mypid is %d\n", getpid());
    fork();
    fork();
    fork();
    printf("mypid is %d\n", getpid());

}

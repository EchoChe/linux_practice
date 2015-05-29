#include <stdio.h>
#include <stdlib.h>
 
int main(void)
{
    FILE *fp;
    char buf[BUFSIZ];
    if (NULL != (fp = popen("curl http://www.baidu.com", "r")))
        fread(buf, BUFSIZ, 1, fp);
    else {
        fprintf(stderr, "popen error...\n");
        exit(1);
    }
    printf("%s\n", buf);
    pclose(fp);
    return 0;
}

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <string.h>
#include <stdarg.h>
#include <netdb.h>
#include <setjmp.h>
#include <signal.h>

/*gethostbyname 超时返回
这里使用的办法是设置一个时钟，如果gethostbyname在指定的时间内尚未返回，
时钟会强制其返回，得到的返回值显然是空指针，等价于告诉用户主机未连如互联网或者该域名无法解析。*/
static sigjmp_buf jmpbuf;
static void alarm_func() //该函数执行之后会执行跳转
{
     siglongjmp(jmpbuf, 1);
}


static struct hostent *gngethostbyname(char *HostName, int timeout)
{
     struct hostent *lpHostEnt;

     signal(SIGALRM, alarm_func);  //接受alarm信号，然后调用函数
     if(sigsetjmp(jmpbuf, 1) != 0)//跳转目的地
     {
           alarm(0);//timout
           signal(SIGALRM, SIG_IGN);
           return NULL;
     }
     alarm(timeout);//setting alarm
     printf("\nwill gethost!\n");
     lpHostEnt = gethostbyname(HostName);
     signal(SIGALRM, SIG_IGN);

     return lpHostEnt;
}



/*(linux socket编程实现connect超时的一种方法
创建套接字，将其设置成非阻塞状态。 
调用connect连接对端主机，如果失败，判断当时的errno是否为EINPROGRESS，也就是说是不是连接正在进行中，如果是，转到步骤3，如果不是，返回错误。 
用select在指定的超时时间内监听套接字的写就绪事件，如果select有监听到，证明连接成功，否则连接失败。*/ 


int main(int argc, char *argv[])
{
//最好检查一下参数，要求传入3个参数 URL PORT TIMEOUT(connect && send && recv 3个参数的超时)
        int fd, retval,res,error;
        struct sockaddr_in addr;
        struct timeval timeo = {15, 0}; //time ou struct
        struct hostent *site;
        socklen_t len = sizeof(timeo);
        fd_set set;
        fd = socket(AF_INET, SOCK_STREAM, 0);
        if (argc == 4)
                timeo.tv_sec = atoi(argv[3]);
        site=gngethostbyname(argv[1],3);  //解析域名的超时设置,测试域名超时，可以写一个可以ping的通但是没有办法解析域名
        //的IP地址到resolv.conf里面，然后加上一个默认路由，直接PING一个百度，就能发现如果不加超时机制就会一直卡在那里
        if(NULL == site)
{
printf("\ncan not find the site!\n");
     return -2;
}
        fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK); //设置为非阻塞模式
        addr.sin_family = AF_INET;
        //addr.sin_addr.s_addr = inet_addr(argv[1]);
        memcpy(&addr.sin_addr, site->h_addr_list[0], site->h_length);
        addr.sin_port = htons(atoi(argv[2]));
        printf("%d\n", time(NULL));
        /*if (connect(fd, (struct sockaddr*)&addr, sizeof(addr)) == 0) {
                printf("connected1\n");
               // return 0;
        }*/
        //res=connect(fd, (struct sockaddr*)&addr, sizeof(addr));
        //printf("\nconnect result:[%d]\n",res);
        if (connect(fd, (struct sockaddr*)&addr, sizeof(addr)) != 0)
        {
         //调用一次系统函数失败后直接看errno,确定是什么问题，下面的代码可以实现在没有默认路由的情况下直接返回失败.
         if (errno != EINPROGRESS) { 
                printf("connect:normal network unreach!!");
                return -1;
            }
         printf("\nwill select\n");
        FD_ZERO(&set);/*将set清零使集合中不含任何fd*/ 
        FD_SET(fd,&set); /*将一个给定的文件描述符加入集合之中*/ 
        retval = select(fd + 1, NULL, &set, NULL, &timeo);
        if (retval == -1) {
                printf("select");
                return -1;
        } else if(retval == 0) {
                printf("timeout\n"); //这样的select等于是变成了再timeout时间内是阻塞模式，超过timeout就直接返回
                printf("%d\n", time(NULL));
                return 0;
        }
        else
        {
         printf("connected--->:[%d]\n",retval);
         getsockopt(fd, SOL_SOCKET, SO_ERROR, &error, (socklen_t *)&len); //判断在connected成功之后，获取套接口目前的一些信息来判断是否真的是连接上了，返回0表示真的连上了
         printf("error--->:[%d]\n",error);
        
         if(0!=error)
         return -1;
        }
        }
        
        int ul = 0;
ioctl(fd, FIONBIO, &ul); //设置为阻塞模式
        //return 0;
        setsockopt(fd,SOL_SOCKET,SO_SNDTIMEO,(char *)&timeo,sizeof(timeo));
      setsockopt(fd,SOL_SOCKET,SO_RCVTIMEO,(char *)&timeo,sizeof(timeo));
      printf("\nbefore\n");
      sleep(5); //在sleep 5的时候，拔掉网线就可以测试出recv超时的功能，如果不加recv 的超时功能，拔掉网线后就会一直卡在那里，当然你在实际应用的时候没必要加这个
      printf("\nafter\n");
        char *msg="GET / HTTP/1.0\r\n\r\n";
if( send(fd, msg, strlen(msg), 0)<0 )
{
   printf("error in send msg\n");
   exit(1);
}
int i=0;
char buf[1000];

   while((recv(fd,buf,1000,MSG_WAITALL))>0)
   {
   printf("[%d]:[%s]",i,buf);
   i++;
   }
printf("\n------end---------\n");
close(fd);
return;
}



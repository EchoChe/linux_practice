#include <stdio.h>
#include <winsock.h>
#include <string.h>
#include <iostream.h>
#include <fstream>
using namespace std;
#pragma comment(lib,"ws2_32.lib");

void geturl(char *url) 
{ 
WSADATA WSAData={0}; 
SOCKET sockfd; 
struct sockaddr_in addr; 
struct hostent *pURL; 
char myurl[BUFSIZ]; 
char *pHost = 0, *pGET = 0; 
char host[BUFSIZ], GET[BUFSIZ]; 
char header[BUFSIZ] = ""; 
static char text[BUFSIZ]; 
int i; 
/* 
 * windows下使用socket必须用WSAStartup初始化，否则不能调用 
 */ 
if(WSAStartup(MAKEWORD(2,2), &WSAData)) 
{ 
printf("WSA failed\n"); 
return; 
} 
 
strcpy(myurl, url); 
for (pHost = myurl; *pHost != '/' && *pHost != '\0'; ++pHost); 
if ( (int)(pHost - myurl) == strlen(myurl) ) 
strcpy(GET, "/"); 
else 
strcpy(GET, pHost); 
*pHost = '\0'; 
strcpy(host, myurl); 
printf("%s\n%s\n", host, GET); 

sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP); 
pURL = gethostbyname(host); 
addr.sin_family = AF_INET; 
addr.sin_addr.s_addr = *((unsigned long*)pURL->h_addr); 
addr.sin_port = htons(80); 
strcat(header, "GET "); 
strcat(header, GET); 
strcat(header, " HTTP/1.1\r\n"); 
strcat(header, "HOST: "); 
strcat(header, host); 
strcat(header, "\r\nConnection: Close\r\n\r\n"); 
connect(sockfd,(SOCKADDR *)&addr,sizeof(addr)); 
send(sockfd, header, strlen(header), 0); 
ofstream fout("savefile.txt");
while ( recv(sockfd, text, BUFSIZ, 0) > 0) 
{ 
fout<<text;
cout<<text;
strnset(text, '\0', BUFSIZ); 
} 
closesocket(sockfd); 
WSACleanup(); 
} 
int main() 
{ 
char url[2560];  
while(scanf("%s", url))
geturl(url); 
return 0; 
} 

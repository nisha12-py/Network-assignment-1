#include<sys/types.h>
#include<sys/shm.h>
#include<fcntl.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#define PORT 8000
#define MAXSZ 100
int main()
{
int sockfd;
int newsockfd;
pid_t chilpd;
struct sockaddr_in serverAddress;
struct sockaddr_in clientAddress;
int n;
char msg[MAXSZ];
int clientAddressLength;
sockfd=socket(AF_INET, SOCK_STREAM, 0);
memset(&serverAddress,0,sizeof(serverAddress));
serverAddress.sin_family=AF_INET;
serverAddress.sin_addr.s_addr=htonl(INADDR_ANY);
serverAddress.sin_port=htons(PORT);
bind(sockfd, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
listen(sockfd, 5);
while(1)
{
printf("\n server waiting for new client connection.\n");
clientAddressLength=sizeof(clientAddress);
newsockfd=accept(sockfd,(struct sockaddr*)&clientAddress, &clientAddressLength);
while(1)
{
n=recv(newsockfd, msg, MAXSZ, 0);
if(n==0)
{
close(newsockfd);
break;
}
msg[n]=0;
send(newsockfd, msg, n, 0);
printf("recieved and set:%s\n",msg);
}
}
return 0;
}


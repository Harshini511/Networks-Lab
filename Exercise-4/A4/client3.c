//Server broadcast arp packet to all clients and client modifies the packet and returns
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include<ctype.h>
#include <string.h>
#include <sys/socket.h>
#define MAX 500
#define PORT 8081
#define SA struct sockaddr 
struct arp
{
	char source_ip[100];
	char dest_ip[100];
	char source_mac[100];
	char dest_mac[100];
	int flag;
};

int main(int argc, char *argv[])
{
	struct arp ac;
	if( argc >= 2 )
    {
       strcpy(ac.source_ip,argv[1]);
	   strcpy(ac.source_mac,argv[2]); 
    }
    printf("Source ip: %s\nSource mac: %s\n",ac.source_ip,ac.source_mac);
	int sockfd, connfd;
	struct sockaddr_in servaddr, cli;
	char buff[MAX];
	struct arp a;
	int n;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) 
	{ 
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr))!= 0) 
	{
		printf("connection with the server failed...\n");
		exit(0);
	}
	else
		printf("connected to the server..\n");
	while(1)
	{
		read(sockfd,&a,sizeof(a));
		printf("From server:\ndest ip: %s\nsource ip: %s\nSource mac: %s\nFlag: %d",a.dest_ip,a.source_ip,a.source_mac,a.flag);
		if(strcmp(a.dest_ip,ac.source_ip)==0)
		{
			strcpy(ac.dest_ip,a.source_ip);
			strcpy(ac.dest_mac,a.source_mac);
			ac.flag=1;
			write(sockfd,"yes",sizeof("yes"));
			send(sockfd,&ac,sizeof(ac),0);
		}
		else
			 write(sockfd,"no",sizeof("no"));
		break;
	}
	close(sockfd);
} 

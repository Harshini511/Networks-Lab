//Server broadcast arp packet to all clients
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

int main()
{
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
		printf("From server:\ndest ip: %s\nsource ip: %s\nSource mac:%s\nFlag: %d\n",a.dest_ip,a.source_ip,a.source_mac,a.flag);
		break;
	}
	close(sockfd);
} 

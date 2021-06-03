//Chat between client and server with date/time request to server by client
#include <stdio.h>
#include<ctype.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include<time.h>
#define MAX 500
#define PORT 8081
#define SA struct sockaddr 
int main()
{
	int sockfd, connfd, len,alp=0,num=0,vow=0,other=0;
	struct sockaddr_in servaddr, cli;
	char buff[MAX];
	int n;
	time_t t=time(NULL);
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
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) !=0)
	{
		printf("socket bind failed...\n");
		exit(0); 
	}
	else
		printf("Socket successfully binded..\n");
	if ((listen(sockfd, 5)) != 0) 
	{
		printf("Listen failed...\n");
		exit(0);
	}
	else
		printf("Server listening..\n");
	len = sizeof(cli); 
	connfd = accept(sockfd, (SA*)&cli, &len);
	if (connfd < 0) 
	{
		printf("server acccept failed...\n");
		exit(0);
	}
	else
		printf("server acccept the client...\n");
	bzero(buff, MAX); 
	printf("\nSend \"exit\" to end conversation\n");
	while(1)
	{
		n = 0;
		read(connfd, buff, sizeof(buff));
		printf("From client: %s", buff);
		if(strncmp(buff,"exit",4)==0)
			break;
		else if(strncmp(buff,"date",4)==0)
		{
			bzero(buff, MAX);
			snprintf(buff,sizeof(buff),"%s",ctime(&t));
			printf("To client: %s",buff);
			write(connfd, buff, sizeof(buff));
		}
		else
		{
			bzero(buff, MAX);
			printf("To client: ");
			while ((buff[n++] = getchar()) != '\n');
			if(strncmp(buff,"exit",4)==0)
			{
			write(connfd, buff, sizeof(buff));
			break;
			}
			write(connfd, buff, sizeof(buff));
		}
		bzero(buff, MAX); 
	}
	close(sockfd);
	
	
} 
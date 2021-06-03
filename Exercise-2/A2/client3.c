//Chat between client and server with file request to client by server
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include<ctype.h>
#include <string.h>
#include <sys/socket.h>
#define MAX 500
#define PORT 8081
#define SA struct sockaddr 
int main()
{
	int sockfd, connfd;
	struct sockaddr_in servaddr, cli;
	char buff[MAX];
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
	bzero(buff, sizeof(buff));
	int flag=0;
	FILE *p;
	printf("\nSend \"exit\" to end conversation\n");
	while(1)
	{
		n = 0;
		
		if(flag==0)
		{
			printf("To server : ");
			while ((buff[n++] = getchar()) != '\n');
		}
		else if(flag==1)
		{
			p = popen("ls","r");  
    		if( p != NULL)
    		{
        		while((buff[n++]=fgetc(p)) != EOF);
        		printf("To server : Files sent\n");
    		}
			flag=0;	
		}
		if(strncmp(buff,"exit",4)==0)
		{
			write(sockfd, buff, sizeof(buff));
			break;
		}
		write(sockfd, buff, sizeof(buff));
		bzero(buff, sizeof(buff));
		read(sockfd, buff, sizeof(buff));
		if(strncmp(buff,"exit",4)==0)
			break;
		printf("From server: %s", buff);
		if(strncmp(buff,"file",4)==0)
		{
			flag=1;
		}
		bzero(buff, sizeof(buff));
	}
	close(sockfd);
} 

//client program that gets filename to be sent to google server through command line
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
typedef struct ip_port{
	char ip[32];
	int port;
};
char *strip_parts(char* web,char* part)
{
	if(strncmp(part,"last",4)==0)
	{
		int l=strlen(web),i,j=0;
		printf("\n%s",web);
		for(i=l-1;i>=0;i--)
		{
			if(strncmp(&web[i],".",1) == 0)
				break;	
		}
		i++;
		char *temp=(char*)malloc(20*sizeof(char));
		while(i<l)
		{
			temp[j]=web[i];
			i++;
			j++;
		}
		return temp;
	}
	else
	{
		int l=strlen(web),i,j=0;
		printf("\n%s",web);
		for(i=0;i<l;i++)
		{
			if(strncmp(&web[i],".",1) == 0)
				break;	
		}
		i++;
		char *temp=(char*)malloc(20*sizeof(char));
		while(strncmp(&web[i],".",1) != 0)
		{
			temp[j]=web[i];
			i++;
			j++;
		}
		return temp;
	}
}

int main(int argc, char *argv[])
{
	char f[20];
	if( argc >= 2 )
    {
        strcpy(f,argv[1]);
    }
	int clientSocket, portNum, nBytes;
	char buffer[1024];
    struct sockaddr_in serverAddr;
    socklen_t addr_size;
    printf("\nConnection with root server");
	clientSocket = socket(PF_INET, SOCK_DGRAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(7891);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  
    addr_size = sizeof serverAddr;
    struct ip_port t[5];
    int p=6500;
    for(int i=0;i<6;i++)
    {
    	sprintf(t[i].ip,"%d.%d.%d.%d",i,i+1,i+2,i+3);
    	t[i].port=p+i;			
	}
	char domain[100];
	strcpy(domain,"www.google.com");
	strcpy(buffer,strip_parts(domain,"last"));
	printf("\nTo root server:%s",buffer);
    nBytes = strlen(buffer) + 1;
    /*Send message to root server*/
    sendto(clientSocket,buffer,nBytes,0,(struct sockaddr *)&serverAddr,addr_size);
    /*Receive message from root server*/
    nBytes = recvfrom(clientSocket,buffer,1024,0,NULL, NULL);
	printf("\nFrom root server: %s",buffer);
	int port;
	for(int i=0;i<6;i++)
    {
    	if(strcmp(buffer,t[i].ip)==0)
			{
			printf("\nCorresponding port of IP %s: %d",t[i].ip,t[i].port);
			port=t[i].port;
			}
	}
	printf("\n\nConnection with tld server");
	serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  
    addr_size = sizeof serverAddr;
    strcpy(buffer,strip_parts(domain,"middle"));
	printf("\nTo tld server:%s",buffer);
    nBytes = strlen(buffer) + 1;
    /*Send message to tld server*/
    sendto(clientSocket,buffer,nBytes,0,(struct sockaddr *)&serverAddr,addr_size);
	/*Receive message from tld server*/
    nBytes = recvfrom(clientSocket,buffer,1024,0,NULL, NULL);
	printf("\nFrom tld server: %s",buffer);
	for(int i=0;i<6;i++)
    {
    	if(strcmp(buffer,t[i].ip)==0)
			{
			printf("\nCorresponding port of IP %s: %d",t[i].ip,t[i].port);
			port=t[i].port;
			}
	}
	printf("\n\nConnection with google server");
	serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  
    addr_size = sizeof serverAddr;
    printf("File Name: %s",f);
    strcpy(buffer,f);
	nBytes = strlen(buffer) + 1;
    /*Send message to google server*/
    sendto(clientSocket,buffer,nBytes,0,(struct sockaddr *)&serverAddr,addr_size);
    /*Receive message from tld server*/
	nBytes = recvfrom(clientSocket,buffer,1024,0,NULL, NULL);
	printf("\nFrom google server (file contents):\n%s\n",buffer);
    return 0;
}

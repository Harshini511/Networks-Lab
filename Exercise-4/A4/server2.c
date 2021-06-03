//Server broadcast arp packet to all clients
#include <stdio.h>  
#include <string.h>   
#include <stdlib.h>  
#include <errno.h>  
#include <unistd.h>  
#include <arpa/inet.h>   
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <sys/time.h>  
#define PORT 8081  
#define max 500
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
    int opt=1;   
    int sockfd ,len , new_socket , client[5] ,max_clients =5, activity, valread ,n, sd,flag=0;   
    int max_sd;   
    struct sockaddr_in servaddr,cli; 
	struct arp a;
	strcpy(a.source_ip,"1.2.3.4");
	strcpy(a.dest_ip,"2.3.4.5");
	strcpy(a.source_mac,"1.2.3.0");
	a.flag=0; 
    char buffer[max]; 
    fd_set readfds;   
    for (int i = 0; i < max_clients; i++)   
    {   
        client[i] = 0;   
    }   
    sockfd = socket(AF_INET , SOCK_STREAM , 0);
    if (sockfd == -1) 
	{
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");  
    if( setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,sizeof(opt)) < 0 )   
    {   
        printf("Multiple connections failed....\n");  
    }  
	else
		printf("Multiple connections succeeded....\n"); 
    servaddr.sin_family = AF_INET;   
    servaddr.sin_addr.s_addr = INADDR_ANY;   
    servaddr.sin_port = htons( PORT );   
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) !=0)
	{
		printf("socket bind failed...\n");
		exit(0); 
	}
	else
		printf("Socket successfully binded..\n");
	 
    if ((listen(sockfd,2)) != 0) 
	{
		printf("Listen failed...\n");
		exit(0);
	}
	else
		printf("Server listening..\n");
	len = sizeof(servaddr);   
    puts("Waiting for connections ...");
    sleep(10);
	bzero(buffer,sizeof(buffer));   
    while(1)   
    {   
        FD_ZERO(&readfds);   
     	FD_SET(sockfd, &readfds);   
        max_sd = sockfd;   
        for ( int i = 0 ; i < max_clients ; i++)   
        {   
            sd = client[i];   
            if(sd > 0)   
                FD_SET( sd , &readfds);   
            if(sd > max_sd)   
                max_sd = sd;   
        }   
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);   
        if ((activity < 0) && (errno!=EINTR))   
        {   
            printf("select error");   
        }   
        if (FD_ISSET(sockfd, &readfds))   
        {   
            if ((new_socket = accept(sockfd,(struct sockaddr *)&servaddr, (socklen_t*)&len))<0)   
            {   
                perror("accept");   
                exit(EXIT_FAILURE);   
            }   
            for (int i = 0; i < max_clients; i++)   
            {   
                if( client[i] == 0 )   
                {   
                    client[i] = new_socket;   
                    break;   
                }   
            }   
        }   
        for (int i=0; i < max_clients; i++)   
        {   
            sd = client[i];   
            send(sd,&a,sizeof(a) , 0 ); 
					flag=1;  
        } 
    }   
         
    return 0;   
}   

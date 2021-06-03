#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
typedef struct table{
	char map[20];
	char ip[20];
};
int main(){
	int udpSocket, nBytes;
    char buffer[1024];
    struct sockaddr_in serverAddr, clientAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size, client_addr_size;
    int i;
    udpSocket = socket(PF_INET, SOCK_DGRAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(6501);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  
    bind(udpSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
    addr_size = sizeof serverStorage;
 	struct table t[3];
 	strcpy(t[0].map,"yahoo");
 	strcpy(t[0].ip,"1.1.1.1");
 	
 	strcpy(t[1].map,"google");
 	strcpy(t[1].ip,"2.3.4.5");
 	
 	strcpy(t[2].map,"gmail");
 	strcpy(t[2].ip,"1.1.5.1");
 
    nBytes = recvfrom(udpSocket,buffer,1024,0,(struct sockaddr *)&serverStorage, &addr_size);
    printf("\nFrom client: %s",buffer);
    int temp=0;
	/*Map corresponding ip*/
	for(int i=0;i<3;i++)
    {
    	if(strcmp(t[i].map,buffer)==0)
    	{
    		temp=i;
		}
	}
	strcpy(buffer,t[temp].ip);
	printf("\nTo client:%s\n",buffer);
    nBytes = strlen(buffer) + 1;
    sendto(udpSocket,buffer,nBytes,0,(struct sockaddr *)&serverStorage,addr_size);
    return 0;
}

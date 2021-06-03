#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <unistd.h> 
int main(){
	int udpSocket, nBytes;
    char buffer[1024];
    struct sockaddr_in serverAddr, clientAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size, client_addr_size;
    int i;
    udpSocket = socket(PF_INET, SOCK_DGRAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(6502);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  
    bind(udpSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)); 
    addr_size = sizeof serverStorage;
    nBytes = recvfrom(udpSocket,buffer,1024,0,(struct sockaddr *)&serverStorage, &addr_size);
    printf("\nFrom client: %s",buffer);
    char temp[50];
    FILE *fp = fopen(buffer, "r"); 
    printf("\nFile Name Received: %s\n", buffer); 
    if (fp == NULL) 
        printf("\nFile open failed!\n"); 
    else
        printf("\nFile Successfully opened!\n"); 
    i=0;
    char ch;
	fscanf(fp, "%[^-1]", temp);
    fclose(fp);
    strcpy(buffer,temp);
    nBytes = strlen(buffer) + 1;
	sendto(udpSocket,buffer,nBytes,0,(struct sockaddr *)&serverStorage,addr_size);
  	printf("\nFILE SENT\n");  
    return 0;
}

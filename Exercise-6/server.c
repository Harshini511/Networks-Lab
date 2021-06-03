#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
int power(int x,int y)
{
	int i,j=1;
	for(i=0;i<y;i++)
	{
		j=j*x;
	}
	return j;
}
int pow_2(int x)
{
	int i,j;
	for(i=0;i<x;i++)
	{
		if(x==power(2,i))
			return 0;
	}
	return 1;
}

int main(){
	int udpSocket, nBytes;
    char buffer[1024];
    struct sockaddr_in serverAddr, clientAddr;
    struct sockaddr_storage serverStorage;
    socklen_t addr_size, client_addr_size;
    int i;
    udpSocket = socket(PF_INET, SOCK_DGRAM, 0);
	serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(7891);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  
	bind(udpSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
    addr_size = sizeof serverStorage;
 	nBytes = recvfrom(udpSocket,buffer,1024,0,(struct sockaddr *)&serverStorage, &addr_size);
    printf("\nFrom client:%s",buffer);
    int l=strlen(buffer);
    int arr[20];
    for(int i=1;i<l+1;i++)
    {
    	arr[i]=buffer[i]-'0';
	}
	//Finds number of redundancy bits
    for(i=0;i<10;i++)
	{
		if((power(2,i)>(l+i+1)) || (power(2,i)==(l+i+1)))
		{
			break;
		}
	}
	int r=i;
	int rb,sum=0,temp;
	i=1;
	//Finds the error bit 
	while(i<l)
	{
		rb=0;
		if(pow_2(i)==0)
		{
			temp=i;
			while(temp<l)
			{
				for(int j=0;j<i;j++)
					if(temp+j<l)
						rb=rb^arr[temp+j];
				temp=temp+(i*2);	
			}
			sum=sum+(i*rb);
						
		}
		i++;
	}
	printf("\nThe bit in position %d has error\n",sum);
  
  return 0;
}

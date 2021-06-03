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
int main()
{
	int n;
	int clientSocket, portNum, nBytes;
	char buffer[1024];
    struct sockaddr_in serverAddr;
    socklen_t addr_size;
    printf("\nConnection with server");
	clientSocket = socket(PF_INET, SOCK_DGRAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(7891);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  
    addr_size = sizeof serverAddr;
    printf("\nEnter the length of message bit: ");
    scanf("%d",&n);
    int i;
    //Finds the number of redundancy bits
	for(i=0;i<10;i++)
	{
		if((power(2,i)>(n+i+1)) || (power(2,i)==(n+i+1)))
		{
			break;
		}
	}
	int r=i;
	printf("\nRedundancy bits:%d\nMessage size:%d",r,n);
	int arr[n+r+1],a[n+r+1];
    printf("\nEnter the message bits one by one\n");
    for(i=1;i<n+1;i++)
    {
    	scanf("%d",&a[i]);
	}
	int j=1;
	i=n;
	//Generate the entire sequence
    while(j<n+r+1)
    {
    	if(pow_2(j)!=0)
		{
			arr[j]=a[i];
			i--;
		}
		else
			arr[j]=0;
		j++;
	}
	int temp=0,rb;
	i=1;
	//Generate and assign redundancy bits
	while(i<n+r+1)
	{
		rb=0;
		if(pow_2(i)==0)
		{
			temp=i;
			while(temp<n+r+1)
			{
				for(int j=0;j<i;j++)
					if(temp+j<n+r+1)
						rb=rb^arr[temp+j];
				temp=temp+(i*2);	
			}
			arr[i]=rb;
			
		}
		i++;
	}
	int flag=0;
	printf("\nShould any bit be changed before sending the message to the server?\nEnter the position to be changed if yes, else enter 0: ");
	scanf("%d",&flag);
	if(flag!=0)
	{
		arr[flag]=arr[flag]^1;
	}
	//Convert integer to character array
    for(int k=1;k<n+r+1;k++)
    {
    	buffer[k]=arr[k]+'0';
	}
	printf("\nTo Server:%s\n",buffer);
    nBytes = strlen(buffer) + 1;
    sendto(clientSocket,buffer,nBytes,0,(struct sockaddr *)&serverAddr,addr_size);
    return 0;
}

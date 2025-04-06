#include<stdio.h>
#include<arpa/inet.h>
#include<string.h>

#define PORT 12345


int main(){
    int sock=socket(AF_INET,SOCK_DGRAM,0);

    struct sockaddr_in sa= {
        .sin_family=AF_INET,
        .sin_port=htons(PORT),
        .sin_addr.s_addr= inet_addr("127.0.0.1")

    };

sendto(sock,"HELLO FROM CLIENT",17,0,(struct sockaddr*)&sa,sizeof(sa));
printf("message sent to server\n");

char b[100];
recvfrom(sock,b,100,0,0,0);
printf("Message from server: %s",b);
return 0;
}
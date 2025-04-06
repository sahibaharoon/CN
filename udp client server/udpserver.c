#include<stdio.h>
#include<arpa/inet.h>
#include<string.h>

#define PORT 12345

int main(){
    int sock= socket(AF_INET,SOCK_DGRAM,0);

    struct sockaddr_in sa= {
        .sin_family=AF_INET,
        .sin_port=htons(PORT),
        .sin_addr.s_addr= INADDR_ANY

    };
    bind(sock,(struct sockaddr*)&sa,sizeof(sa));
    printf("server is ready and running.\n");

    struct sockaddr_in ca;
    socklen_t clen=sizeof(ca);
    char buffer[100];
    recvfrom(sock,buffer,100,0,(struct sockaddr*)&ca,&clen);
    printf("Message from client: %s",buffer);

    sendto(sock,"HELLO FROM SERVER",17,0,(struct sockaddr*)&ca,clen);
    printf("\nmessage sent to client\n");
    return 0;
}
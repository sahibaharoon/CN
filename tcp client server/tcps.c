#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>

#define PORT 8080


int main(){


    int s= socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in sa={
        .sin_family= AF_INET,
        .sin_port=htons(PORT),
        .sin_addr.s_addr=INADDR_ANY
    };
    bind(s,(struct addr*)&sa,sizeof(sa));
    listen(s,3);
    printf("SERVER RUNNING AND READY.\n");
    int c=accept(s,0,0);

    send(c,"HELLO FROM SERVER",17,0);
    printf("\nMessage sent to client");
    char b[100];
    read(c,b,100);
    printf("\nMessage from client:%s\n",b);


    return 0;
}
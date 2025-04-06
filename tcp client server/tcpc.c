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
        .sin_addr.s_addr=inet_addr("127.0.0.1")
    };
    connect(s,(struct sockaddr*)&sa,sizeof(sa));
    char buff[100];
    read(s,buff,100);
    printf("\nMessage from server:%s\n",buff);
    send(s,"HELLO FROM CLIENT",17,0);
    printf("\nMessage sent to server");
    return 0;
}
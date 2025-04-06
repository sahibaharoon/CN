#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<arpa/inet.h>
#include<string.h>
#include<unistd.h>

#define port 8080

int main(){
    int s=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in sa={
        .sin_family=AF_INET,
        .sin_port=htons(port),
        .sin_addr.s_addr=INADDR_ANY
    };
    bind(s,(struct sockaddr*)&sa,sizeof(sa));
    listen(s,3);
    printf("server ready and running...\n");

    int c= accept(s,0,0);
    char fname[10];
    recv(c,fname,10,0);

    printf("Client requested file %s.\n",fname);
    FILE *f =fopen(fname,"r");
    if(!f){
        send(c,"FILE NOT FOUND",15,0);
        printf("File not found.\n");
    }else{
        printf("File content sent.\n");
        char buffer[1024];
        int bytes;
        send(c,"FILE CONTENT:",13,0);
        while((bytes=fread(buffer,1,sizeof(buffer),f))>0){
            send(c,buffer,bytes,0);
        }
        fclose(f);
    }

    return 0;
}
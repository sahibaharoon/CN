#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <time.h>
#include<unistd.h>
#include<string.h>

#define PORT 8080


int main() {
    int s = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in sa = {.sin_family=AF_INET, .sin_port=htons(PORT), .sin_addr.s_addr=INADDR_ANY};
    bind(s, (struct sockaddr*)&sa, sizeof(sa));
    listen(s, 3);
    
    printf("Waiting...\n");
    int c = accept(s, 0, 0);
    printf("Connected.\n");

    char buf[16];
    srand(time(0));

    while (read(c, buf, 16) > 0) {
        int p = atoi(buf);
        printf("Received packet %d\n", p);
    
        if (rand() % 100 < 70) {
            sleep(1);
            printf("ACK for %d sent\n\n", p);
            char ack[16];
            sprintf(ack,"%d",p);
            send(c,ack,strlen(ack)+1,0);
        } else {
            printf("ACK for %d lost!\n\n", p);
        }
    }
    close(c);
    close(s);
}
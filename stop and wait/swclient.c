#include <stdio.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include<unistd.h>

int main() {
    int s = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in sa = {.sin_family=AF_INET, .sin_port=htons(8080), .sin_addr.s_addr=inet_addr("127.0.0.1")};
    connect(s, (struct sockaddr*)&sa, sizeof(sa));

    struct timeval tv = {3, 0};
    setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    char b[16];
    for (int p = 1; p <= 5; ) {
        printf("Sending %d...", p);
        //dprintf(sock,which format u need,what to store)
        dprintf(s, "%d", p);

        if (read(s, b, 16) > 0) {
            printf(" ACK  for %d received\n",p);
            p++;
        } else printf(" Timeout - retrying\n");
    }
    close(s);
}
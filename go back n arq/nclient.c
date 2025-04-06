#include <stdio.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include<unistd.h>
#include <stdlib.h>

#define PORT 8080
#define WINDOW 4
#define TOTAL 10
#define TIMEOUT 3

int main() {
    int s = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in sa = {.sin_family=AF_INET, .sin_port=htons(PORT)};
    inet_pton(AF_INET, "127.0.0.1", &sa.sin_addr);
    connect(s, (struct sockaddr*)&sa, sizeof(sa));
    printf("Connected.\n");

    struct timeval tv = {TIMEOUT, 0};
    setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));

    int base = 0, next = 1, acked = 0;
    char buf[16];

    while (acked < TOTAL) {
        // Send window
        while (next < base + WINDOW && next <= TOTAL) {
            printf("Sending %d\n", next);
            dprintf(s, "%d\n", next);
            next++;
        }

        // Wait for ACK
        if (read(s, buf, 16) > 0) {
            acked = atoi(buf);
            printf("ACK %d\n", acked);
            if (acked == base) base++;
        } else {
            printf("Timeout! Retry from %d\n", base);
            next = base;
        }
    }
    printf("All sent.\n");
    close(s);
}
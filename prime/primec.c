#include <stdio.h>
#include <arpa/inet.h>
#include<string.h>
#include <unistd.h> 

int main() {
    // Connect to server
    int s = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in sa = {.sin_family=AF_INET, .sin_port=htons(8080), .sin_addr.s_addr=inet_addr("127.0.0.1")};
    connect(s, (struct sockaddr*)&sa, sizeof(sa));

    // Send number and get response
    char n[100], r[100];
    printf("Enter number: "); scanf("%s", n);
    send(s, n, strlen(n), 0);
    read(s, r, 100);
    printf("Server: %s\n", r);
}
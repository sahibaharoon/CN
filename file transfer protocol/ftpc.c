#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include<string.h>
#define PORT 8080

int main() {
    int s = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in sa = {
        .sin_family = AF_INET,
        .sin_port = htons(PORT),
        .sin_addr.s_addr = inet_addr("127.0.0.1")
    };
    
    connect(s, (struct sockaddr*)&sa, sizeof(sa));
    
    printf("Enter filename: ");
    char fname[256];
    scanf("%s", fname);
    send(s, fname, strlen(fname), 0);
    
    char buf[1024];
    int bytes;
    while ((bytes = recv(s, buf, 1024, 0)) > 0) {
        fwrite(buf, 1, bytes, stdout); // Proper binary output
    }
    
    close(s);
    return 0;
}
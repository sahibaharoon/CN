/* UDP TIME SERVER (minimal) */
#include <stdio.h>
#include <time.h>
#include <arpa/inet.h>
#include <string.h> // For strlen()

#define PORT 12345

int main() {
    // 1. Create UDP socket
    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    // 2. Bind socket to port (INADDR_ANY = listen on all network interfaces)
    struct sockaddr_in server_addr = {
        .sin_family = AF_INET,
        .sin_port = htons(PORT),
        .sin_addr.s_addr = INADDR_ANY
    };
    bind(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));

    printf("server running and waiting time req\n");
    while(1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        
        // 3. Wait for incoming datagram (buffer, max size, flags=0, store client info)
        char request[10];
        recvfrom(sock, request, sizeof(request), 0, 
                (struct sockaddr*)&client_addr, &client_len);
        printf("time req received\n");
        // 4. Send back current time (ctime() adds newline)
        time_t now = time(NULL);
        char *times=ctime(&now);
        sendto(sock,times,strlen(times), 0, 
              (struct sockaddr*)&client_addr, client_len);
        printf("Time sent to client: %s",times);
    }
}
/* UDP TIME CLIENT (minimal) */
#include <stdio.h>
#include <arpa/inet.h> // For sockaddr_in, htons(), inet_addr()

#define PORT 12345

int main() {
    // 1. Create UDP socket (AF_INET=IPv4, SOCK_DGRAM=UDP, 0=auto protocol)
    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    // 2. Configure server address struct
    struct sockaddr_in server_addr = {
        .sin_family = AF_INET,          // IPv4
        .sin_port = htons(PORT),        // Port in network byte order
        .sin_addr.s_addr = inet_addr("127.0.0.1") // Localhost IP
    };

    // 3. Send time request (no need for null terminator - we specify length 4)
    sendto(sock, "TIME", 4, 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
    printf("Time request sent.\n");
    // 4. Receive response (buffer, max size, flags=0, no sender info needed)
    char time_str[100];
    recvfrom(sock, time_str, sizeof(time_str), 0, NULL, NULL);
    
    printf("Server time: %s", time_str);
} 
#include <stdio.h>
#include <arpa/inet.h>
#include<string.h>
#include <unistd.h> 

int is_prime(int n) { for(int i=2;i*i<=n;i++) if(n%i==0) return 0; return n>1; }

int main() {
    // Setup server socket
    int s = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in sa = {.sin_family=AF_INET, .sin_port=htons(8080), .sin_addr.s_addr=INADDR_ANY};
    bind(s, (struct sockaddr*)&sa, sizeof(sa));
    listen(s, 3);
    printf("Prime server ready on 8080...\n");

    // Handle client
    int c = accept(s, 0, 0);
    char buf[100]; int n;
    read(c, buf, 100);
    sscanf(buf, "%d", &n);
    sprintf(buf, "%d is%s prime", n, is_prime(n)?"":" not");
    send(c, buf, strlen(buf), 0);
    printf("Checked: %d\n", n);
}
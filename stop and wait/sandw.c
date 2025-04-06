#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <time.h>
#include<unistd.h>

#define timeout 3
#define total 5

int ack(){
    return rand()%100<70;
}

int main(){
    srand(time(0));
    for(int i=0;i<total;){
        printf("Sending %d packet..\n",i);
        sleep(1);
        if(ack()){
            printf("ACK for %d rec.\n",i++);
        }else{
            printf("ACK for %d lost..\n",i);
            sleep(timeout);
        }
    }

    printf("All packets sent !");
    return 0;
}
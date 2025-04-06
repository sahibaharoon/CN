#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/time.h>
#include<time.h>
#include<unistd.h>

#define max 10
#define window 4

void sr(){
    int base=0,acked[max]={0},sent[max]={0},retransmit[max]={0};
    while(base<max){
        //SENDING PACKET
        for(int i=base;i<base+window && i<max;i++){
            if(!sent[i] || retransmit[i]){
                if(retransmit[i]){
                    printf("Resending pakcet %d...\n",i);
                }else{
                    printf("Sending pakcet %d...\n",i);
                }
                sent[i]=1;
                retransmit[i]=0;
                sleep(1);
                
            }
        }
        //ACK PACKET
        for(int i=base;i<base+window&&i<max;i++){
            if(sent[i]&&!acked[i]){
                if(rand()%100<70){
                    printf("ACK for %d received...\n",i);
                    acked[i]=1;
                    sleep(1);
                }else{
                    printf("ACK for %d lost...\n",i);
                    retransmit[i]=1;
                }
            }

        }
        //SLIDING WINDOW
        while(acked[base] && base<max){
            printf("Window slides past %d\n",base);
            base++;
        }
    }

printf("ALL DONE");
}

int main(){
    srand(time(0));
    sr();
    return 0;
}
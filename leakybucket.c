#include <stdio.h>

void simulate_leaky_bucket(int capacity, int leak_rate, int num_packets, int packets[]) {
    int bucket = 0;
    int time = 1;
    
    printf("Time\tIncoming\tBucket\tLeaked\tRemaining\n");
    
    // Process all incoming packets
    for (int i = 0; i < num_packets; i++, time++) {
        // Add packet to bucket (handle overflow)
        bucket += packets[i];
        if (bucket > capacity) {
            int overflow = bucket - capacity;
            bucket = capacity;
            printf("%d\t%d\t%d (overflow %d)\t", time, packets[i], bucket, overflow);
        } else {
            printf("%d\t%d\t%d\t", time, packets[i], bucket);
        }
        
        // Leak packets at constant rate
        int leaked = (bucket > leak_rate) ? leak_rate : bucket;
        bucket -= leaked;
        printf("%d\t%d\n", leaked, bucket);
    }
    
    // Drain remaining packets in bucket
    while (bucket > 0) {
        int leaked = (bucket > leak_rate) ? leak_rate : bucket;
        bucket -= leaked;
        printf("%d\t0\t%d\t%d\t%d\n", time++, bucket + leaked, leaked, bucket);
    }
}

int main() {
    int capacity, leak_rate, num_packets;
    
    printf("Enter bucket capacity, leak rate, and packet count: ");
    scanf("%d %d %d", &capacity, &leak_rate, &num_packets);
    
    int packets[num_packets];
    printf("Enter %d packet sizes:\n", num_packets);
    for (int i = 0; i < num_packets; i++) {
        scanf("%d", &packets[i]);
    }
    
    printf("\nLeaky Bucket Simulation:\n");
    simulate_leaky_bucket(capacity, leak_rate, num_packets, packets);
    
    return 0;
}
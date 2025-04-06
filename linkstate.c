#include <stdio.h>


#define MAX 10
#define INF 9999

int cost[MAX][MAX], dist[MAX][MAX], next_hop[MAX][MAX];
int nodes;

void initialize() {
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            dist[i][j] = cost[i][j];
            next_hop[i][j] = j;  // Always point to next hop (DVR style)
        }
    }
}

void dijkstra() {
    for (int src = 0; src < nodes; src++) {
        int visited[MAX] = {0};
        dist[src][src] = 0;
        visited[src] = 1;

        for (int count = 0; count < nodes-1; count++) {
            // Find minimum distance node
            int min_node = -1;
            for (int i = 0; i < nodes; i++) {
                if (!visited[i] && (min_node == -1 || dist[src][i] < dist[src][min_node])) {
                    min_node = i;
                }
            }
            if (min_node == -1) break;

            visited[min_node] = 1;

            // Update neighbors (DVR-style next hop propagation)
            for (int i = 0; i < nodes; i++) {
                if (!visited[i] && cost[min_node][i] != INF) {
                    if (dist[src][i] > dist[src][min_node] + cost[min_node][i]) {
                        dist[src][i] = dist[src][min_node] + cost[min_node][i];
                        next_hop[src][i] = next_hop[src][min_node];  // Inherit next hop
                    }
                }
            }
        }
    }
}

void display() {
    for (int i = 0; i < nodes; i++) {
        printf("\nRouter %d's Routing Table:\n", i + 1);
        printf("Destination\tCost\tNext Hop\n");
        for (int j = 0; j < nodes; j++) {
            printf("%d\t\t", j + 1);
            if (dist[i][j] == INF) {
                printf("INF\t-\n");  // DVR-style unreachable marker
            } else {
                printf("%d\t%d\n", dist[i][j], next_hop[i][j] + 1);
            }
        }
    }
}

int main() {
    printf("Enter number of routers: ");
    scanf("%d", &nodes);

    printf("Enter cost matrix (0 for no link):\n");
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            scanf("%d", &cost[i][j]);
            if (cost[i][j] == 0 && i != j) {
                cost[i][j] = INF;
            }
        }
    }

    initialize();
    dijkstra();
    display();

    return 0;
}
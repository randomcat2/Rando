#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define WINDOW_SIZE 4
#define MAX_PACKETS 20

// Define a structure to represent packets
struct packet {
    int seq_num;
    char data[20];
};

int main() {
    int sockfd, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("Socket creation failed");
        exit(1);
    }

    // Initialize server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(12345);

    // Bind socket
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Binding failed");
        exit(1);
    }

    printf("Server listening on port 12345...\n");

    struct packet window[WINDOW_SIZE];
    int expected_seq_num = 0;

    while (1) {
        int num_packets_received = recvfrom(sockfd, &window[expected_seq_num % WINDOW_SIZE], sizeof(struct packet), 0, (struct sockaddr*)&client_addr, &client_len);

        if (num_packets_received == -1) {
            perror("Receive error");
            continue;
        }

        if (window[expected_seq_num % WINDOW_SIZE].seq_num == expected_seq_num) {
            printf("Received packet with sequence number %d: %s\n", expected_seq_num, window[expected_seq_num % WINDOW_SIZE].data);
            expected_seq_num++;
        } else {
            printf("Received out-of-order packet with sequence number %d. Ignoring...\n", window[expected_seq_num % WINDOW_SIZE].seq_num);
        }

        if (expected_seq_num >= MAX_PACKETS) {
            break;
        }
    }

    close(sockfd);
    return 0;
}

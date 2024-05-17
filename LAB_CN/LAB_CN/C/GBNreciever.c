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
    int sockfd;
    struct sockaddr_in server_addr;

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

    struct packet packets[MAX_PACKETS];
    int num_packets = MAX_PACKETS;

    // Fill packets with data and sequence numbers
    for (int i = 0; i < num_packets; i++) {
        packets[i].seq_num = i;
        snprintf(packets[i].data, sizeof(packets[i].data), "Packet %d", i);
    }

    int base = 0;
    int next_seq_num = 0;

    while (base < num_packets) {
        for (int i = base; i < next_seq_num + WINDOW_SIZE && i < num_packets; i++) {
            printf("Sending packet with sequence number %d: %s\n", packets[i].seq_num, packets[i].data);
            sendto(sockfd, &packets[i], sizeof(struct packet), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
        }

        // Receive acknowledgments
        for (int i = base; i < next_seq_num + WINDOW_SIZE && i < num_packets; i++) {
            struct packet ack_packet;
            recvfrom(sockfd, &ack_packet, sizeof(struct packet), 0, NULL, NULL);
            printf("Received acknowledgment for packet with sequence number %d\n", ack_packet.seq_num);
            base++;
        }
    }

    close(sockfd);
    return 0;
}

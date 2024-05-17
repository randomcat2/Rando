#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_BUFFER_SIZE 1024

int main() {
    int receiver_socket;
    struct sockaddr_in receiver_addr, sender_addr;

    if ((receiver_socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    receiver_addr.sin_family = AF_INET;
    receiver_addr.sin_port = htons(PORT);
    receiver_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(receiver_socket, (struct sockaddr *)&receiver_addr, sizeof(receiver_addr)) < 0) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    printf("Receiver waiting for packets...\n");

    char buffer[MAX_BUFFER_SIZE];
    int expected_sequence_number = 0;

    while (1) {
        socklen_t sender_addr_len = sizeof(sender_addr);

        // Receive a packet from the sender
        int received_bytes = recvfrom(receiver_socket, buffer, sizeof(buffer), 0, (struct sockaddr *)&sender_addr, &sender_addr_len);
        buffer[received_bytes] = '\0';

        printf("Received: %s\n", buffer);

        if (expected_sequence_number == (buffer[7] - '0')) {
            // If the received sequence number matches the expected sequence number, send an acknowledgment
            char ack[4] = "ACK";
            sendto(receiver_socket, ack, strlen(ack), 0, (struct sockaddr *)&sender_addr, sender_addr_len);
            printf("Sent ACK: %s\n", ack);

            expected_sequence_number = (expected_sequence_number + 1) % 2; // Toggle expected sequence number (0 or 1)
        }
    }

    close(receiver_socket);

    return 0;
}

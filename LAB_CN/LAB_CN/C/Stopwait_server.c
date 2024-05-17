#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_BUFFER_SIZE 1024

int main() {
    int sender_socket;
    struct sockaddr_in receiver_addr;

    if ((sender_socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    receiver_addr.sin_family = AF_INET;
    receiver_addr.sin_port = htons(PORT);
    receiver_addr.sin_addr.s_addr = INADDR_ANY;

    char message[MAX_BUFFER_SIZE];
    int sequence_number = 0;

    while (1) {
        snprintf(message, sizeof(message), "Packet %d", sequence_number);

        // Send the message to the receiver
        sendto(sender_socket, message, strlen(message), 0, (struct sockaddr *)&receiver_addr, sizeof(receiver_addr));

        printf("Sent: %s\n", message);

        // Wait for acknowledgment from the receiver
        char ack[MAX_BUFFER_SIZE];
        recvfrom(sender_socket, ack, sizeof(ack), 0, NULL, NULL);

        printf("Received ACK: %s\n", ack);

        sequence_number = (sequence_number + 1) % 2; // Toggle sequence number (0 or 1)
        sleep(1); // Simulate transmission delay
    }

    close(sender_socket);

    return 0;
}

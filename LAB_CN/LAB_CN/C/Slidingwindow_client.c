#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 8080
#define MAX_BUFFER_SIZE 1024
#define WINDOW_SIZE 8

int main() {
    int client_socket;
    struct sockaddr_in server_addr;

    if ((client_socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    srand(time(NULL));

    char buffer[MAX_BUFFER_SIZE];

    for (int i = 0; i < WINDOW_SIZE; i++) {
        snprintf(buffer, sizeof(buffer), "%d", i);

        // Send packets to the server
        sendto(client_socket, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
        printf("Sent: %d\n", i);
    }

    int expected_sequence_number = 0;

    while (1) {
        socklen_t server_addr_len = sizeof(server_addr);
        int received_bytes = recvfrom(client_socket, buffer, sizeof(buffer), 0, (struct sockaddr *)&server_addr, &server_addr_len);
        buffer[received_bytes] = '\0';

        int sequence_number = atoi(buffer);

        if (sequence_number == expected_sequence_number) {
            printf("Received ACK: %d\n", sequence_number);

            // Move the window
            expected_sequence_number = (expected_sequence_number + 1) % WINDOW_SIZE;

            // Send the next packet
            snprintf(buffer, sizeof(buffer), "%d", (expected_sequence_number + WINDOW_SIZE) % WINDOW_SIZE);
            sendto(client_socket, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
            printf("Sent: %d\n", (expected_sequence_number + WINDOW_SIZE) % WINDOW_SIZE);
        }
    }

    close(client_socket);

    return 0;
}

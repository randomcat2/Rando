#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_BUFFER_SIZE 1024

int main() {
    int server_socket;
    struct sockaddr_in server_addr, client_addr;

    if ((server_socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    char buffer[MAX_BUFFER_SIZE];
    int expected_sequence_number = 0;

    while (1) {
        socklen_t client_addr_len = sizeof(client_addr);
        int received_bytes = recvfrom(server_socket, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_addr, &client_addr_len);
        buffer[received_bytes] = '\0';

        // Simulate packet loss
        if (rand() % 10 < 3) {
            printf("Packet lost: %s\n", buffer);
            continue;
        }

        int sequence_number = atoi(buffer);

        if (sequence_number == expected_sequence_number) {
            printf("Received: %d\n", sequence_number);
            expected_sequence_number = (expected_sequence_number + 1) % 8; // Assuming a window size of 8
        }

        // Send acknowledgment back to the client
        snprintf(buffer, sizeof(buffer), "%d", sequence_number);
        sendto(server_socket, buffer, strlen(buffer), 0, (struct sockaddr *)&client_addr, client_addr_len);
    }

    close(server_socket);

    return 0;
}

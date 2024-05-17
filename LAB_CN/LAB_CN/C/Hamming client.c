#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <bitstream.h>

#define PORT 8080
#define MAX_BUFFER_SIZE 1024
#define DATA_BITS 4
#define PARITY_BITS 3

void encode_hamming74(uint8_t *data, uint8_t *encoded) {
    // Calculate parity bits
    encoded[2] = data[0] ^ data[1] ^ data[3];
    encoded[4] = data[0] ^ data[2] ^ data[3];
    encoded[5] = data[1] ^ data[2] ^ data[3];

    // Copy data and parity bits to the encoded message
    encoded[0] = data[0];
    encoded[1] = data[1];
    encoded[3] = data[2];
    encoded[6] = data[3];
}

int main() {
    int client_socket;
    struct sockaddr_in server_addr;

    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        perror("Invalid address / Address not supported");
        exit(EXIT_FAILURE);
    }

    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    char message[MAX_BUFFER_SIZE];
    int read_bytes;

    while (1) {
        printf("Enter a message to send (or 'exit' to quit): ");
        fgets(message, sizeof(message), stdin);

        if (strncmp(message, "exit", 4) == 0) {
            break;
        }

        // Hamming encoding
        uint8_t data[DATA_BITS];
        strncpy((char *)data, message, DATA_BITS);
        uint8_t encoded[DATA_BITS + PARITY_BITS];
        encode_hamming74(data, encoded);

        // Send the encoded message
        send(client_socket, encoded, sizeof(encoded), 0);

        int error;
        read_bytes = recv(client_socket, &error, sizeof(int), 0);
        if (read_bytes <= 0) {
            break;
        }

        if (error) {
            printf("Error detected in transmission.\n");
        } else {
            printf("Message sent successfully: %s", message);
        }
    }

    close(client_socket);

    return 0;
}

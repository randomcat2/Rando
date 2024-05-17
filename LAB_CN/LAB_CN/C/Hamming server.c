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
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Binding failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 5) < 0) {
        perror("Listening failed");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);

    if ((client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len)) < 0) {
        perror("Acceptance failed");
        exit(EXIT_FAILURE);
    }

    uint8_t buffer[MAX_BUFFER_SIZE];
    int read_bytes;

    while (1) {
        read_bytes = recv(client_socket, buffer, sizeof(buffer), 0);
        if (read_bytes <= 0) {
            break;
        }

        // Hamming decoding
        uint8_t decoded[DATA_BITS];
        decoded[0] = buffer[0];
        decoded[1] = buffer[1];
        decoded[2] = buffer[3];
        decoded[3] = buffer[6];

        // Check parity bits
        uint8_t parity_bits[PARITY_BITS];
        parity_bits[0] = buffer[2];
        parity_bits[1] = buffer[4];
        parity_bits[2] = buffer[5];

        uint8_t calculated_parity[PARITY_BITS];
        encode_hamming74(decoded, calculated_parity);

        int error = 0;
        for (int i = 0; i < PARITY_BITS; i++) {
            if (calculated_parity[i] != parity_bits[i]) {
                printf("Error detected in bit %d.\n", i);
                error = 1;
                break;
            }
        }

        if (!error) {
            printf("Received: %s\n", decoded);
        }

        send(client_socket, &error, sizeof(int), 0);
    }

    close(client_socket);
    close(server_socket);

    return 0;
}
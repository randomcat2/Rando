#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_BUFFER_SIZE 1024

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

    char expression[MAX_BUFFER_SIZE];
    int read_bytes;

    while (1) {
        printf("Enter an expression (e.g., '5 + 3', or 'exit' to quit): ");
        fgets(expression, sizeof(expression), stdin);

        if (strncmp(expression, "exit", 4) == 0) {
            break;
        }

        // Send the expression to the server
        send(client_socket, expression, strlen(expression), 0);

        // Receive and print the result from the server
        int result;
        read_bytes = recv(client_socket, &result, sizeof(int), 0);
        if (read_bytes <= 0) {
            break;
        }

        printf("Server response: %d\n", result);
    }

    close(client_socket);

    return 0;
}

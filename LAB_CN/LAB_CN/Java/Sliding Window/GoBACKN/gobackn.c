#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for sleep()
#include <stdbool.h>
#include<time.h>
#define WINDOW_SIZE 4
#define MAX_PACKETS 10

struct Packet {
    int sequence_number;
    char data[20]; // Assuming maximum data length of 20 characters
};

void send_packet(struct Packet packet) {
    printf("Sending packet: %d\n", packet.sequence_number);
    // Simulate packet transmission
    // Assuming packet transmission time
    sleep(1);
}

void receive_packet(int sequence_number, int *acknowledgment) {
    // Simulate packet reception
    // Assuming packet reception time
    sleep(1.5);
    printf("Receiving packet: %d\n", sequence_number);

    // Simulate acknowledgment transmission
    // Assuming acknowledgment transmission time
    sleep(0.5);

    // Simulate acknowledgment reception
    if (rand() % 2 == 0) {
        printf("Acknowledgment for packet %d received.\n", sequence_number);
        *acknowledgment = 1;
    } else {
        printf("Acknowledgment for packet %d not received.\n", sequence_number);
        *acknowledgment = 0;
    }
}

int main() {
    srand(time(NULL)); // Seed the random number generator

    struct Packet packets[MAX_PACKETS];
    for (int i = 0; i < MAX_PACKETS; i++) {
        packets[i].sequence_number = i;
        sprintf(packets[i].data, "Packet %d", i);
    }

    int base = 0;
    int next_seq_num = 0;
    char input;

    while (base < MAX_PACKETS) {
        for (int i = base; i < base + WINDOW_SIZE && i < MAX_PACKETS; i++) {
            send_packet(packets[i]);
        }

        printf("Press 'n' to stop transmission or any other key to continue: ");
        scanf(" %c", &input);
        if (input == 'n') {
            printf("Transmission stopped.\n");
            break;
        }

        printf("Waiting for acknowledgments...\n");
        int acknowledgment;
        // Simulate acknowledgment reception
        // Assuming acknowledgment reception time
        sleep(2);
        receive_packet(base, &acknowledgment);

        // Update base on receiving acknowledgment
        if (acknowledgment)
            base++;
    }

    printf("All packets sent successfully!\n");

    return 0;
}
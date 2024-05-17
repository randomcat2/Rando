#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOT_FRAMES 500
#define FRAMES_SEND 10

struct SelectiveRepeat {
    int fr_send_at_instance;
    int arr[TOT_FRAMES];
    int send[FRAMES_SEND];
    int rcvd[FRAMES_SEND];
    char rcvd_ack[FRAMES_SEND];
    int sw;
    int rw;
};

void input(struct SelectiveRepeat *sr) {
    int n; // number of bits for the frame
    int m; // number of frames from n bits
    printf("Enter the number of bits for the sequence no.: ");
    scanf("%d", &n);
    m = 1 << n; // Equivalent to pow(2, n)
    int t = 0;
    sr->fr_send_at_instance = m / 2;
    for (int i = 0; i < TOT_FRAMES; i++) {
        sr->arr[i] = t;
        t = (t + 1) % m;
    }
    for (int i = 0; i < sr->fr_send_at_instance; i++) {
        sr->send[i] = sr->arr[i];
        sr->rcvd[i] = sr->arr[i];
        sr->rcvd_ack[i] = 'n';
    }
    sr->rw = sr->sw = sr->fr_send_at_instance;
    sender(sr, m);
}

void sender(struct SelectiveRepeat *sr, int m) {
    for (int i = 0; i < sr->fr_send_at_instance; i++) {
        if (sr->rcvd_ack[i] == 'n')
            printf("SENDER : Frame %d is sent\n", sr->send[i]);
    }
    receiver(sr, m);
}

void receiver(struct SelectiveRepeat *sr, int m) {
    srand(time(NULL));
    for (int i = 0; i < sr->fr_send_at_instance; i++) {
        if (sr->rcvd_ack[i] == 'n') {
            int f = rand() % 10;
            if (f != 5) {
                for (int j = 0; j < sr->fr_send_at_instance; j++) {
                    if (sr->rcvd[j] == sr->send[i]) {
                        printf("RECEIVER : Frame %d received correctly\n", sr->rcvd[j]);
                        sr->rcvd[j] = sr->arr[sr->rw];
                        sr->rw = (sr->rw + 1) % m;
                        break;
                    }
                }
                int a1 = rand() % 5;
                if (a1 == 3) {
                    printf("(Acknowledgement %d lost)\n", sr->send[i]);
                    printf("(Sender timeouts --> Resend the frame)\n");
                    sr->rcvd_ack[i] = 'n';
                } else {
                    printf("(Acknowledgement %d received)\n", sr->send[i]);
                    sr->rcvd_ack[i] = 'p';
                }
            } else {
                int ld = rand() % 2;
                if (ld == 0) {
                    printf("RECEIVER : Frame %d is damaged\n", sr->send[i]);
                    printf("RECEIVER : Negative Acknowledgement %d sent\n", sr->send[i]);
                } else {
                    printf("RECEIVER : Frame %d is lost\n", sr->send[i]);
                    printf("(SENDER TIMEOUTS --> RESEND THE FRAME)\n");
                }
                sr->rcvd_ack[i] = 'n';
            }
        }
    }

    int j = 0;
    for (j = 0; j < sr->fr_send_at_instance; j++) {
        if (sr->rcvd_ack[j] == 'n')
            break;
    }

    int i = 0;
    for (int k = j; k < sr->fr_send_at_instance; k++) {
        sr->send[i] = sr->send[k];
        if (sr->rcvd_ack[k] == 'n')
            sr->rcvd_ack[i] = 'n';
        else
            sr->rcvd_ack[i] = 'p';
        i++;
    }

    if (i != sr->fr_send_at_instance) {
        for (int k = i; k < sr->fr_send_at_instance; k++) {
            sr->send[k] = sr->arr[sr->sw];
            sr->sw = (sr->sw + 1) % m;
            sr->rcvd_ack[k] = 'n';
        }
    }

    char ch;
    printf("Want to continue (y/n): ");
    scanf(" %c", &ch);
    if (ch == 'y') {
        sender(sr, m);
    } else {
        printf("Transmission stopped.\n");
        exit(0);
    }
}

int main() {
    struct SelectiveRepeat sr;
    input(&sr);
    return 0;
}
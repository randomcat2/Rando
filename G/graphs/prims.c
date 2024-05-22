#include <stdio.h>
#define I 32767
#define n 8

void disp(int t[][6]) {
    int i;
    printf("\n");
    for (i = 0; i < 6; i++) {
        printf("(%d, %d)\n", t[0][i], t[1][i]);
    }
}

void prims(int cost[][n], int near[]) {
    int i, j, k, v, u, min = I;
    int t[2][6];

    for (i = 1; i < n; i++) {
        for (j = i; j < n; j++) {
            if (cost[i][j] < min) {
                min = cost[i][j];
                u = i;
                v = j;
            }
        }
    }

    near[u] = 0;
    near[v] = 0;
    t[0][0] = u;
    t[1][0] = v;

    printf("%d %d\n", u, v);

    // Initialize near array
    for (i = 1; i < n; i++) {
        if (near[i] != 0) {
            if (cost[i][u] < cost[i][v]) {
                near[i] = u;
            } else {
                near[i] = v;
            }
        }
    }

    // Update t array repeatedly
    for (i = 1; i < 6; i++) {
        min = I;
        for (j = 1; j < n; j++) {
            if (near[j] != 0 && cost[j][near[j]] < min) {
                k = j;
                min = cost[j][near[j]];
            }
        }
        t[0][i] = k;
        t[1][i] = near[k];
        near[k] = 0;

        // Update near array
        for (j = 1; j < n; j++) {
            if (near[j] != 0 && cost[j][k] < cost[j][near[j]]) {
                near[j] = k;
            }
        }
    }
    disp(t);
}

int main() {
    int cost[n][n] = {
        {I, I, I, I, I, I, I, I},
        {I, I, 25, I, I, I, 5, I},
        {I, 25, I, 12, I, I, I, 10},
        {I, I, 12, I, 8, I, I, I},
        {I, I, I, 8, I, 16, I, 14},
        {I, I, I, I, 16, I, 20, 18},
        {I, 5, I, I, I, 20, I, I},
        {I, I, 10, I, 14, 18, I, I}
    };

    int near[n] = {I, I, I, I, I, I, I, I};

    prims(cost, near);
    return 0;
}

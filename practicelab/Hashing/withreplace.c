#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

int hash(int key)
{
    return key % SIZE;
}

int probe(int H[], int key)
{
    int index = hash(key);
    int i = 0;
    while (H[(index + i) % SIZE] != 0)
        i++;
    return (index + i) % SIZE;
}

void InsertWithReplacement(int H[], int key)
{
    int index = hash(key);

    // If the spot is already taken
    if (H[index] != 0)
    {
        // Swap the current key with the one in the table
        int temp = H[index];
        H[index] = key;
        key = temp;

        // Probe to insert the displaced key
        index = probe(H, key);
    }
    H[index] = key;
}

void display(int H[])
{
    printf("Index\tValue\n");
    printf("--------------\n");
    for (int i = 0; i < SIZE; i++)
    {
        if (H[i] != 0)
            printf("%d\t%d\n", i, H[i]);
        else
            printf("%d\t%s\n", i, "NULL");
    }
    printf("\n");
}

int main()
{
    int HT[SIZE] = {0};

    InsertWithReplacement(HT, 12);
    InsertWithReplacement(HT, 25);
    InsertWithReplacement(HT, 35);
    InsertWithReplacement(HT, 26);

    display(HT);

    return 0;
}

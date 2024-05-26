#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define READERS_COUNT 5
#define WRITERS_COUNT 5

sem_t mutex, writeBlock;
int data = 0;
int readers = 0;

void *reader(void *arg) {
    int readerID = *((int *)arg);
    while (1) {
        
        sem_wait(&mutex);
        readers++;
        if (readers == 1) {
           
            sem_wait(&writeBlock);
        }
        sem_post(&mutex);
        printf("Reader %d read data: %d\n", readerID, data);
        sem_wait(&mutex);
        readers--;
        if (readers == 0) {
            sem_post(&writeBlock);
        }        sem_post(&mutex);
        sleep(1);
    }
}

void *writer(void *arg) {
    int writerID = *((int *)arg);
    while (1) {
       
        sem_wait(&writeBlock);
        
        data++;
        printf("Writer %d wrote data: %d\n", writerID, data);
        
        sem_post(&writeBlock);
        sleep(1);
    }
}

int main() {
    pthread_t readers_threads[READERS_COUNT], writers_threads[WRITERS_COUNT];
    int readers_ids[READERS_COUNT], writers_ids[WRITERS_COUNT];

    sem_init(&mutex, 0, 1);
    sem_init(&writeBlock, 0, 1);


    for (int i = 0; i < READERS_COUNT; i++) {
        readers_ids[i] = i + 1;
        pthread_create(&readers_threads[i], NULL, reader, &readers_ids[i]);
    }
    for (int i = 0; i < WRITERS_COUNT; i++) {
        writers_ids[i] = i + 1;
        pthread_create(&writers_threads[i], NULL, writer, &writers_ids[i]);
    }

    
    for (int i = 0; i < READERS_COUNT; i++) {
        pthread_join(readers_threads[i], NULL);
    }

   
    for (int i = 0; i < WRITERS_COUNT; i++) {
        pthread_join(writers_threads[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&writeBlock);

    return 0;
}

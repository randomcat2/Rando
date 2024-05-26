#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define READERS_COUNT 5
#define WRITERS_COUNT 5

pthread_mutex_t mutex;
pthread_mutex_t writeMutex;
int data = 0;
int readers = 0;

void *reader(void *arg) {
    int readerID = *((int *)arg);
    while (1) {
        
        pthread_mutex_lock(&mutex);
        readers++;
        if (readers == 1) {
           
            pthread_mutex_lock(&writeMutex);
        }
       
        pthread_mutex_unlock(&mutex);

       
        printf("Reader %d read data: %d\n", readerID, data);

       
        pthread_mutex_lock(&mutex);
        readers--;
        if (readers == 0) {

            pthread_mutex_unlock(&writeMutex);
        }
       
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
}

void *writer(void *arg) {
    int writerID = *((int *)arg);
    while (1) {
      
        pthread_mutex_lock(&writeMutex);
        
        data++;
        printf("Writer %d wrote data: %d\n", writerID, data);
       
        pthread_mutex_unlock(&writeMutex);
        sleep(1);
    }
}

int main() {
    pthread_t readers_threads[READERS_COUNT], writers_threads[WRITERS_COUNT];
    int readers_ids[READERS_COUNT], writers_ids[WRITERS_COUNT];

    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&writeMutex, NULL);

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

    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&writeMutex);

    return 0;
}

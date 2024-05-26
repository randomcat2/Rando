#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define MAX_MATERIALS 20

sem_t empty;
sem_t full;
int materials_buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
int teacher_provided = 0;
int student_consumed = 0;

void *teacher(void *arg) {
    int material = 1;
    while (teacher_provided < MAX_MATERIALS) {
        sem_wait(&empty);
        materials_buffer[in] = material;
        printf("Teacher provided material: %d\n", material);
        material++;
        in = (in + 1) % BUFFER_SIZE;
        sem_post(&full);
        teacher_provided++;
        usleep(1000000);
    }
}

void *student(void *arg) {
    while (student_consumed < MAX_MATERIALS) {
        sem_wait(&full);
        int material = materials_buffer[out];
        printf("Student consumed material: %d\n", material);
        out = (out + 1) % BUFFER_SIZE;
        sem_post(&empty);
        student_consumed++;
        usleep(1000000);
    }
}

int main() {
    pthread_t teacher_thread, student_thread;

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    pthread_create(&teacher_thread, NULL, teacher, NULL);
    pthread_create(&student_thread, NULL, student, NULL);

    pthread_join(teacher_thread, NULL);
    pthread_join(student_thread, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}

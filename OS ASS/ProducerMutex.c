#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define MAX_MATERIALS 20

pthread_mutex_t mutex;
pthread_cond_t full_cond, empty_cond;
int materials_buffer[BUFFER_SIZE];
int in = 0;
int out = 0;
int teacher_provided = 0;
int student_consumed = 0;

void *teacher(void *arg) {
    int material = 1;
    while (teacher_provided < MAX_MATERIALS) {
        pthread_mutex_lock(&mutex);
        while ((in + 1) % BUFFER_SIZE == out) {
            pthread_cond_wait(&empty_cond, &mutex);
        }
        materials_buffer[in] = material;
        printf("Teacher provided material: %d\n", material);
        material++;
        in = (in + 1) % BUFFER_SIZE;
        pthread_cond_signal(&full_cond);
        teacher_provided++;
        pthread_mutex_unlock(&mutex);
        usleep(1000000);
    }
}

void *student(void *arg) {
    while (student_consumed < MAX_MATERIALS) {
        pthread_mutex_lock(&mutex);
        while (in == out) {
            pthread_cond_wait(&full_cond, &mutex);
        }
        int material = materials_buffer[out];
        printf("Student consumed material: %d\n", material);
        out = (out + 1) % BUFFER_SIZE;
        pthread_cond_signal(&empty_cond);
        student_consumed++;
        pthread_mutex_unlock(&mutex);
        usleep(1000000);
    }
}

int main() {
    pthread_t teacher_thread, student_thread;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&full_cond, NULL);
    pthread_cond_init(&empty_cond, NULL);

    pthread_create(&teacher_thread, NULL, teacher, NULL);
    pthread_create(&student_thread, NULL, student, NULL);

    pthread_join(teacher_thread, NULL);
    pthread_join(student_thread, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&full_cond);
    pthread_cond_destroy(&empty_cond);

    return 0;
}

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

sem_t waiter;
pthread_mutex_t chopsticks[NUM_PHILOSOPHERS];

void *philosopher(void *arg) {
    int id = *(int *)arg;
    int left = id;
    int right = (id + 1) % NUM_PHILOSOPHERS;

    printf("Philosopher %d is thinking...\n", id);
    sleep(1);

    printf("Philosopher %d is asking waiter for permission...\n", id);
    sem_wait(&waiter);
    printf("Philosopher %d got permission from waiter!\n", id);

    printf("Philosopher %d is picking up chopsticks %d and %d...\n", id, left, right);
    pthread_mutex_lock(&chopsticks[left]);
    pthread_mutex_lock(&chopsticks[right]);

    printf("Philosopher %d is eating...\n", id);
    sleep(1);

    printf("Philosopher %d is putting down chopsticks...\n", id);
    pthread_mutex_unlock(&chopsticks[left]);
    pthread_mutex_unlock(&chopsticks[right]);

    printf("Philosopher %d is releasing waiter permission...\n", id);
    sem_post(&waiter);

    printf("Philosopher %d finished their cycle!\n", id);
    return NULL;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    printf("Starting Dining Philosophers Problem - One Cycle\n");
    printf("Waiter allows max %d philosophers to try eating at once\n\n", NUM_PHILOSOPHERS - 1);

    sem_init(&waiter, 0, NUM_PHILOSOPHERS - 1);

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&chopsticks[i], NULL);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    printf("\nAll philosophers completed their cycle!\n");

    sem_destroy(&waiter);
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&chopsticks[i]);
    }

    return 0;
}

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "monitor.h"

void *startThinking(void *i) {
    while (true) {
        int philosopher = *(int *)i;
        printf("Philosopher %d is thinking\n", philosopher + 1);
        sleep(rand() % 5);

        pickup(philosopher); // pega os hashis
        printf("Philosopher %d is eating\n", philosopher + 1);
        sleep(rand() % 5);

        putdown(philosopher); // devolve os hashis
    }
}

int main() {
    int philosopher_id[PHILOSOPHERS];
    pthread_t philosopher[PHILOSOPHERS];
    pthread_attr_t attr;

    initialization(); // inicializa o monitor

    pthread_attr_init(&attr);
    for (int i = 0; i < PHILOSOPHERS; i++) {
        philosopher_id[i] = i;
        pthread_create(&philosopher[i], NULL, startThinking, (int *) &philosopher_id[i]);
    }

    for (int i = 0; i < PHILOSOPHERS; i++)
        pthread_join(philosopher[i], NULL);
    
    return EXIT_SUCCESS;
}
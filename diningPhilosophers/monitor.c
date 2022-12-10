#include "monitor.h"
#include <semaphore.h>

typedef struct {
    sem_t sem;
    int count;
} condition;

condition self[PHILOSOPHERS]; // condição de cada filósofo
int state[PHILOSOPHERS]; // estado de cada filósofo
int chopstick[PHILOSOPHERS]; // cada posição indica um hashi, e o valor dessa posição indica com qual filósofo o hashi está

sem_t mutex; // semáforo para acesso a regiao critica

/*
 * Semáforo auxiliar para evitar starvation,
 * antes de permitir que outro filósofo coma novamente, todos deverão ter comido
 */
sem_t next;
int next_count = 0; // número de filósofos que estão esperando para pegar os hashis

void wait(int i) {
    self[i].count++; // incrementa o contador de espera do filósofo

    // se houver algum filósofo esperando para pegar os hashis, libera o proximo filósofo para pegá-los
    // se não, libera o mutex
    (next_count > 0) ? sem_post(&next) : sem_post(&mutex);

    sem_wait(&self[i].sem); // libera o filósofo i para pegar os hashis
    self[i].count--; // decrementa o contador de espera do filósofo
}

void signal(int i) {
    if (self[i].count <= 0) return; // se o filósofo i não estiver esperando, retorna

    next_count++; // incrementa o contador de filósofos esperando para pegar os hashis
    sem_post(&self[i].sem); // filósofo i terminou, libera o próximo para comer

    sem_wait(&next); // libera o próximo filósofo para pegar os hashis
    next_count--; // decrementa o contador de filósofos esperando para pegar os hashis
}

/*
 * Inicializa o monitor, setando os parâmetros iniciais
 * e definindo quem pode começar a comer primeiro
 */
void initialization() {
    sem_init(&mutex, 0, 1);
    sem_init(&next, 0, 0);
    for (int i = 0; i < PHILOSOPHERS; i++) {
        state[i] = THINKING;
        sem_init(&self[i].sem, 0, 0);
        self[i].count = 0;
        chopstick[i] = i; // dá a cada filósofo o hashi a sua direita
    }

    // para evitar deadlock, garante-se que o filósofo de id 0 (filósofo 1) receba os 2 hashis primeiro
    chopstick[4] = 0;
}

// verifica se o filósofo i está com fome, se os vizinhos não estão comendo, e se ele possui os hashis
void test(int i) {
    if (state[i] == HUNGRY && state[(i + 4) % 5] != EATING && state[(i + 1) % 5] != EATING && chopstick[i] == i && chopstick[(i + 4) % 5] == i) {
        state[i] = EATING;
        signal(i);
    }
}

void pickup(int i) {
    sem_wait(&mutex); // entra na região crítica

    state[i] = HUNGRY; 
    test(i); // tenta pegar os hashis

    while (state[i] == HUNGRY) { // se não conseguiu, espera
        wait(i);
    }

    // se tem alguem esperando, libera o próximo filósofo para pegar os hashis
    // se nao, libera o mutex
    (next_count > 0) ? sem_post(&next) : sem_post(&mutex);
}

// OBS: como devolve cada hashi para os vizinhos, todos poderão comer eventualmente, evitando starvation
void putdown(int i) {
    state[i] = THINKING;
    chopstick[i] = (i + 1) % 5; // dá o hashi da direita para o filósofo da direita
    chopstick[(i + 4) % 5] = (i + 4) % 5; // dá o hashi da esquerda para o filósofo da esquerda
    
    test((i + 4) % 5); // testa se o filósofo da esquerda pode comer
    test((i + 1) % 5); // testa se o filósofo da direita pode comer

    // se tem alguem esperando, libera o próximo filósofo para pegar os hashis
    // se nao, libera o mutex
    (next_count > 0) ? sem_post(&next) : sem_post(&mutex);
}
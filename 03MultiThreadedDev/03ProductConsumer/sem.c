#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>


pthread_mutex_t mutex;
sem_t prosem, consem;

struct Node{
    int num;
    struct Node *next;
};
struct Node * head = NULL;

void * producer(void * arg) {
    while(1) {
        sem_wait(&prosem);
        pthread_mutex_lock(&mutex);
        struct Node * newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->next = head;
        head = newNode;
        newNode->num = rand() % 1000;
        printf("add node, num : %d, tid : %ld\n", newNode->num, pthread_self());
        pthread_mutex_unlock(&mutex);
        sem_post(&consem);
    }
    return NULL;
}

void * customer(void * arg) {
    while(1) {
        sem_wait(&consem);
        pthread_mutex_lock(&mutex);
        struct Node * tmp = head;
        head = head->next;
        printf("del node, num : %d, tid : %ld\n", tmp->num, pthread_self());
        free(tmp);
        pthread_mutex_unlock(&mutex);
        sem_post(&prosem);
    }
    return  NULL;
}

int main() {
    sem_init(&prosem, 0, 8);
    sem_init(&consem, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_t ptids[5], ctids[5];
    for(int i = 0; i < 5; i++) {
        pthread_create(&ptids[i], NULL, producer, NULL);
        pthread_create(&ctids[i], NULL, customer, NULL);
    }
    for(int i = 0; i < 5; i++) {
        pthread_detach(ptids[i]);
        pthread_detach(ctids[i]);
    }

    while(1) {
        sleep(10);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&consem);
    sem_destroy(&prosem);

    pthread_exit(NULL);
    return 0;
}


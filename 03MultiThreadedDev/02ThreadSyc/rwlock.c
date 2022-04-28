#include <stdio.h>
#include <pthread.h>
#include <unistd.h>



int num = 100;

pthread_rwlock_t rwlcok;

void* readNum(void* arg) {
    while(1) {
        pthread_rwlock_rdlock(&rwlcok);
        if(num >= 0) {
            printf("read: %d\n", num);
            pthread_rwlock_unlock(&rwlcok);
        } else {
            pthread_rwlock_unlock(&rwlcok);
            pthread_exit(NULL);
        }
        usleep(500);
    }
}

void* writeNum(void* arg) {
    while(1) {
        pthread_rwlock_wrlock(&rwlcok);
        if(num >= 0) {
            printf("write: %d\n", --num);
            pthread_rwlock_unlock(&rwlcok);
        } else {
            pthread_rwlock_unlock(&rwlcok);
            pthread_exit(NULL);
        }
        usleep(500);
    }
}


int main() {

    pthread_rwlock_init(&rwlcok, NULL);

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    pthread_t rdtid[5], wrtid[3];
    for(int i = 0; i < 5; i++) {
        pthread_create(&rdtid[i], &attr, readNum, NULL);
    }
    for(int i = 0; i < 3; i++) {
        pthread_create(&wrtid[i], &attr, writeNum, NULL);
    }
    
    pthread_rwlock_destroy(&rwlcok);
    pthread_attr_destroy(&attr);
    pthread_exit(NULL);
    return 0;
}
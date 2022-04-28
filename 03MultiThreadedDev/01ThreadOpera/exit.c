#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>



void* callback(void* arg) {
    printf("pthread id %ld, num %d\n", pthread_self(), *(int*)arg);
    pthread_exit(0);
}


int main() {

    pthread_t tid;
    int num = 0;
    pthread_create(&tid, NULL, callback, (void*)&num);

    num++;

    pthread_exit(0);

    return 0;
}
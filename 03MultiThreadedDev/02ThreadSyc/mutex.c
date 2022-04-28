#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;

int num = 500;

void* sellticket(void* arg) {

    while(1) {
        pthread_mutex_lock(&mutex);
        if(num > 0) {
            usleep(6000);
            printf("pthread %ld selling %d\n", pthread_self(), num);
            num--;
            pthread_mutex_unlock(&mutex);
        } else {
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }
    }

}

int main() {
    
    pthread_mutex_init(&mutex, NULL);

    pthread_t tid[5];

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    for(int i = 0; i < 5; i++) {
        pthread_create(&tid[i], &attr, sellticket, NULL);
    }

    pthread_mutex_destroy(&mutex);

    pthread_attr_destroy(&attr);
    pthread_exit(NULL);
    return 0;
}
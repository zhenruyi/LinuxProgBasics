#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int tickets = 100;

void * sellticket(void * arg) {
    while(tickets > 0) {
        usleep(6000);
        printf("%ld sell ticket no: %d\n", pthread_self(), tickets);
        tickets--;
    }
    return NULL;
}

int main() {

    pthread_t tid1, tid2, tid3;
    pthread_create(&tid1, NULL, sellticket, NULL);
    pthread_create(&tid2, NULL, sellticket, NULL);
    pthread_create(&tid3, NULL, sellticket, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);

    pthread_exit(NULL);

    return 0;
}
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>


void* callback(void* arg) {

    sleep(1);

    pthread_exit(NULL);

}


int main() {

    pthread_t tid;
    pthread_create(&tid, NULL, callback, NULL);

    int res = pthread_detach(tid);
    if(res != 0) {
        char* errstr = strerror(res);
        printf("error: %s\n", errstr);
    }

    pthread_exit(NULL);

    return 0;
}
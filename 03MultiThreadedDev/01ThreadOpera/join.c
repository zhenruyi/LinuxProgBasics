#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

int num = 123;

void* callback(void* arg) {
    
    pthread_exit((void*)&num);
}


int main() {

    pthread_t tid;  
    int res = pthread_create(&tid, NULL, callback, NULL);
    if(res != 0) {
        char* errstr = strerror(res);
        printf("error: %s\n", errstr);
    }

    printf("tid: %ld, main thread id: %ld\n", tid, pthread_self());

    int* retval;
    res = pthread_join(tid, (void**)&retval);
    if(res != 0) {
        char* errstr = strerror(res);
        printf("error: %s\n", errstr);
    }

    printf("exit data : %d\n", *retval);

    pthread_exit(NULL);


    return 0;
}
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>



void* callback(void* arg) {
    printf("i am child thread\n");
    return NULL;
}


int main() {    


    pthread_t tid;
    int res = pthread_create(&tid, NULL, callback, NULL);
    if(res != 0) {
        char* errstr = strerror(res);
        printf("error : %s\n", errstr);
    }

    for(int i = 0; i < 5; i++) {
        printf("%d\n", i);
    }



    return 0;
}
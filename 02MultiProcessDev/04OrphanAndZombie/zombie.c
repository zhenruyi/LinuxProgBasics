#include <stdio.h>
#include <unistd.h>


int main() {


    pid_t pid = fork();

    if(pid > 0) {
        while(1) {
            printf("parent pid %d\n", getpid());  
            sleep(2);
        }
    }

    if(pid == 0) {
        printf("child exit\n");
    }

    return 0;
}
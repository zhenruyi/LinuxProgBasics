#include <stdio.h>
#include <unistd.h>


int main() {

    pid_t pid = fork();

    if(pid > 0) {
        sleep(2);
        printf("parent proc %d exit\n", getpid());
    }

    if(pid == 0) {
        for(int i = 0; i < 5; i++) {
            printf("child proc %d 's parent %d\n", getpid(), getppid());
            sleep(1);
        }
    }


    return 0;
}
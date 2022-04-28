#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main() {

    pid_t pid = fork();

    if(pid == -1) {
        perror("fork");
        return 0;
    } else if(pid > 0) {
        printf("parent pid = %d, child pid = %d\n", getpid(), pid);
    } else if(pid == 0) {
        printf("child pid = %d, parent pid = %d\n", getpid(), getppid());
    } else {
        return 0;
    }

    printf("pid %d eixt\n", getpid());

    return 0;
}
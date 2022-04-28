#include <unistd.h>
#include <stdio.h>

int main() {

    pid_t pid = fork();
    if(pid > 0 ) {
        printf("parent process, pid = %d\n", getpid());
    }
    if(pid == 0) {
        printf("child process, pid = %d\n", getpid());
        execl("/bin/ps", "ps", "aux", NULL);
        perror("execl");
        printf("1");
    }

    printf("pid = %d\n", getpid());

    return 0;
}
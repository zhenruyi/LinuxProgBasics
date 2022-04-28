#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {

    pid_t pid = fork();
    if(pid == 0) {
        sleep(1);
        // exit(3);
        // kill(getpid(), SIGINT);
        // raise(SIGKILL);
        abort();
    }
    if(pid > 0) {
        int st;
        wait(&st);
        if(WIFEXITED(st)) {
            printf("exit %d\n", WEXITSTATUS(st));
        }
        if(WIFSIGNALED(st)) {
            printf("signal %d\n", WTERMSIG(st));
        }
    }


    return 0;
}
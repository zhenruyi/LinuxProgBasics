#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main() {

    pid_t pid;

    for(int i = 0; i < 5; i++) {
        pid = fork();
        if(pid == 0) break;
    }

    if(pid == 0) {
        while(1) {
            printf("child %d \n", getpid());
            sleep(1);
        }
    }

    if(pid > 0) {
        while(1) {
            int st;
            int ret = waitpid(-1, &st, WNOHANG);
            if(ret == -1) {
                return 0;
            }
            if(ret == 0) {
                continue;
            }
            if(ret > 0) {
                if(WIFEXITED(st)) {
                    printf("exit %d\n", WEXITSTATUS(st));
                }
                if(WIFSIGNALED(st)) {
                    printf("signal %d\n", WTERMSIG(st));
                }
            }
        }
    }

    return 0;
}
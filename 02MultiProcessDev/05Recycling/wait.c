#include <sys/types.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {

    pid_t pid;
    for(int i = 0; i < 5; i++) {
        pid = fork();
        if (pid == 0) {
            break;
        }
    }

    if(pid == 0) {
        while (1) {
            printf("child pid %d\n", getpid());
            sleep(2);
        }
    }

    if(pid > 0) {
        while(1) {
            printf("parent pid %d", getpid());

            int st;
            int ret = wait(&st);

            if(ret == -1) {
                break;
            }

            if(WIFEXITED(st)) {
                printf("exit %d\n", WEXITSTATUS(st));
            }

            if(WIFSIGNALED(st)) {
                printf("signal %d", WTERMSIG(st));
            }
        }
    }


    return 0;
}
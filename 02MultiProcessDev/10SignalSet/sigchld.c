#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/wait.h>


void recycleChld(int num) {
    int st;
    while(1) {
        int ret = waitpid(-1, &st, WNOHANG);
        if(ret > 0) {
            printf("child die");
        } else if(ret == 0) {
            break;
        } else {
            break;
        }
    }
}

int main() {

    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGCHLD);
    sigprocmask(SIG_BLOCK, &set, NULL);

    pid_t pid = fork();
    
    if(pid == 0) {
        printf("child process pid : %d\n", getpid());
    }

    if(pid > 0) {
        struct sigaction act;
        act.sa_flags = 0;
        sigemptyset(&act.sa_mask);
        act.sa_handler = recycleChld;

        sigaction(SIGCHLD, &act, NULL);

        sigemptyset(&set);
        sigprocmask(SIG_SETMASK, &set, NULL);

        while(1) {
            printf("parent process pid : %d\n", getpid());
            sleep(2);
        }
    }

    return 0;
}
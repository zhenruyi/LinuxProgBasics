#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>


int main() {

    int pipefd[2];
    int ret = pipe(pipefd);
    if(ret == -1) {
        perror("pipe");
        exit(0);
    }

    pid_t pid = fork();
    if(pid == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        execlp("ps", "ps", "aux", NULL);
        perror("execlp");
        exit(0);
    }
    if(pid > 0) {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        int st;
        waitpid(0, &st, WNOHANG);
    }



    return 0;
}
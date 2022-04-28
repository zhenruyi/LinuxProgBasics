#include <stdio.h>
#include <unistd.h>


int main() {

    int pipefd[2];
    pipe(pipefd);

    long size = fpathconf(pipefd[0], _PC_PIPE_BUF);

    printf("size : %ld", size);

    return 0;
}
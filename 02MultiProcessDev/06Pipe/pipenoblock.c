#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
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
        printf("child\n");
        close(pipefd[0]);
        char buf[1024] = "1asdasdasdasd";
        while(1) {
            write(pipefd[1], buf, sizeof(buf));
            sleep(2);
        }
        close(pipefd[1]);
        exit(0);
    }
    if(pid > 0) {
        printf("parent\n");
        close(pipefd[1]);
        char buf[1024] = {0};
        int flag = fcntl(pipefd[0], F_GETFL);
        flag = flag | O_NONBLOCK;
        fcntl(pipefd[0], F_SETFL, flag);
        while(1) {
            read(pipefd[0], buf, sizeof(buf));
            printf("read :%s\n", buf);
            memset(buf, 0, sizeof(buf));
            sleep(1);
        }
        close(pipefd[0]);
    }


    return 0;
}
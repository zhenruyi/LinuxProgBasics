#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main() {

    int pipefd[2] = {0};
    int ret = pipe(pipefd);
    if(ret == -1) {
        perror("pipe");
        return -1;
    }

    pid_t pid = fork();
    if(pid > 0) {
        while (1) {
            char buf[1024] = {0};
            read(pipefd[0], buf, sizeof(buf));
            printf("read: %s\n", buf);
        }
        
    }

    if(pid == 0) {
        char buf[256] = "123123";
        write(pipefd[1], (void*)buf, sizeof(buf));
        sleep(2);
        char buf2[256] = "asadsadsadas";
        write(pipefd[1], buf2, sizeof(buf2));
    }
    
    close(pipefd[1]);
    close(pipefd[0]);

    return 0;
}
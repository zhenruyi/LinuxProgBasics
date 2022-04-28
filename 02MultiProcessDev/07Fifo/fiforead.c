#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


int main() {

    int ret = access("fifo2", F_OK);
    if(ret == -1) {
        printf("create fifo2");
        ret = mkfifo("fifo2", 0664);
        if(ret == -1) {
            perror("mkfifo");
            exit(0);
        }
    }

    int fd = open("fifo2", O_RDONLY);
    if(fd == -1)  {
        perror("open");
        exit(0);
    }
    // int flag = fcntl(fd, F_GETFL);
    // flag = flag | O_NONBLOCK;
    // fcntl(fd, F_SETFL, flag);
    char buf[1024];
    while(1) {
        read(fd, buf, sizeof(buf));
        printf("read : %s", buf);
        memset(buf, 0, sizeof(buf));
        sleep(1);
    }
    close(fd);


    return 0;
}
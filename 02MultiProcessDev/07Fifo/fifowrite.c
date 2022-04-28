#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {

    int fd = open("fifo2", O_WRONLY, 0664);
    if(fd == -1) {
        perror("open");
        exit(0);
    }

    char buf[1024] = "asdas";
    while(1) {
        write(fd, buf, sizeof(buf));
        sleep(1);
    }

    close(fd);

    return 0;
}
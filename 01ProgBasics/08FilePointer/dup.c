#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main() {

    int fd = open("a.txt", O_RDONLY);
    if(fd == -1) {
        perror("open");
        return -1;
    }

    int fd2 = dup(fd);
    if(fd2 = -1) {
        perror("dup");
        return -1;
    }

    printf("fd:%d, fd2:%d\n", fd, fd2);

    close(fd2);
    close(fd);


    return 0;
}
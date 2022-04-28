#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main() {

    int fd = open("a.txt", O_RDWR);

    int fd2 = fcntl(fd, F_DUPFD);

    printf("%d\n%d\n", fd, fd2);

    int flag = fcntl(fd, F_GETFL);
    flag = flag & O_RDONLY;
    printf("flag = %d\n", flag);


    return 0;
}
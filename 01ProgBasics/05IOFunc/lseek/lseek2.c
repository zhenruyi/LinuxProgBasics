#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {

    int fd = open("english.txt", O_RDONLY);

    off_t len = lseek(fd, 0, SEEK_END);

    printf("english.txt len = %ld", len);

    close(fd);

    return 0;
}
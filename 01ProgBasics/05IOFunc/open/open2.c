#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {

    int fd = open("a.txt", O_RDONLY | O_CREAT, 0777);
    if(fd == -1) {
        perror("open");
        return -1;
    }

    close(fd);

    return 0;
}
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main() {

    int fd = open("./t.txt", O_RDONLY);
    if(fd == -1) {
        perror("open");
        return -1;
    }

    close(fd);

    return 0;
}
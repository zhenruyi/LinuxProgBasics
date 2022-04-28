#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main() {

    int fd = open("english.txt", O_RDONLY);

    struct stat statbuf;

    int ret = fstat(fd, &statbuf);
    if(ret == -1) {
        perror("fstat");
        return -1;
    }

    int uid = statbuf.st_uid;
    int len = statbuf.st_size;

    printf("uid = %d, size = %d", uid, len);

    close(fd);


    return 0;
}
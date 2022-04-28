#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


int main() {

    int fdrd = open("test.txt", O_RDONLY);
    if(fdrd == -1) {
        perror("open");
        exit(0);
    }
    int len = lseek(fdrd, 0, SEEK_END);

    int fdwr = open("cpy.txt", O_RDWR | O_CREAT, 0664);
    if(fdwr == -1) {
        perror("open");
        exit(0);
    }
    truncate("cpy.txt", len);
    write(fdwr, " ", 1);

    void* rptr = mmap(NULL, len, PROT_READ, MAP_SHARED, fdrd, 0);
    void* wptr = mmap(NULL, len, PROT_WRITE, MAP_SHARED, fdwr, 0);
    if(rptr == NULL || wptr == NULL) {
        perror("mmap");
        exit(0);
    }

    memcpy(wptr, rptr, len);

    munmap(wptr, len);
    munmap(rptr, len);

    close(fdwr);
    close(fdrd);



    return 0;
}
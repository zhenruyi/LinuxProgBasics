#include <stdio.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <wait.h>


int main() {

    int fd = open("test.txt", O_RDWR);
    if(fd == -1) {
        perror("open");
        exit(0);
    }
    lseek(fd, 200, SEEK_END);
    int size = lseek(fd, 0, SEEK_END);

    void* ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(ptr == MAP_FAILED) {
        perror("mmap");
        exit(0);
    }

    pid_t pid = fork();
    if(pid > 0) {
        wait(NULL);
        char buf[1024];
        strcpy(buf, (char*)ptr);
        printf("%s", buf);
    }
    if(pid == 0) {
        char buf[1024] = "asdasdas";
        strcpy((char*)ptr, buf);
    }

    munmap(ptr, size);
    close(fd);


    return 0;
}
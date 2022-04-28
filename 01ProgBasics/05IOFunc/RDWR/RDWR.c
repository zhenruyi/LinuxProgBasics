#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {

    int fdrd = open("english.txt", O_RDONLY);
    if(fdrd == -1) {
        perror("open");
        return -1;
    }

    int fdwr = open("cpy.txt", O_RDWR | O_CREAT, 0777);
    if(fdwr == -1) {
        perror("open");
        return -1;
    }

    char buf[1024] = {0};

    ssize_t ret = 0;
    while((ret = read(fdrd, buf, sizeof(buf))) > 0) {
        ssize_t wret = write(fdwr, buf, ret);
        if(wret == -1) {
            perror("write");
            return -1;
        }
    }

    close(fdwr);
    close(fdrd);
    

    return 0;
}
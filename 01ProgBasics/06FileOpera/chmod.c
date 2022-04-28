#include <sys/stat.h>
#include <stdio.h>

int main() {

    int ret = chmod("a.txt", 0771);
    if(ret == -1) {
        perror("chmod");
        return -1;
    }

    return 0;
}
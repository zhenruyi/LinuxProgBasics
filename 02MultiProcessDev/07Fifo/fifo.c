#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {

    int ret = access("fifo1", F_OK);
    if(ret == -1) {
        printf("fifo1 not exist, create fifo1");
        ret = mkfifo("fifo1", 0664);
        if(ret == -1) {
            perror("mkfifo");
            exit(0);
        }
    }

    return 0;
}
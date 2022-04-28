#include <signal.h>
#include <stdio.h>

int main() {

    sigset_t set;

    sigemptyset(&set);

    int ret = sigismember(&set, SIGINT);
    if(ret == 0) {
        printf("no block\n");
    } else if(ret == 1) {
        printf("block \n");
    }

    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGQUIT);

    sigdelset(&set, SIGINT);


    return 0;
}
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


void myalarm(int num) {
    printf("asdas");
}

int main() {

    struct sigaction act;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    act.sa_handler = myalarm;

    sigaction(SIGALRM, &act, NULL);

    struct itimerval new_value;
    new_value.it_interval.tv_sec = 2;
    new_value.it_interval.tv_usec = 0;
    new_value.it_value.tv_sec = 3;
    new_value.it_value.tv_usec = 0;

    setitimer(ITIMER_REAL, &new_value, NULL);

    while(1);



    return 0;
}
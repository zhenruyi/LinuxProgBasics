#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


void myalarm(int num){
    printf("alarm : %d\n", num);
}



int main() {

    signal(SIGALRM, myalarm);

    struct itimerval new_value;
    new_value.it_interval.tv_sec = 2;
    new_value.it_interval.tv_usec = 0;
    new_value.it_value.tv_sec = 3;
    new_value.it_value.tv_usec = 0;
    setitimer(ITIMER_REAL, &new_value, NULL);

    while(1) {

    }



    return 0;
}
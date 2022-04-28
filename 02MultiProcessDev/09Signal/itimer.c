#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>


int main() {

    struct itimerval* val;
    val->it_interval.tv_sec = 2;
    val->it_interval.tv_usec = 0;
    val->it_value.tv_sec = 5;
    val->it_value.tv_usec = 0;
    
    setitimer(ITIMER_REAL, val, NULL);

    getchar();


    return 0;
}
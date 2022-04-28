#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <signal.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>



void work(int num) {
    printf("asdas");
}

int main() {

    pid_t pid = fork();

    if(pid > 0) {
        exit(0);
    }

    if(pid == 0) {
        pid = getpid();
        setpgrp();
        setsid();

        umask(022);
        chdir("/home/zhenruyi/");

        int fd = open("/dev/null", O_RDWR);
        dup2(fd, STDIN_FILENO);
        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDERR_FILENO);

        struct sigaction act;
        act.sa_flags = 0;
        sigemptyset(&act.sa_mask);
        act.sa_handler = work;
        sigaction(SIGALRM, &act, NULL);

        struct itimerval val;
        val.it_interval.tv_sec = 2;
        val.it_interval.tv_usec = 0;
        val.it_value.tv_sec = 5;
        val.it_value.tv_usec = 0;
        setitimer(ITIMER_REAL, &val, NULL);
    }


    return 0;
}
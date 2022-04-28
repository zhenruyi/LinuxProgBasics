#include <unistd.h>
#include <stdio.h>

int main() {

    int seconds = alarm(20);
    printf("seconds = %d\n", seconds);

    sleep(2);

    seconds = alarm(5);
    printf("seconds = %d\n", seconds);

    seconds = 5;

    while(1) {
        printf("%d\n", seconds--);
        sleep(1);
    }



    return 0;
}
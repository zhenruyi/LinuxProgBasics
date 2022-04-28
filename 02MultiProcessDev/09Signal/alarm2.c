#include <unistd.h>
#include <stdio.h>


int main() {

    alarm(1);

    int num = 0;
    while(1) {
        printf("%d\n", num++);
    }

    return 0;
}
#include <stdio.h>

int main() {

    union {
        short value;
        char byte[sizeof(short)];
    } test;

    test.value = 0x0102;
    if(test.byte[0] == 1 && test.byte[1] == 2) {
        printf("big");
    } else if(test.byte[1] == 1 && test.byte[0] == 2) {
        printf("small");
    } else {
        printf("wrong");
    }

    return 0;
}

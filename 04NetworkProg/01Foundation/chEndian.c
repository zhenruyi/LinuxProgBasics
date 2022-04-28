#include <arpa/inet.h>
#include <stdio.h>

int main() {

    unsigned short a = 0x0102;
    printf("%x\n", a);
    unsigned short b = htons(a);
    printf("%x\n", b);

    char buf[4] = {192, 168, 1, 100};
    int num = *(int*)buf;
    int sum = htonl(num);
    unsigned char* p = (char*)&sum;
    printf("%d %d %d %d\n", *p, *(p+1), *(p+2), *(p+3));

    


    return 0;




}
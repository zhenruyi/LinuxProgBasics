#include <stdio.h>
#include <arpa/inet.h>



int main() {

    char buf[] = "192.168.1.4";
    unsigned int num = 0;

    inet_pton(AF_INET, buf, &num);
    unsigned char* p = (unsigned char*)&num;
    printf("%d %d %d %d\n", *p, *(p+1), *(p+2), *(p+3));




    return 0;
}
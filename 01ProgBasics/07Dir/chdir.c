#include <unistd.h>
#include <stdio.h>

int main() {

    char buf[1024] = {0};
    getcwd(buf, sizeof(buf));
    printf("pwd: %s\n", buf);

    int ret = chdir("/home/zhenruyi/linux/");
    if(ret == -1) {
        perror("chdir");
        return -1;
    }

    char buf2[1024] = {0};
    getcwd(buf2, sizeof(buf2));
    printf("pwd: %s\n", buf2);

    return 0;
}
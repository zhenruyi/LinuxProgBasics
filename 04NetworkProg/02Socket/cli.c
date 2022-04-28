#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


int main() {
    int fd = socket(PF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serveraddr;
    serveraddr.sin_family = PF_INET;
    serveraddr.sin_port = htons(9999);
    inet_net_pton(AF_INET, "192.168.193.128", &serveraddr.sin_addr.s_addr, sizeof(serveraddr));

    int ret = connect(fd, &serveraddr, sizeof(serveraddr));

    char recvBuf[1024] = {0};
    while(1) {
        char * data = "hello,i am client";
        write(fd, data , strlen(data));
        sleep(1);
        int len = read(fd, recvBuf, sizeof(recvBuf));
        if(len == -1) {
            perror("read");
            exit(-1);
        } else if(len > 0) {
            printf("recv server data : %s\n", recvBuf);
        } else if(len == 0) {
            printf("server closed...");
            break;
        }
    }

    close(fd);
    return 0;
}
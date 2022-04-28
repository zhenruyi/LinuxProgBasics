#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


int main() {


    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    if(lfd == -1) {
        perror("socket");
        exit(-1);
    }


    struct sockaddr_in saddr;
    saddr.sin_family = PF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;
    saddr.sin_port = htons(9999);
    int res = bind(lfd, (struct sockaddr*)&saddr, sizeof(saddr));
    if(res == -1) {
        perror("bind");
        exit(-1);
    }


    res = listen(lfd, 8);
    if(res == -1) {
        perror("listen");
        exit(-1);
    }


    struct sockaddr_in caddr;
    int size = sizeof(caddr);
    int cfd = accept(lfd, (struct sockaddr*)&caddr, &size);
    if(cfd == -1) {
        perror("accept");
        exit(-1);
    }


    char clientIP[16] = {0};
    inet_ntop(AF_INET, &caddr.sin_addr.s_addr, clientIP, sizeof(clientIP));
    unsigned short clientPort = ntohs(caddr.sin_port);
    printf("client ip is %s, port is %d\n", clientIP, clientPort);

    char buf[1024] = {0};
    while(1) {  
        memset(buf, 0, sizeof(buf));
        int len = read(cfd, buf, sizeof(buf));
        if(len == -1) {
            perror("read");
            exit(-1);
        } else if(len == 0) {
            printf("connect close\n");
            break;
        } else {
            printf("data: %s\n", buf);
        }
        char* str = "hello i am server\n";
        write(cfd, str, sizeof(str));
    }

    close(cfd);
    close(lfd);

    return 0;
}
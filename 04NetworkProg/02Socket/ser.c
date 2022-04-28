#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main() {

    int sockfd = socket(PF_INET, SOCK_STREAM, 0);
    if(sockfd == -1) {
        perror("socket");
        exit(-1);
    }

    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;
    saddr.sin_port = htons(9999);
    int res = bind(sockfd, (struct sockaddr*)&saddr, sizeof(saddr));
    if(res == -1) {
        perror("bind");
        exit(-1);
    }

    listen(sockfd, 8);

    struct sockaddr_in clientaddr;
    int len = sizeof(clientaddr);
    int cfd = accept(sockfd, (struct sockaddr*)&clientaddr, &len);

    char clientIP[16];
    inet_ntop(AF_INET, &clientaddr.sin_addr.s_addr, clientIP, sizeof(clientIP));
    unsigned short clientport = ntohs(clientaddr.sin_port);
    printf("client ip is %s, port is %d\n", clientIP, clientport);

    char recvBuf[1024] = {0};
    while(1) {
        int num = read(cfd, recvBuf, sizeof(recvBuf));
        if(num == -1) {
            perror("read");
            exit(-1);
        } else if(num > 0) {
            printf("recv client data : %s\n", recvBuf);
        } else if(num == 0) {
            printf("clinet closed...");
            break;
        }
        char * data = "hello,i am server";
        write(cfd, data, strlen(data));
    }

    close(cfd);
    close(sockfd);



    return 0;
}
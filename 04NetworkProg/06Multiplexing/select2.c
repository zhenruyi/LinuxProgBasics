#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>

int main() {

    int lfd = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in saddr;
    saddr.sin_port = htons(9999);
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;
    bind(lfd, (struct sockaddr *)&saddr, sizeof(saddr));
    listen(lfd, 8);

    fd_set fds, tmp;
    FD_ZERO(&fds);
    FD_SET(lfd, &fds);
    int maxfd = lfd;

    while(1) {
        tmp = fds;
        int res = select(maxfd+1, &tmp, NULL, NULL, NULL);
        if(res == -1) {
            perror("select");
            exit(-1);
        } else if(res == 0) {
            continue;
        } else if(res > 0) {
            if(FD_ISSET(lfd, &tmp)) {
                struct sockaddr_in cliaddr;
                int size = sizeof(cliaddr);
                int cfd = accept(lfd, (struct sockaddr*)&cliaddr, &size);
                FD_SET(cfd, &fds);
                maxfd = maxfd > cfd ? maxfd : cfd;
            }
            for(int i = lfd + 1; i <= maxfd; i++) {
                if(FD_ISSET(i, &tmp)) {
                    // 说明这个文件描述符对应的客户端发来了数据
                    char buf[1024] = {0};
                    int len = read(i, buf, sizeof(buf));
                    if(len == -1) {
                        perror("read");
                        exit(-1);
                    } else if(len == 0) {
                        printf("client closed...\n");
                        close(i);
                        FD_CLR(i, &fds);
                    } else if(len > 0) {
                        printf("read buf = %s\n", buf);
                        write(i, buf, strlen(buf) + 1);
                    }
                }
            }
        }
    }


}
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <wait.h>
#include <errno.h>


void recyChld(int arg) {
    while(1) {
        int res = waitpid(-1, NULL, WNOHANG);
        if(res == -1) {
            break;
        } else if(res == 0) {
            break;
        } else {
            printf("子进程 %d 被回收了\n", res);
        }
    }
}


int main() {

    struct sigaction act;
    act.sa_flags = 0;
    act.sa_handler = recyChld;
    sigemptyset(&act.sa_mask);
    sigaction(SIGCHLD, &act, NULL);

    int lfd = socket(PF_INET, SOCK_STREAM, 0);
    if(lfd == -1){
        perror("socket");
        exit(-1);
    }
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(9999);
    saddr.sin_addr.s_addr = INADDR_ANY;
    int res = bind(lfd,(struct sockaddr *)&saddr, sizeof(saddr));
    if(res == -1) {
        perror("bind");
        exit(-1);
    }
    res = listen(lfd, 128);
    if(res == -1) {
        perror("listen");
        exit(-1);
    }

    while(1) {
        struct sockaddr_in cliaddr;
        int size = sizeof(cliaddr);
        int cfd = accept(lfd, &cliaddr, &size);
        if(cfd == -1) {
            if(errno == EINTR) {
                continue;
            }
            perror("accept");
            exit(-1);
        }
        pid_t pid = fork();
        if(pid == 0) {
            char cliIP[16] = {0};
            inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, cliIP, sizeof(cliIP));
            unsigned short cliPort = ntohs(cliaddr.sin_port);
            printf("client ip is : %s, prot is %d\n", cliIP, cliPort);
            char recvBuf[1024];
            while(1) {
                int len = read(cfd, &recvBuf, sizeof(recvBuf));
                if(len == -1) {
                    perror("read");
                    exit(-1);
                }else if(len > 0) {
                    printf("recv client : %s\n", recvBuf);
                } else if(len == 0) {
                    printf("client closed....\n");
                    break;
                }
                write(cfd, recvBuf, strlen(recvBuf) + 1);
            }
            close(cfd);
            exit(0);
        }
    }
    
}
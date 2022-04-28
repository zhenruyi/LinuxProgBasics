#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>


struct sockInfo {
    int fd;
    struct sockaddr_in addr;
    pthread_t tid;
};

struct sockInfo sockinfos[128];


void* sockComu(void* arg) {
    struct sockInfo* pinfo = (struct sockInfo*)arg;
    char cliIp[16];
    inet_ntop(AF_INET, &pinfo->addr.sin_addr.s_addr, cliIp, sizeof(cliIp));
    unsigned short cliPort = ntohs(pinfo->addr.sin_port);
    printf("client ip is : %s, prot is %d\n", cliIp, cliPort);

    char recvBuf[1024];
    while(1) {
        int len = read(pinfo->fd, &recvBuf, sizeof(recvBuf));
        if(len == -1) {
            perror("read");
            exit(-1);
        }else if(len > 0) {
            printf("recv client : %s\n", recvBuf);
        } else if(len == 0) {
            printf("client closed....\n");
            break;
        }
        write(pinfo->fd, recvBuf, strlen(recvBuf) + 1);
    }
    close(pinfo->fd);
    return NULL;
}



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
    int res = bind(lfd, &saddr, sizeof(saddr));
    if(res == -1) {
        perror("bind");
        exit(-1);
    }

    res = listen(lfd, 128);
    if(res == -1) {
        perror("listen");
        exit(-1);
    }

    int max = sizeof(sockinfos) / sizeof(sockinfos[0]);
    for(int i = 0; i < max; i++) {
        bzero(&sockinfos[i], sizeof(sockinfos[i]));
        sockinfos[i].fd = -1;
        sockinfos[i].tid = -1;
    }

    while(1) {
        struct sockaddr_in cliaddr;
        int size = sizeof(cliaddr);
        int cfd = accept(lfd, &cliaddr, &size);
        if(cfd == -1) {
            perror("accept");
            exit(-1);
        }

        struct sockInfo* pinfo;
        for(int i = 0; i < max; i++) {
            if(sockinfos[i].fd == -1) {
                pinfo = &sockinfos[i];
                break;
            }
            if(i == max - 1) {
                sleep(1);
                i--;
            }
        }
        pinfo->fd = cfd;
        memcpy(&pinfo->addr, &cliaddr, size);


        pthread_attr_t attr;
        res = pthread_attr_init(&attr);
        if(res == -1) {
            char* errstr = strerror(res);
            printf("err: %s", errstr);
        }
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
        pthread_create(&pinfo->tid, &attr, sockComu, pinfo);
        pthread_attr_destroy(&attr);
    }
    

    close(lfd);
    return 0;
}
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main() {

    int shmid = shmget(100, 0, IPC_CREAT);
    void* ptr = shmat(shmid, NULL, 0);

    char buf[1024];
    memcpy(buf, ptr, sizeof(buf));
    
    printf("%s", buf);

    shmdt(ptr);

    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
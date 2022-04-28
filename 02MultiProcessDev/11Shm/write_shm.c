#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main() {

    int shmid = shmget(100, 4096, IPC_CREAT | 0664);

    void* ptr = shmat(shmid, NULL, 0);

    char* str = "asdasd";
    memcpy(ptr, str, strlen(str)+1);

    shmdt(ptr);

    shmctl(shmid, IPC_RMID, NULL);


    return 0;
}
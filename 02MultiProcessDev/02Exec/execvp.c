#include <unistd.h>
#include <stdio.h>

int main() {

    pid_t pid = fork();

    if(pid > 0) {
        printf("pa");
    }

    if(pid == 0) {
        char* argv[3];
        argv[0] = "ps";
        argv[1] = "aux";
        argv[2] = NULL;
        execvp("ps", argv);
        perror("execvp");
    }

    return 0;
}
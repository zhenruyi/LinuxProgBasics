#include <unistd.h>
#include <stdio.h>

int main() {

    int rOk = access("a.txt", R_OK);
    int wOK = access("a.txt", W_OK);
    int f2Ok = access("a222.txt", F_OK);
    int fOk = access("a.txt", F_OK);

    if(!fOk) printf("file is exist\n");
    else printf("file is not exist\n");

    if(!f2Ok) printf("file is exist\n");
    else printf("file is not exist\n");

    if(!wOK) printf("can write\n");
    else printf("can not write\n");

    return 0;
}
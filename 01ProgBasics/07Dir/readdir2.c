#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int countFiles(char * path);

int main(int argc, char* argv[]) {

    if(argc < 2) {
        printf("%s path\n", argv[0]);
        exit(0);
    }

    int num = countFiles(argv[1]);

    printf("files num is %d\n", num);

    return 0;
}


int countFiles(char * path) {
    DIR* dir = opendir(path);
    if(dir == NULL) {
        perror("opendir");
        exit(0);
    }

    int count = 0;

    struct dirent* dpt;

    while((dpt = readdir(dir)) != NULL) {
        char* name = dpt->d_name;
        if(strcmp(name, ".") == 0 || strcmp(name, "..") == 0) {
            continue;
        }

        if(dpt->d_type == DT_DIR) {
            char newpath[1024];
            sprintf(newpath, "%s/%s", path, name);
            count += countFiles(newpath);
        }

        if(dpt->d_type == DT_REG) {
            count++;
        }
    }

    closedir(dir);
    return count;
}
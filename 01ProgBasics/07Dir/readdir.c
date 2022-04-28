#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int countFiles(const char* path) {
    DIR* dir = opendir(path);   
    if(dir == NULL) {
        perror("opendir");
        exit(0);
    }
    struct dirent *ptr;
    int total = 0;
    while((ptr = readdir(dir)) != NULL) {
        char* name = ptr->d_name;
        if(strcmp(name, ".") == 0 || strcmp(name, "..") == 0) {
            continue;
        }
        if(ptr->d_type == DT_DIR) {
            char newpath[256];
            sprintf(newpath, "%s/%s", path, name);
            total += countFiles(newpath);
        }
        if(ptr->d_type == DT_REG) {
            total++;
        }
    }
    closedir(dir);
    return total;
}

int main(int argc, char* argv[]) {

    if(argc < 2) {
        printf("%s dir", argv[0]);
        return 0;
    }

    int num = countFiles(argv[1]);
    printf("普通文件的个数为：%d\n", num);

    return 0;
}
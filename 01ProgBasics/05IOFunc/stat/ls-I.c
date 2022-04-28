#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>

int main(int argc, char* argv[]) {

    if(argc < 2) {
        printf("%s filename\n", argv[0]);
        return 0;
    }

    struct stat statbuf;
    int res = lstat(argv[1], &statbuf);
    if(res == -1) {
        printf("filename error");
        return 0;
    }

    char perm[11] = {0};
    mode_t mode = statbuf.st_mode;
    switch(mode & S_IFMT) {
        case S_IFDIR:
            perm[0] = 'd';
            break;
        case S_IFREG:
            perm[0] = '-';
            break;
        default:
            perm[0] = 'o';
    }

    perm[1] = (mode & S_IRUSR) ? 'r' : '-';
    perm[2] = (mode & S_IWUSR) ? 'w' : '-';
    perm[3] = (mode & S_IXUSR) ? 'x' : '-';
    perm[4] = (mode & S_IRGRP) ? 'r' : '-';
    perm[5] = (mode & S_IWGRP) ? 'w' : '-';
    perm[6] = (mode & S_IXGRP) ? 'x' : '-';
    perm[7] = (mode & S_IROTH) ? 'r' : '-';
    perm[8] = (mode & S_IWOTH) ? 'w' : '-';
    perm[9] = (mode & S_IXOTH) ? 'x' : '-';

    int lnkNum = statbuf.st_nlink;

    uid_t uid = statbuf.st_uid;
    char* usr = getpwuid(uid)->pw_name;

    gid_t gid = statbuf.st_gid;
    char* grp = getgrgid(gid)->gr_name;

    off_t size = statbuf.st_size;

    printf("%s %d %s %s %ld %s\n", perm, lnkNum, usr, grp, size, argv[1]);


    return 0;
}


// -rw-rw-r-- 1 zhenruyi zhenruyi 1511 4月  18 05:34 stat.c
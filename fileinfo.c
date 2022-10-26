#include <stdio.h>
#include <sys/stat.h>

void show_stat_info (char *, struct stat *);

int main(int argc, char *argv[]) {
    struct stat info;

    if(argc > 1) {
        if(stat (argv[1], &info) != -1) {
            show_stat_info(argv[1], &info);
        }
    }
}

void show_stat_info(char *fname, struct stat *info) {
    printf("name : %s\n", fname);
    printf("user : %d\n", info->st_uid);
    printf("group : %d\n", info->st_gid);
    printf("size : %ld\n", info->st_size);
    printf("mode : %o\n", info->st_mode);
}
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

void do_ls(char []);

int main(int argc, char *argv[]) {
    int i;
    if(argc == 1)
        do_ls(".");
    else {
        for(i = 1; i < argc; i++) {
            do_ls(argv[1]);
        }
    }
}

void do_ls(char dirname[]) {
    DIR *dirptr;
    struct dirent *direntp;

    dirptr = opendir(dirname);
    if ( dirptr != NULL ) {
        while((direntp = readdir(dirptr)) != NULL) {
            printf("%s \n", direntp->d_name);
        }
        closedir(dirptr);
    }
}
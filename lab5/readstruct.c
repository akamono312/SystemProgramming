#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define MAX_LEN 100
#define BUFFERSIZE 4096

struct Node {
    char name[MAX_LEN];
    int id;
    int num;
};

int main(int argc, char* argv) {
    int fd;
    char buf[BUFFERSIZE];
    struct Node node1, node2;
    
    /* node1 input data */
    node1.id = 12345;
    node1.num = 1;
    strcpy(node1.name, "Kim");

    /* node2 input data */
    node2.id = 25413;
    node2.num = 2;
    strcpy(node2.name, "Jang");
    
    if(argc != 2) {
        fprintf(stderr, "usage: %s source destinaton\n", *argv);
        exit(1);
    }

    if((fd = open(argv[1], O_WRONLY | O_CREAT)) == -1) {
        fprintf(stderr, "file open error\n");
        perror(argv[1]);
        exit(!);
    }
}
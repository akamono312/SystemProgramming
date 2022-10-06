#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#define MAX_LEN 100
#define BUFFERSIZE 4096

struct Node {
    int num;
    int id;
    char name[MAX_LEN];
};

void read_node(int, struct Node);

int main(int argc, char* argv[]) {
    int fd;
    char buf[BUFFERSIZE];
    struct Node node, node1, node2, node3, node4, node5;
    
    if(argc != 2) {
        fprintf(stderr, "usage: %s source destinaton\n", *argv);
        exit(1);
    }

    if((fd = open(argv[1], O_RDONLY)) == -1) {
        fprintf(stderr, "file open error\n");
        perror(argv[1]);
        exit(1);
    }

    read_node(fd, node);
    read_node(fd, node);
    read_node(fd, node);
    read_node(fd, node);
    read_node(fd, node);
    
    close(fd);
    
}

void read_node(int fd, struct Node node) {
    read(fd, &node, sizeof(struct Node));
    printf("num: %d, id: %d, name: %s\n", node.num, node.id, node.name);
}
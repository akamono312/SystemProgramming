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

void write_node(int, struct Node);

int main(int argc, char* argv[]) {
    int fd;
    char buf[BUFFERSIZE];
    struct Node node1, node2, node3, node4, node5;
    
    /* node1 input data */
    node1.id = 12345;
    node1.num = 1;
    strcpy(node1.name, "Kim");

    /* node2 input data */
    node2.id = 25413;
    node2.num = 2;
    strcpy(node2.name, "Jang");

    /* node3 input data */
    node3.id = 34623;
    node3.num = 3;
    strcpy(node3.name, "Park");

    /* node4 input data */
    node4.id = 43267;
    node4.num = 4;
    strcpy(node4.name, "Choi");

    /* node5 input data */
    node5.id = 16436;
    node5.num = 5;
    strcpy(node5.name, "Lee");
    
    if(argc != 2) {
        fprintf(stderr, "usage: %s source destinaton\n", *argv);
        exit(1);
    }

    if((fd = open(argv[1], O_WRONLY | O_CREAT)) == -1) {
        fprintf(stderr, "file open error\n");
        perror(argv[1]);
        exit(1);
    }

    write_node(fd, node1);
    write_node(fd, node2);
    write_node(fd, node3);
    write_node(fd, node4);
    write_node(fd, node5);

    close(fd);
}

void write_node(int fd, struct Node node) {
    write(fd, &node, sizeof(struct Node));
}
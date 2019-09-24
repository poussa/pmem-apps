
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libpmem.h>

#define SIZE  4096
#define OP_READ  0
#define OP_WRITE 1

char *msg = "line item\n";
int op;

char *usage = "usage: %s -r|-w <file>\n";

int main(int argc, char **argv) {

    char *pmemaddr;
    char *path;
    size_t len;
    int is_pmem;

    if (argc != 3) {
        printf(usage, argv[0]);
        exit(1);
    }
    if (strcmp(argv[1], "-r") == 0) {
        op = OP_READ;
    } else if (strcmp(argv[1], "-w") == 0) {
        op = OP_WRITE;
    } else {
        printf(usage, argv[0]);
        exit(0);
    }

    path = argv[2];
    if ((pmemaddr = (char *)pmem_map_file(path, SIZE, PMEM_FILE_CREATE, 0666, &len, &is_pmem)) == NULL) {
        perror("pmem_map_file");
        exit(1);
    }

    printf("pmem: %d, len: %d\n", is_pmem, len);

    if (op == OP_READ) {
        printf("read: %s\n", pmemaddr);
    } else {
        printf("write: %s\n", msg);
        strcpy(pmemaddr, msg);
        if (is_pmem)
            pmem_persist(pmemaddr, len);
        else
            pmem_msync(pmemaddr, len);
    }

    return 0;
}
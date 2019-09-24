#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libpmemobj.h>

POBJ_LAYOUT_BEGIN(transaction);
POBJ_LAYOUT_ROOT(transaction, struct root);
POBJ_LAYOUT_TOID(transaction, struct vector);
POBJ_LAYOUT_END(transaction);

#define SIZE 4096
#define OP_READ 0
#define OP_WRITE 1

char *usage = "usage: %s <pool> -r|-w\n";
int op;

typedef struct vector {
    int x;
    int y;
    int z;
} vector_t;

typedef struct root {
    TOID(struct vector) vector;
} root_t;

int main(int argc, char **argv)
{
    PMEMobjpool *pop;
    char *path;
    size_t len;
    int is_pmem;

    if (argc < 3) {
        printf(usage, argv[0]);
        exit(1);
    }
    path = argv[1];
    if (strcmp(argv[2], "-r") == 0)
    {
        op = OP_READ;
    }
    else if (strcmp(argv[2], "-w") == 0)
    {
        op = OP_WRITE;
    }
    else
    {
        printf(usage, argv[0]);
        exit(0);
    }

    if ((pop = pmemobj_open(path, POBJ_LAYOUT_NAME(transaction))) == NULL) {
        perror(path);
        exit(1);
    }

    PMEMoid root = pmemobj_root(pop, sizeof(vector_t));
    vector_t *root_ptr = pmemobj_direct(root);
    TX_BEGIN(pop) {

    } TX_END {

    }

}
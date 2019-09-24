
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libpmemobj.h>

#define SIZE 4096
#define OP_READ 0
#define OP_WRITE 1

#define LAYOUT "app"

struct root
{
    size_t len;
    char buf[SIZE];
};

char *msg = "line item\n";
int op;

char *usage = "usage: %s <pool> -r|-w\n";

int main(int argc, char **argv)
{

    PMEMobjpool *pop;
    char *path;
    size_t len;
    int is_pmem;

    if (argc != 3)
    {
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

    if (op == OP_READ)
    {
        if ((pop = pmemobj_open(path, LAYOUT)) == NULL)
        {
            perror(path);
            exit(1);
        }
        PMEMoid root = pmemobj_root(pop, sizeof(struct root));
        struct root *root_ptr = pmemobj_direct(root);
        printf("r: %s", root_ptr->buf);
    }
    else if (op == OP_WRITE)
    {
        if ((pop = pmemobj_create(path, LAYOUT, PMEMOBJ_MIN_POOL, 0666)) == NULL)
        {
            perror(path);
            exit(1);
        }
        PMEMoid root = pmemobj_root(pop, sizeof(struct root));
        struct root *root_ptr = pmemobj_direct(root);
        root_ptr->len = strlen(msg);
        // first, sync len (4 bytes)
        pmemobj_persist(pop, &root_ptr->len, sizeof(root_ptr->len));
        // next, then sync the string
        pmemobj_memcpy_persist(pop, root_ptr->buf, msg, root_ptr->len);
        printf("w: %s", root_ptr->buf);
        pmemobj_close(pop);
    }

    return 0;
}
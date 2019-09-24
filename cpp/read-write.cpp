#include "read-write.hpp"

#define OP_READ 0
#define OP_WRITE 1

char usage[] = "usage: %s <pool> -r|-w\n";
char input [] = "line item";
int op;

int main(int argc, char **argv) {
    pmem::obj::pool<root> pop;
    pmem::obj::persistent_ptr<root> pool;
    char *path;

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

    pop = pmem::obj::pool<root>::open(path, LAYOUT);
    pool = pop.root();

    if (op == OP_READ) {
        cout << pool->hello->get_msg();

    } else if (op == OP_WRITE) {
        pmem::obj::make_persistent_atomic<Hello>(pop, pool->hello, input);
    }
    pop.close();

}
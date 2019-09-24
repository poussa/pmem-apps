#include "queue.hpp"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <functional>

namespace {
#define OP_PUSH 0
#define OP_POP  1
#define OP_SHOW 2


const char *LAYOUT = "queue";
const char *usage = "usage: %s <pool> [v|p] [push value | pop | show]\n";

struct root {
    pmem::obj::persistent_ptr<PersistentQueue> p_queue;
    VolatileQueue *v_queue;
};

bool
file_exists(const std::string &path)
{
	std::ifstream f(path.c_str());
	return f.good();
}
};

int main(int argc, char **argv)
{
    if (argc < 4)
    {
        printf(usage, argv[0]);
        exit(1);
    }
    std::string pool{argv[1]};
    std::string type{argv[2]};
    std::string op{argv[3]};
    long value = 10;

    if (argc == 4) {
    	/* lambda get value for push operation */
    	auto v = [&argv]() -> long { return atoll(argv[4]); };
    }

    pmem::obj::pool<root> pop;
    if (file_exists(pool)) {
        pop = pmem::obj::pool<root>::open(pool, LAYOUT);
    } else {
        std::cerr << "eeeor";
        exit(1);
    }
    auto root = pop.root();

    // allocate volatile queue
    root->v_queue = new VolatileQueue();

    if (type == "v") {
        if (op == "show")
            std::cout << root->v_queue->show() << std::endl;
        if (op == "push")
            root->v_queue->push(value);
        if (op == "pop")
            root->v_queue->pop();
    } else if (type == "p") {
        if (op == "show")
            std::cout << root->p_queue->show() << std::endl;
        if (op == "push")
            root->p_queue->push(value);
        if (op == "pop")
            root->p_queue->pop();
    } else {
        std::cerr << "err";
    }

}
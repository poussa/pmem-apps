#include <libpmemobj++/make_persistent.hpp>
#include <libpmemobj++/make_persistent_atomic.hpp>
#include <libpmemobj++/p.hpp>
#include <libpmemobj++/persistent_ptr.hpp>
#include <libpmemobj++/pool.hpp>

#include <fstream>
#include <iostream>
#include <string.h>

#define SIZE 64
#define LAYOUT "app"

using namespace std;
//namespace pobj = pmem::obj;

class Hello
{
private:
    char msg[SIZE] = {0};

public:
    Hello(char *input)
    {
        strcpy(msg, input);
    }
    char *get_msg() {
        return msg;
    }
};

struct root {
    pmem::obj::persistent_ptr<Hello> hello;
};
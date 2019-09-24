#include <memory>
#include <utility>
#include <libpmemobj++/p.hpp>
#include <libpmemobj++/persistent_ptr.hpp>

class VolatileQueue
{
private:
    struct Node
    {
        Node(long value, std::shared_ptr<Node> n)
            : next(std::move(n)), value(std::move(value))
        {
        }
        long value;
        std::shared_ptr<Node> next;
    };
    std::shared_ptr<Node> head;
    std::shared_ptr<Node> tail;
    
public:
    void push(long value);
    long pop(void);
    std::string show(void) const;
};

class PersistentQueue
{
private:
    struct Node
    {
        Node(long value, pmem::obj::persistent_ptr<Node> n)
            : next(std::move(n)), value(std::move(value))
        {
        }
        pmem::obj::persistent_ptr<Node> next;
        long value;
    };
    pmem::obj::persistent_ptr<Node> head;
    pmem::obj::persistent_ptr<Node> tail;
public:
    void push(long value);
    long pop(void);
    std::string show(void) const;
};

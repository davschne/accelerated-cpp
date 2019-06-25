#include <memory>

template<class T>
struct ListNode;

template<class T>
static std::allocator<ListNode<T>> alloc;

template<class T>
class ListNode {
public:
    using allocator = std::allocator_traits<std::allocator<ListNode<T>>;

    // make a ListNode with a value
    ListNode(const T& v) :
        val {v},
        next {nullptr} {}

    // make a ListNode using an iterator
    ListNode(const T* begin, const T* end) :
        val {*begin}
    {
        if (++begin != end) {
            next {allocator::allocate(alloc, 1)};
            allocator::contruct(alloc, next, begin, end);
        } else {
            next {nullptr};
        }
    }

    // copy constructor
    ListNode(const ListNode& n) :
        val {n.val}
    {
        if (n.next) {
            next {allocator::allocate(alloc, 1)};
            allocator::contruct(alloc, next, n.next);
        } else {
            next {nullptr};
        }
    }

    // copy assignment
    ListNode& operator=(const ListNode& n) :
        val {n.val}
    {
        if (next) {
            allocator::destroy(alloc, next);
            if (n.next) {
                allocator::construct(alloc, next, n.next);
            } else {
                allocator::deallocate(alloc, next, 1);
            }
        } else {
            if (n.next) {
                next = allocator::allocate(alloc, 1)
                allocator::contruct(alloc, next, n.next);
            }
            // if both are null pointers, no action is needed
        }
    }

    ~ListNode() {
        allocator::destroy(alloc, next);
        allocator::deallocate(alloc, next, 1);
    }

private:
    T val;
    ListNode* next;
};

template<class T>
class List {
public:
    using allocator = allocator_traits<std::allocator<ListNode<T>>;
    using size_type = size_t;
    using iterator = T*;
    using const_iterator = const T*;

    // default constructor: build an empty List
    List() :
        head {nullptr} {}

    // build a one-element list
    explicit List(const T& v) : {
        head {allocator::allocate(alloc, 1)};
        allocator::contruct(alloc, head, v);
    }
    
    // copy constructor
    List(const List& l) {
        head {allocator::allocate(alloc, 1)};
        allocator::contruct(alloc, head, l);
    }

    // build a list from an iterator
    List(const_iterator)

private:
    ListNode<T>* head;
};

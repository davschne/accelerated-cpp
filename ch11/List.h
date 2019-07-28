// Exercise 11-8. Write a simplified version of the standard `list` class and its associated iterator.

#ifndef List_h
#define List_h

#include <cctype>

template<class T> class List;

template<class T>
class ListNode {
    friend List<T>;
public:
    // make a ListNode with a value
    explicit ListNode(const T& v) :
        h {v},
        t {nullptr}
    { }

    // make a ListNode using a pair of iterators
    template<class It>
    ListNode(It begin, It end) :
        h {*begin},
        t {(++begin != end) ? new ListNode<T>(begin, end) : nullptr}
    { }

    // copy
    ListNode(const ListNode& n) :
        h {n.h},
        t {n.t ? new ListNode(*n.t) : nullptr}
    { }

    ListNode& operator=(const ListNode& n) {
        if (this != &n) {
            h = n.h;
            delete t; // if nullptr, should be no-op
            t = n.t ? new ListNode(*n.t) : nullptr;
        }
        return *this;
    }

    // move
    ListNode(ListNode&& n) :
        h {n.h},
        t {n.t}
    {
        n.t = nullptr;
    }

    ListNode& operator=(ListNode&& n) {
        h = n.h;
        swap(t, n.t);
        return *this;
    }

    ~ListNode() { delete t; }

private:
    T h;
    ListNode* t;
};

template<class T>
class List {
public:
    class iterator {
    public:
        iterator() : p {nullptr} { }
        explicit iterator(ListNode<T>* l) : p {l} { }

        T& operator*() { return p->h; }
        ListNode<T>* operator->() { return p; }

        iterator& operator++() {
            p = p->t;
            return *this;
        }

        bool operator==(const iterator& rhs) const {
            return p == rhs.p;
        }

        bool operator!=(const iterator& rhs) const {
            return !(*this == rhs);
        }
    private:
        ListNode<T>* p;
    };

    class const_iterator {
    public:
        const_iterator() : p {nullptr} { }
        explicit const_iterator(const ListNode<T>* l) : p {l} { }

        const T& operator*() const { return p->h; }
        const ListNode<T>* operator->() const { return p; }

        const_iterator& operator++() {
            p = p->t;
            return *this;
        }

        bool operator==(const const_iterator& rhs) const {
            return p == rhs.p;
        }

        bool operator!=(const const_iterator& rhs) const {
            return !(*this == rhs);
        }
    private:
        const ListNode<T>* p;
    };

    using size_type = std::size_t;

    // default constructor: make an empty list
    List() : p {nullptr} { }
    // make a one-lement List with a value
    explicit List(const T& v) : p {new ListNode<T>(v)} { }
    // make a List using a pair of iterators
    template<class It>
    List(It begin, It end) :
        p {begin != end ? new ListNode<T>(begin, end) : nullptr}
    { }

    // copy
    List(const List& l) :
        p {l.p ? new ListNode<T>(*l.p) : nullptr}
    { }
    List& operator=(const List& l) {
        if (this != &l) {
            delete p;
            p = l.p;
        }
        return *this;
    }

    // move
    List(List&& l) : p {l.p} { l.p = nullptr; }
    List& operator=(List&& l) {
        swap(p, l.p);
    }

    ~List() { delete p; }

    bool operator==(const List<T>& l) const {
        const_iterator this_it {begin()};
        const_iterator that_it {l.begin()};
        while (this_it != end() && that_it != l.end()) {
            if (*this_it != *that_it) return false;
            ++this_it;
            ++that_it;
        }
        // If we've reached the end of both, the Lists are equal; otherwise not.
        return this_it == end() && that_it == l.end();
    }
    bool operator!=(const List<T>& l) const {
        return !(*this == l);
    }

    const T& head() const { return p->h; }
    T& head() { return p->h; }

    const List& tail() const { return new List(*p); }
    List& tail() { return new List(*p); }

    const_iterator begin() const { return const_iterator {p}; }
    const_iterator   end() const { return const_iterator {}; }

    iterator begin() { return iterator {p}; }
    iterator   end() { return iterator {}; }

    size_type size() const {
        size_type count {0};
        const_iterator it {begin()};
        while (it != end()) {
            ++it;
            ++count;
        }
        return count;
    }

    void push_back(const T& v) {
        size_type sz {size()};
        iterator it {begin()};
        size_type count {0};
        while (count != sz - 1) {
            ++it;
            ++count;
        }
        it->t = new ListNode<T>(v);
    }

private:
    ListNode<T>* p;
};

#endif

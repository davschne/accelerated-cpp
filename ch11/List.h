// Exercise 11-8. Write a simplified version of the standard `list` class and its associated iterator.

#ifndef List_h
#define List_h

#include <cctype>

template<class T>
class List {
public:
    class iterator {
    public:
        iterator() : p {nullptr} { }
        explicit iterator(List* l) : p {l} { }

        T& operator*() { return p->h; }
        List<T>* operator->() { return p; }

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
        List* p;
    };

    class const_iterator {
    public:
        const_iterator() : p {nullptr} { }
        explicit const_iterator(const List* l) : p {l} { }

        const T& operator*() const { return p->h; }
        const List<T>* operator->() const { return p; }

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
        const List* p;
    };

    using size_type = std::size_t;

    // make a one-element List with a value
    explicit List(const T& v) :
        h {v},
        t {nullptr}
    { }

    // make a List using an iterator
    template<class It>
    List(It begin, It end) :
        h {*begin},
        t {(++begin != end) ? new List<T>(begin, end) : nullptr}
    { }

    // copy
    List(const List& l) :
        h {l.h},
        t {l.t ? new List(*l.t) : nullptr}
    { }

    List& operator=(const List& l) {
        h = l.h;
        delete t; // if nullptr, should be no-op
        t = l.t ? new List(*l.t) : nullptr;
    }

    // move
    List(List&& l) :
        h {l.h},
        t {l.t}
    {
        l.t = nullptr;
    }

    List& operator=(List&& l) {
        h = l.h;
        swap(t, l.t);
    }

    ~List() { delete t; }

    bool operator==(const List& l) const {
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
    bool operator!=(const List& l) const {
        return !(*this == l);
    }

    const T& head() const { return h; }
    T& head() { return h; }

    const List& tail() const { return *t; }
    List& tail() { return *t; }

    const_iterator begin() const { return const_iterator {this}; }
    const_iterator   end() const { return const_iterator {}; }

    iterator begin() { return iterator {this}; }
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
        it->t = new List(v);
    }

private:
    T h;
    List* t;
};

#endif

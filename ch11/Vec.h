#ifndef VEC_h
#define VEC_h

#include <memory>

template <class T> class Vec {
public:
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef size_t size_type;
    typedef T value_type;
    typedef std::ptrdiff_t difference_type;
    typedef T& reference;
    typedef const T& const_reference;

    Vec() { create(); }
    explicit Vec(size_type n, const T& val = T()) { create(n, val); }

    // copy constructor
    Vec(const Vec& v) { create(v.begin(), v.end()); }
    // move constructor
    Vec(Vec&& v);

    // copy assignment
    Vec& operator=(const Vec&);
    // move assignment
    Vec& operator=(Vec&&);

    ~Vec() { uncreate(); }

    size_type size() const { return avail - data; }
    bool empty() const { return data; }

    T& operator[](size_type i) { return data[i]; }
    const T& operator[](size_type i) const { return data[i]; }
    
    iterator begin() { return data; }
    const_iterator begin() const { return data; }

    iterator end() { return avail; }
    const_iterator end() const { return avail; }

    void push_back(const T&);
    iterator erase(const_iterator);
    void clear() { uncreate(); }

private:
    // Class invariants:
    // 1. `data` points at our initial data element, if we have any, and is 0 otherwise
    // 2. data <= avail <= limit
    // 3. Elements have been constructed in the range [data, avail)
    // 4. Elements have not been constructed in the range [avail, limit)
    iterator data;  // first element in the Vec
    iterator avail; // one past the last constructed element
    iterator limit; // one past the last available element

    // facilities for memory allocation

    // object to handle memory allocation
    std::allocator<T> alloc;

    // allocate and initialize the underlying array
    void create();
    void create(size_type, const T&);
    void create(const_iterator, const_iterator);

    // destroy the elements in the array and free the memory
    void uncreate();

    // support functions for `push_back`
    void grow();
    void unchecked_append(const T&);

    // support function for `erase`
    void shrink();
};

template <class T>
Vec<T>& Vec<T>::operator=(const Vec& rhs) {
    // check for self-assignment
    if (&rhs != this) {
        // free the array in the left-hand side
        uncreate();

        // copy elements from the right-hand side to the left-hand side
        create(rhs.begin(), rhs.end());
    }

    return *this;
}

// move constructor
template <class T>
Vec<T>::Vec(Vec&& v) :
    // copy v's representation
    data {v.data}, avail {v.avail}, limit {v.limit}
{
    // set null pointers for v's represention, so its destructor doesn't try
    // to free the memory whose ownership was just transferred to the current Vec
    v.data = v.avail = v.limit = nullptr;
}

// move assignment
template <class T>
Vec<T>& Vec<T>::operator=(Vec&& v) {
    // swap representations
    // v's destructor will clean up this Vec's previous representation
    std::swap(data, v.data);
    std::swap(avail, v.avail);
    std::swap(limit, v.limit);
    return *this;
}

template <class T>
void Vec<T>::push_back(const T& val) {
    // get space if needed
    if (avail == limit) {
        grow();
    }
    // append the new element
    unchecked_append(val); 
}

template <class T>
typename Vec<T>::iterator Vec<T>::erase(const_iterator i) {
    // shrink the memory allocation if the size is less than 1/4 the available space
    if (size() < (limit - data) / 4) {
        shrink();
    }
    if (avail) {
        alloc.destroy(i--);
        avail = i;
    }
    return avail;
}

template <class T>
void Vec<T>::shrink() {
    // when shrinking, allocate half as much space as currently in use
    size_type new_size = std::max((limit - data) / 2, std::ptrdiff_t(1));

    // allocate new space and copy existing elements into it
    iterator new_data = alloc.allocate(new_size);
    iterator new_avail = std::uninitialized_copy(data, avail, new_data);

    // free the old space
    uncreate();

    // reset pointers to point to the newly allocated space
    data = new_data;
    avail = new_avail;
    limit = data + new_size;
}

template <class T>
void Vec<T>::create() {
    // use null pointers for the data members to indicate an empty array
    data = avail = limit = nullptr;
}

template <class T>
void Vec<T>::create(size_type n, const T& val) {
    // allocate enough memory for `n` elements of type `T`
    data = alloc.allocate(n);
    // set `avail` and `limit` to one past the allocated memory
    limit = avail = data + n;
    // construct `n` copies of `val` in the allocated memory
    std::uninitialized_fill(data, limit, val);
}

template <class T>
void Vec<T>::create(const_iterator i, const_iterator j) {
    // allocate enough space to store the incoming elements
    data = alloc.allocate(j - i);
    // copy elements into the allocated space, using the input iterators
    // set `avail` and `limit` to one past the allocated space
    limit = avail = std::uninitialized_copy(i, j, data);
}

template <class T>
void Vec<T>::uncreate() {
    // if the Vec is nonempty
    if (data) {
        // destroy the constructed elements
        // (in reverse order, to match the behavior of `delete[]`)
        for (iterator i = avail - 1; i >= data; --i) {
            alloc.destroy(i);
        }
        // free allocated space
        alloc.deallocate(data, limit - data);
        // reset pointers to indicate that the `Vec` is empty
        data = avail = limit = nullptr;
    }
}

template <class T>
void Vec<T>::grow() {
    // when growing, allocate twice as much space as currently in use
    size_type new_size = std::max(2 * (limit - data), std::ptrdiff_t(1));

    // allocate new space and copy existing elements into it
    iterator new_data = alloc.allocate(new_size);
    iterator new_avail = std::uninitialized_copy(data, avail, new_data);

    // free the old space
    uncreate();

    // reset pointers to point to the newly allocated space
    data = new_data;
    avail = new_avail;
    limit = data + new_size;
}

// assumes `avail` points at allocated (but uninitialized) space
template <class T>
void Vec<T>::unchecked_append(const T& val) {
    alloc.construct(avail++, val);
}

#endif

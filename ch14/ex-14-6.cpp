// 14-6. The `Ptr` class really solves two problems: maintaining reference counts and allocating and
// deallocating objects. Define a class that does reference counting and nothing else; then use that
// class to reimplement the `Ptr` class.

#include <cstddef>


// Defining `clone` as a non-member function allows us to define specializations for classes that
// don't have member function `clone`.
template<class T>
T* clone(const T* tp) {
    return tp->clone();
}

class Ref_count {
public:
    Ref_count(): p {new std::size_t(1)} { }
    Ref_count(const Ref_count& rc): p {rc.p} { ++*p; }
    Ref_count& operator=(const Ref_count& rhs) {
        // by incrementing rhs's ref count eagerly, we ensure self-assignment works as expected
        ++*rhs.p;
        if (--*p == 0) delete p;
        p = rhs.p;
        return *this;
    }

    ~Ref_count() {
        if (--*p == 0) delete p;
    }

    std::size_t count() const { return *p; }

private:
    std::size_t* p;
};

template<class T>
class Ptr {
public:
    // new member to copy the object when needed
    void make_unique() {
        if (counter.count() != 1) {
            counter = Ref_count {};
            p = p ? clone(p) : nullptr;
        }
    }

    // the rest is essentially the same as `Ref_handle`
    Ptr(): p {nullptr} { }
    Ptr(T* t): p {t} { }

    Ptr(const Ptr& h): p {h.p}, counter {h.counter} { }
    Ptr& operator=(const Ptr& rhs) {
        if (counter.count() == 1 && rhs.p != p) delete p;
        p = rhs.p;
        counter = rhs.counter;
        return *this;
    }

    ~Ptr() {
        // only delete underlying value if no other references remain
        if (counter.count() == 1) delete p;
    }

    operator bool() const { return p; }
    T& operator*()  const { return *p; }
    T* operator->() const { return p; }

    std::size_t num_references() const {
        return counter.count();
    }

private:
    T* p;
    Ref_count counter;
};

#include <cassert>
#include <string>

using namespace std;

// Define a specialization of `clone` for `string`, which we'll use in the tests.
template<>
string* clone(const string* tp) {
    return new string {*tp};
}

int main() {
    Ptr<string> p1_a {new string {"a"}};
    assert(p1_a.num_references() == 1);
    Ptr<string> p2_a {p1_a};
    assert(
        p2_a.num_references() == p1_a.num_references()
        && p1_a.num_references() == 2
    );
    assert(*p2_a == *p1_a);
    p2_a.make_unique();
    assert(p2_a.num_references() == 1);
    assert(p1_a.num_references() == 1);

    return 0;
}

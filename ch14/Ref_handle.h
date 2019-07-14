// 14.2/260

// reference-counted handle that manages memory for a polymorphic object
// copying a handle does not copy the underlying object; it is shared among copies

template<class T>
class Ref_handle {
public:
    // manage reference count as well as pointer to the object
    Ref_handle():     p {nullptr}, refptr {new std::size_t {1}} { }
    Ref_handle(T* t): p {t},       refptr {new std::size_t {1}} { }

    // copy and assignment don't copy the underlying object
    Ref_handle(const Ref_handle& h): p {h.p}, refptr {h.refptr} { ++*refptr; }
    Ref_handle& operator=(const Ref_handle& rhs) {
        // by incrementing rhs's refcount eagerly, we ensure self-assignment works as expected
        ++*rhs.refptr;
        if (--*refptr == 0) {
            delete p;
            delete refptr;
        }
        p = rhs.p;
        refptr = rhs.refptr;
        return *this;
    }

    // Because Ref_handle never copies the underlying object when copying or assigning, there's no
    // need to define move operations.

    ~Ref_handle() {
        // only delete underlying values if no references remain
        if (--*refptr == 0) {
            delete p;
            delete refptr;
        }
    }

    // same as Handle
    operator bool() const { return p; }
    T& operator*() const {
        if (p) return *p;
        else throw std::runtime_error("unbound Ref_handle");
    }
    T* operator->() const {
        if (p) return p;
        else throw std::runtime_error("unbound Ref_handle");
    }

private:
    // pointer to the underlying object (shared among copies)
    T* p;
    // pointer to a count of Ref_handles (shared among copies)
    std::size_t* refptr;
};

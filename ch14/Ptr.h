// 14.3/263, 14.4.1/266

// handle that only copies the underlying object if needed (i.e. when modified)

template<class T>
class Ptr {
public:
    // new member to copy the object when needed
    void make_unique() {
        if (*refptr != 1) {
            --*refptr;
            refptr = new size_t {1};
            p = p ? clone(p) : nullptr;
        }
    }

    // the rest is essentially the same as `Ref_handle`
    Ptr():     p {nullptr}, refptr {new size_t(1)} { }
    Ptr(T* t): p {t},       refptr {new size_t(1)} { }

    Ptr(const Ptr& h): p {h.p}, refptr {h.refptr} {
        ++*refptr;
    }
    Ptr& operator=(const Ptr& rhs) {
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

    ~Ptr() {
        // only delete underlying values if no references remain
        if (--*refptr == 0) {
            delete p;
            delete refptr;
        }
    }

    operator bool() const { return p; }
    T& operator*()  const { return *p; }
    T* operator->() const { return p; }

private:
    T* p;
    std::size_t* refptr;
};

// Defining `clone` as a non-member function allows us to define specializations for classes that
// don't have member function `clone`.
template<class T>
T* clone(const T* tp) {
    return tp->clone();
}

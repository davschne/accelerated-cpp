#ifndef HANDLE_H
#define HANDLE_H

// 14.1.1/255

// handle that manages memory for polymorphic object
// copying a handle copies the underlying object

template<class T>
class Handle {
public:
    Handle(): p {nullptr} { }

    Handle(const Handle& s):
        p {s.p ? s.p->clone() : nullptr}
    { }
    // assignment copies the underlying object
    Handle& operator=(const Handle& rhs) {
        if (&rhs != this) {
            delete p;
            p = rhs.p ? rhs.p->clone() : 0;
        }
        return *this;
    }

    Handle(Handle&& s): p {s.p} {
        s.p = nullptr;
    }
    Handle& operator=(Handle&& rhs) {
        std::swap(p, rhs.p);
        return *this;
    }

    ~Handle() { delete p; }

    Handle(T* t): p {t} { }

    // is the handle bound to an object?
    operator bool() const { return p; }

    // get the object (as ref)
    T& operator*() const {
        if (p) {
            return *p;
        }
        throw runtime_error("unbound Handle");
    }

    // get the object (as ptr)
    T* operator->() const {
        if (p) {
            return p;
        }
        throw runtime_error("unbound Handle");
    }

private:
    T* p;
};

#endif

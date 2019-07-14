// 14.1.2/258

// Student_info rewritten to defer memory management to Handle

#include "Handle.h"
#include "Core.h"
#include "Grad.h"

class Student_info {
public:
    Student_info() { }
    Student_info(std::istream& is) { read(is); }

    // no copy, assignment, or destructor needed

    std::istream& read(std::istream& is) {
        char ch;
        // get record type
        is >> ch;

        // allocate new object of the appropriate type
        // use Handle<T>(T*) to build a Handle<Core> from Core* and
        // call Handle<T>::operator= to assign Handle<Core> to the left-hand side
        cp = Handle<Core>(ch == 'U' ? new Core {is} : new Grad {is});

        return is;
    }

    // forward call to the underlying object
    std::string name() const {
        if (cp) return cp->name();
        else throw std::runtime_error("uninitialized Student");
    }

    // forward call to the virtual function `grade` of the underlying (polymorphic) object
    double grade() const {
        if (cp) return cp->grade();
        else throw std::runtime_error("uninitialized Student");
    }

    // compare two Student_info objects
    static bool compare(const Student_info& a, const Student_info& b) {
        return a.name() < b.name();
    }

private:
    Handle<Core> cp;
};

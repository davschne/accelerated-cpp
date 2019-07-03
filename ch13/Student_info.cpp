#include "Core.h"
#include "Grad.h"
#include "Student_info.h"

using namespace std;

// COPY
Student_info::Student_info(const Student_info& s) : cp {s.cp ? s.cp->clone() : nullptr} { }
Student_info& Student_info::operator=(const Student_info& s) {
    if (&s != this) {
        delete cp;
        cp = s.cp ? s.cp->clone() : nullptr;
    }
    return *this;
}

// MOVE
Student_info::Student_info(Student_info&& s) : cp {s.cp} { s.cp = nullptr; }
Student_info& Student_info::operator=(Student_info&& s) {
    swap(cp, s.cp);
    return *this;
}

istream& Student_info::read(istream& is) {
    // delete previous object, if any
    delete cp;

    // get record type (U = undergrad; G = grad)
    char ch;
    is >> ch;

    cp = ch == 'U' ? new Core(is) : new Grad(is);

    return is;
}

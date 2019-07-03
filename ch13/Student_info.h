#ifndef STUDENT_INFO_h
#define STUDENT_INFO_h

#include "Core.h"

class Student_info {
public:
    // constructors and copy control
    Student_info(): cp {nullptr} { }
    Student_info(std::istream& is): cp {nullptr} { read(is); }

    Student_info(const Student_info&);
    Student_info(Student_info&&);
    Student_info& operator=(const Student_info&);
    Student_info& operator=(Student_info&&);
    ~Student_info() { delete cp; }

    // operations
    std::istream& read(std::istream&);

    std::string name() const {
        if (cp) return cp->name();
        else throw std::runtime_error("uninitialized Student");
    }

    double grade() const {
        if (cp) return cp->grade();
        else throw std::runtime_error("uninitialized Student");
    }

    static bool compare(const Student_info& a, const Student_info& b) {
        return a.name() < b.name();
    }

private:
    Core* cp;
};

#endif

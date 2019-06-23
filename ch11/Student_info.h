#ifndef STUDENT_INFO_h
#define STUDENT_INFO_h

#include <iostream>
#include <string>

#include "Vec.h"

class Student_info {
public:
    Student_info();
    explicit Student_info(std::istream&);
    Student_info(const Student_info&);
    ~Student_info();

    Student_info& operator=(const Student_info&);

    std::istream& read(std::istream&);
    bool valid() const { return !homework.empty(); }
    const std::string& name() const { return n; }
    double grade() const;

private:
    std::string n;
    double midterm, final;
    Vec<double> homework;
};

bool compare(const Student_info&, const Student_info&);

#endif

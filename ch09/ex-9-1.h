/**
 * Ex. 9-1. Reimplement the `Student_info` class so that it calculates the final grade when
 * reading the student's record, and stores that grade in the object. Reimplement the grade
 * function to use this precomputed value.
 */

#ifndef STUDENT_INFO_h
#define STUDENT_INFO_h

#include <iostream>
#include <string>
#include <vector>

class Student_info {
public:
    Student_info();
    explicit Student_info(std::istream&);

    std::istream& read(std::istream&);
    bool valid() const { return is_valid; }
    const std::string& name() const { return n; }
    double grade() const { return final_grade; };

private:
    std::string n;
    double final_grade;
    bool is_valid;
};

bool compare(const Student_info&, const Student_info&);

#endif

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
    bool valid() const { return !homework.empty(); }
    const std::string& name() const { return n; }
    double grade() const;

private:
    std::string n;
    double midterm, final;
    std::vector<double> homework;
};

bool compare(const Student_info&, const Student_info&);

#endif

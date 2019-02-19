#ifndef GUARD_Student_info
#define GUARD_Student_info

// The preprocessor directives above guard against including this header more than once.

#include <iostream>
#include <string>
#include <vector>

// In a header file, we avoid `using` declarations, because we don't want to clutter a client's symbol table with aliases.

struct Student_info {
    std::string name;
    double midterm, final;
    std::vector<double> homework;
};

bool compare(const Student_info&, const Student_info&);
std::istream& read(std::istream&, Student_info&);
std::istream& read_hw(std::istream&, std::vector<double>&);

#endif

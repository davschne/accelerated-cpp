#include <iostream>
#include <string>
#include <vector>

#include "Student_info.h"

using std::istream;
using std::vector;

bool compare(const Student_info& x, const Student_info& y) {
    return x.name < y.name;
}

// read from an input stream to obtain a student's info
istream& read(istream& is, Student_info& s) {
    // read and store the student's name and midterm and final exam grades
    is >> s.name >> s.midterm >> s.final;

    read_hw(is, s.homework);

    return is;
}

// read homework grades from an input stream into a `vector<double>`
istream& read_hw(istream& in, vector<double>& hw) {
    if (in) {
        // get rid of previous vector contents
        hw.clear();

        // read homework grades
        double x;
        while (in >> x)
            hw.push_back(x);
        
        // clear the stream error state so that input will work for the next student
        in.clear();
    }
    return in;
}

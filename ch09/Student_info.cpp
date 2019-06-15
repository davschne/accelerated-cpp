#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Student_info.h"
#include "median.h"

using namespace std;

bool compare(const Student_info& x, const Student_info& y) {
    return x.name() < y.name();
}

// default constructor
Student_info::Student_info() : midterm {0}, final {0} { }

Student_info::Student_info(istream& is) { read(is); }

istream& Student_info::read(istream& is) {
    is >> n >> midterm >> final;
    if (is) {
        // get rid of previous vector contents
        homework.clear();

        // read homework grades
        double x;
        while (is >> x)
            homework.push_back(x);
        
        // clear the stream error state so that input will work for the next student
        is.clear();
    }
    return is;
}

// compute a student's overall grade from midterm, final, and homework grades
double Student_info::grade() const {
    if (homework.size() == 0)
        throw domain_error("student has done no homework");
    else
        return 0.2 * midterm
        + 0.4 * final
        + 0.4 * median(homework);
}

#include <stdexcept>
#include <vector>
#include "grade.h"
#include "median.h"
#include "Student_info.h"

using std::domain_error;
using std::vector;

// compute a student' overall grade from midterm, final, and homework grades
double grade(double midterm, double final, double homework) {
    return 0.2 * midterm
        + 0.4 * final
        + 0.4 * homework;
}

// compute a student's overall grade from midterm and final exam grades and vector of homework grades
double grade(double midterm, double final, const vector<double>& hw) {
    if (hw.size() == 0)
        throw domain_error("student has done no homework");
    else return grade(midterm, final, median(hw));
}

// compute a student's overall grade given a Student_info record
double grade(const Student_info& s) {
    return grade(s.midterm, s.final, s.homework);
}

// Does the student have a failing grade?
bool fgrade(const Student_info& s) {
    return grade(s) < 60;
}

// Does the student have a passing grade?
bool pgrade(const Student_info& s) {
    return !fgrade(s);
}

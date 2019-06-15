/**
 * Ex. 9-1. Reimplement the `Student_info` class so that it calculates the final grade when
 * reading the student's record, and stores that grade in the object. Reimplement the grade
 * function to use this precomputed value.
 */

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "ex-9-1.h"
#include "median.h"

using namespace std;

bool compare(const Student_info& x, const Student_info& y) {
    return x.name() < y.name();
}

// helper function:
// compute a student's overall grade from midterm, final, and homework grades
// invariant: `homework` is a non-empty vector
double compute_grade(
    double midterm,
    double final,
    const vector<double>& homework
) {
    return 0.2 * midterm
    + 0.4 * final
    + 0.4 * median(homework);
}

// default constructor
Student_info::Student_info() : final_grade {0}, is_valid {false} { }

Student_info::Student_info(istream& is) { read(is); }

istream& Student_info::read(istream& is) {
    double midterm, final;
    vector<double> homework;

    is >> n >> midterm >> final;

    if (is) {
        // read homework grades
        double x;
        while (is >> x)
            homework.push_back(x);
        
        // clear the stream error state so that input will work for the next student
        is.clear();
    }

    if (homework.size() == 0)
        throw domain_error("student " + n + " has done no homework");

    final_grade = compute_grade(midterm, final, homework);
    is_valid = true;

    return is;
}

int main() {
    vector<Student_info> students;
    string::size_type maxlen {0};

    // Create student records until end of input.
    while (!(cin >> ws).eof()) {
        try {
            Student_info record(cin);
            maxlen = max(maxlen, record.name().size());
            students.push_back(record);
        } catch (domain_error e) {
            cout << e.what() << endl;
        }
    }

    // alphabetize the student records
    sort(students.begin(), students.end(), compare);

    // write the names and grades
    for (const auto& student : students) {
        cout << student.name()
             << string(maxlen + 1 - student.name().size(), ' ');

        double final_grade = student.grade();
        auto prec = cout.precision();
        cout << setprecision(3) << final_grade
             << setprecision(prec) << endl;
    }

    return 0;
}

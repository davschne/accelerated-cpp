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

#include "Vec.h"
#include "Student_info.h"
#include "median.h"

using namespace std;

int main() {
    Vec<Student_info> students;
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

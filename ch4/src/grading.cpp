// 4.5/70

#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "grade.h"
#include "Student_info.h"

using std::cin;
using std::cout;
using std::domain_error;
using std::endl;
using std::max;
using std::setprecision;
using std::sort;
using std::streamsize;
using std::string;
using std::vector;

int main() {
    vector<Student_info> students;
    Student_info record;
    string::size_type maxlen = 0;

    // read and store all the students' data
    // Invariant:
    //   `students` contains all the student records read so far
    //   `maxlen` contains the length of the longest name in `students`
    while (read(cin, record)) {
        // find length of longest name so far
        maxlen = max(maxlen, record.name.size());
        students.push_back(record);
    }

    // alphabetize the student records
    sort(students.begin(), students.end(), compare);

    // write the names and grades
    for (vector<Student_info>::size_type i = 0;
        i != students.size();
        ++i
    ) {
        string& name = students[i].name;
        // write the name, padded on the right to `maxlen + 1` characters
        cout << name << string(maxlen + 1 - name.size(), ' ');

        // compute and write the grade
        try {
            // The call to `grade` might throw (if we don't have any homework records), so we put it in its own statement.
            // That way we don't cause any side effects if `grade` throws.
            double final_grade = grade(students[i]);
            streamsize prec = cout.precision();
            cout << setprecision(3) << final_grade << setprecision(prec);
        } catch (domain_error e) {
            // method `what` on an error object returns the error message, if any
            cout << e.what();
        }
        cout << endl;
    }

    return 0;
}

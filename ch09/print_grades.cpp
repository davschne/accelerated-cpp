#include <algorithm>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Student_info.h"

using std::max;
using std::sort;

using std::setprecision;

using std::cin;
using std::cout;
using std::endl;

using std::domain_error;
using std::string;
using std::vector;

int main() {
    vector<Student_info> students;
    
    Student_info record;
    string::size_type maxlen {0};

    // read and store the data
    while (record.read(cin)) {
        maxlen = max(maxlen, record.name().size());
        students.push_back(record);
    }

    // alphabetize the student records
    sort(students.begin(), students.end(), compare);

    // write the names and grades
    for (const auto& student : students) {
        cout << student.name()
             << string(maxlen + 1 - student.name().size(), ' ');
        
        try {
            double final_grade = student.grade();
            auto prec = cout.precision();
            cout << setprecision(3) << final_grade
                 << setprecision(prec) << endl;
        } catch (domain_error e) {
            cout << e.what() << endl;
        }
    }

    return 0;
}

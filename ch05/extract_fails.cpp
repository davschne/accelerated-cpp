// 5.5/85
// Extract records of students with failing grades from a collection.

#include <list>

#include "Student_info.h"
#include "grade.h"

using std::list;

bool fgrade(const Student_info& s) {
    return grade(s) < 60;
}

// We use the `list` container because of its superior performance when removing interior elements.
list<Student_info> extract_fails(list<Student_info>& students) {
    // list to hold records of students with failing grades
    list<Student_info> fail;
    list<Student_info>::iterator iter = students.begin();

    while (iter != students.end()) {
        if (fgrade(*iter)) {
            fail.push_back(*iter);
            iter = students.erase(iter);
        } else {
            ++iter;
        }
    }
    return fail;
}

// 6.3.1/117
// From a vector of student info, extract elements that represent failing grades.
// This version uses two passes through the iterator.

#include <algorithm>
using std::remove_copy_if;
using std::remove_if;

#include <vector>
using std::vector;

#include "grade.h"
#include "Student_info.h"

vector<Student_info> extract_fails(vector<Student_info>& students) {
    vector<Student_info> fail;
    // pass 1: Copy the failing records into a new collection.
    // `remove_copy_if` copies only those elements of a collection that DO NOT satisfy a predicate
    remove_copy_if(students.begin(), students.end(), back_inserter(fail), pgrade);
    // Erase the failing records from the input collection
    students.erase(
        // pass 2: Group passing grades at the beginning of the collection.
        // `remove_if` modifies a collection in-place by moving elements that DO NOT satisfy a predicate
        // to the beginning of the collection, returning an iterator one past the end of these grouped elements.
        // Elements after this point are essentially garbage values.
        remove_if(students.begin(), students.end(), fgrade),
        students.end()
    );
    return fail;
}

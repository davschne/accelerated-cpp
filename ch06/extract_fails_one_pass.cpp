// 6.3.2/119
// From a vector of student info, extract elements that represent failing grades.
// This version uses a single pass through an iterator as should perform better than the two-pass solution.

#include <algorithm>
using std::stable_partition;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include "grade.h"
#include "Student_info.h"

vector<Student_info> extract_fails(vector<Student_info>& students) {
    // `stable_partition` (like `partition`) mutates a collection in-place, grouping those elements that satisfy the
    // predicate together at the beginning of the collection and those elements that don't together at the end of the
    // collection. It returns an iterator to the first element of the second group.
    auto iter = stable_partition(students.begin(), students.end(), pgrade);
    vector<Student_info> fail(iter, students.end());
    students.erase(iter, students.end());
    return fail;
}

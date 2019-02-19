// 6.2/110
// Compare three different grading schemes

#include <algorithm>
using std::find;
using std::transform;

#include <stdexcept>
using std::domain_error;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::ostream;

#include <iterator>
using std::back_inserter;

#include <numeric>
using std::accumulate;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include "grade.h"
#include "median.h"
#include "Student_info.h"

// write the result of a given analysis scheme, represented as a function, for students who:
// a) completed all homework assignments
// b) didn't complete all homework assignments
void write_analysis(
    ostream& out,
    const string& name,
    double analysis(const vector<Student_info>&),
    const vector<Student_info>& did,
    const vector<Student_info>& didnt
) {
    out << name
        << ": median(did) = " << analysis(did)
        << ", median(didnt) = " << analysis(didnt)
        << endl;
}

// Did the student complete all homework assignments?
bool did_all_hw(const Student_info& s) {
    return find(s.homework.begin(), s.homework.end(), 0) == s.homework.end();
}

// analysis scheme that uses the median of the homework assignments a student completed;
// if the student completed no assignments, then the homework score will be 0
double median_analysis(const vector<Student_info>& students) {
    vector<double> grades;
    // `transform` works like the functional combinator `map`
    transform(
        students.begin(), students.end(),
        back_inserter(grades),
        // this lambda wraps the `grade` function, handling the exception if it throws
        [] (const Student_info& s) {
            try {
                return grade(s);
            } catch (domain_error) {
                return grade(s.midterm, s.final, 0);
            }
        }
    );
    return median(grades);
}

// compute the mean of a vector of double
double average(const vector<double>& v) {
    // `accumulate` works like the functional combinator `reduce`.
    // This version, which doesn't take a function argument, simply adds the elements
    // of a container to the initializer (third arg).
    return accumulate(v.begin(), v.end(), 0.0) / v.size();
}

// compute a student's grade using the average of homework assignments
double average_grade(const Student_info& s) {
    return grade(s.midterm, s.final, average(s.homework));
}

// analysis scheme that uses the mean of students' homework assignments,
// assigning a grade of 0 for incomplete assignments
double average_analysis(const vector<Student_info>& students) {
    vector<double> grades;
    transform(students.begin(), students.end(), back_inserter(grades), average_grade);
    return median(grades);
}

// median of the nonzero elements of `s.homework`, or 0 if no such elements exist
double optimistic_median(const Student_info& s) {
    vector<double> nonzero;
    remove_copy(s.homework.begin(), s.homework.end(), back_inserter(nonzero), 0);
    if (nonzero.empty())
        return grade(s.midterm, s.final, 0);
    else
        return grade(s.midterm, s.final, median(nonzero));
}

// analysis scheme that uses the median of only the assignments that the student completed;
// assumes a student's average grade for incomplete homework would have been the same as
// that for completed homework
double optimistic_median_analysis(const vector<Student_info>& students) {
    vector<double> grades;
    transform(students.begin(), students.end(), back_inserter(grades), optimistic_median);
    return median(grades);
}

int main() {
    // students who did and didn't do all their homework
    vector<Student_info> did, didnt;

    // read the student records and partition them
    Student_info student;
    while (read(cin, student)) {
        if (did_all_hw(student))
            did.push_back(student);
        else
            didnt.push_back(student);
    }

    // verify that the analyses will show us something
    if (did.empty()) {
        cout << "No student did all the homework!" << endl;
        return 1;
    } else if (didnt.empty()) {
        cout << "Every student did all the homework!" << endl;
        return 1;
    }

    // do the analyses, write to stdout
    write_analysis(cout, "median", median_analysis, did, didnt);
    write_analysis(cout, "average", average_analysis, did, didnt);
    write_analysis(cout, "median of homework turned in", optimistic_median_analysis, did, didnt);

    return 0;
}

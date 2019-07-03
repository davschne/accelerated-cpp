#include "Core.h"
#include "grade.h"

using namespace std;

// default constructor
Core::Core(): midterm {0}, final {0} { }

// build from istream
Core::Core(istream& is) { read(is); }

string Core::name() const { return n; }

istream& Core::read(istream& in) {
    read_common(in);
    read_hw(in, homework);
    return in;
}

double Core::grade() const {
    return ::grade(midterm, final, homework);
}

Core* Core::clone() const {
    return new Core(*this);
}

istream& Core::read_common(istream& in) {
    // read and store the student's name and exam grades
    in >> n >> midterm >> final;
    return in;
}

// read homework grades from an input stream into a `vector<double>`
istream& read_hw(istream& in, vector<double>& hw) {
    if (in) {
        // get rid of previous vector contents
        hw.clear();

        // read homework grades
        double x;
        while (in >> x)
            hw.push_back(x);

        // clear the stream error state so that input will work for the next student
        in.clear();
    }
    return in;
}

bool compare_grades(const Core& a, const Core& b) {
    // Because a and b are passed by reference, and `grade` is a virtual function,
    // the correct implementation will be called at runtime.
    return a.grade() < b.grade();
}

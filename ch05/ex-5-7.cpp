// 5-7. Given the implementation of `frame` in 5.8.1/93, and the following code fragment
//
//        vector<string> v;
//        frame(v);
//
//      describe what happens in this call. In particular, trace through how both the `width`
//      function and the `frame` function operate. Now, run this code. If the results differ
//      from your expectations, first understand why your expectations and the program differ,
//      and then change one to match the other.

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "width.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

vector<string> frame(const vector<string>& v) {
    vector<string> ret;

    // Unlike the original `frame` function, here we check the size of `v`.
    // If `v` is of size 0, just return a new empty vector.
    if (v.size() == 0) {
        return ret;
    }

    auto maxlen = width(v);
    // string representing horizontal border
    string border(maxlen + 4, '*');

    // write the top border
    ret.push_back(border);

    // write each interior row, bordered by an asterisk and a space
    for (string s : v) {
        string padding_right = string(maxlen - s.size(), ' ');
        ret.push_back("* " + s + padding_right + " *");
    }

    // write the bottom border
    ret.push_back(border);

    return ret;
}

// This program calls `frame` with an empty vector. It should print nothing.
int main() {
    vector<string> v;
    const vector<string> picture {frame(v)};
    for (auto line : picture) {
        cout << line << endl;
    }
}

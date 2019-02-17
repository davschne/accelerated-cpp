// 5.8.1/93
// Frame a multiline message with a border of asterisks, returning a vector representing each row.

#include <algorithm>
#include <string>
#include <vector>

#include "width.h"

using std::string;
using std::vector;

vector<string> frame(const vector<string>& v) {
    vector<string> ret;
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

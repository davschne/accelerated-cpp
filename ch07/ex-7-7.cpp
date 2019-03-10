// 7.7. Change the driver for the cross-reference program so that it writes `line` if there is only one line and `lines` otherwise.

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::istream;

#include <map>
using std::map;

#include <string>
using std::getline;
using std::string;

#include <set>
using std::set;

#include <vector>
using std::vector;

#include "split.h"

// find all the lines that refer to each word in the input

map<string, set<int> > xref(istream& in, vector<string> find_words(const string&) = split) {
    string line;
    int line_number {0};
    map<string, set<int> > ret;

    // read the next line
    while (getline(in, line)) {
        ++line_number;

        // break the input line into words
        vector<string> words {find_words(line)};

        // remember that each word occurs on the current line
        for (auto it = words.cbegin(); it != words.cend(); ++it) {
            ret[*it].insert(line_number);
        }
    }
    return ret;
}

int main() {
    // call `xref` using `split` by default
    map<string, set<int> > ret {xref(cin)};

    // write the results
    for (auto it {ret.cbegin()}; it != ret.cend(); ++it) {
        // write the word
        cout
            << "\"" << it->first << "\""
            << " occurs on "
            << (it->second.size() == 1 ? "line" : "lines")
            << ": ";

        // followed by one or more line numbers
        auto line_it = it->second.cbegin();
        // write the first line number (each entry in the `map` appears at least once)
        cout << *line_it;
        ++line_it;

        // write the rest of the line numbers, if any
        while (line_it != it->second.cend()) {
            cout << ", " << *line_it;
            ++line_it;
        }
        // write a newline to separate each word from the next
        cout << endl;
    }
    return 0;
}

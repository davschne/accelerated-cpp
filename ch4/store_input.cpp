#include <iostream>
#include <string>
#include <vector>

using std::istream;
using std::string;
using std::vector;

// read words from an input stream and store them in a vector
istream& store_input(istream& in, vector<string>& vec) {
    if (in) {
        vec.clear();

        string s;
        while (in >> s)
            vec.push_back(s);

        in.clear();
    }

    return in;
}

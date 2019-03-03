// 6.1.1/103 Split a string into words

#include <algorithm>
using std::find_if;

#include <cctype>
using std::isspace;

#include <string>
using std::string;

#include <vector>
using std::vector;

// `true` if the argument is whitespace, `false` otherwise
bool space(char c) {
    return isspace(c);
}

// `false` if the argument is whitespace, `true` otherwise
bool not_space(char c) {
    return !isspace(c);
}

vector<string> split(const string& str) {
    using iter = string::const_iterator;
    vector<string> ret;

    iter i = str.cbegin();
    while (i != str.end()) {
        // ignore leading blanks
        i = find_if(i, str.end(), not_space);

        // find end of next word
        iter j = find_if(i, str.end(), space);

        // copy the characters in [i, j)
        if (i != str.end())
            ret.push_back(string(i, j));
            
        i = j;
    }
    return ret;
}

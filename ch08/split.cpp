// 8.4/152
// rewrite `split` to take an output iterator, so that it will work with arbitrary containers

#include <algorithm>
using std::find_if;

#include <cctype>
using std::isspace;

#include <string>
using std::string;

// `true` if the argument is whitespace, `false` otherwise
bool space(char c) {
    return isspace(c);
}

// `false` if the argument is whitespace, `true` otherwise
bool not_space(char c) {
    return !isspace(c);
}

template <class Out>
void split(const string& str, Out os) {
    typedef string::const_iterator iter;

    iter i = str.begin();
    while (i != str.end()) {
        // ignore leading blanks
        i = find_if(i, str.end(), not_space);

        // find end of next word
        iter j = find_if(i, str.end(), space);

        // copy the characters in [i, j)
        if (i != str.end())
            *os++ = string(i, j);
        
        i = j;
    }
}

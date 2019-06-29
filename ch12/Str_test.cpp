#include <cassert>
#include <sstream>
#include <vector>

#include "Str.h"

using namespace std;

int main() {
    // construct from `n` copies of `c`
    Str aaa {3, 'a'};
    // copy the contents of a string into a char array
    // we leave an extra character for the null terminator
    char c_string[4];
    aaa.copy(c_string, 3);
    assert(aaa == Str{c_string});
    assert(aaa.size() == 3);

    // default constructor
    Str from_stream;
    stringstream ss, ss_cp;
    // build from character stream
    ss >> from_stream;
    ss_cp << from_stream;
    assert(ss.str() == ss_cp.str());

    // construct from char*
    Str good {"good"};
    // subscript operator
    assert(good[3] == 'd');
    // concatenate strings
    Str goodbye {good + "bye"};
    // construct a vector using the string's iterators
    vector<char> vec {goodbye.begin(), goodbye.end()};
    // construct a string from a vector's iterators
    Str goodbye_again {vec.begin(), vec.end()};
    assert(goodbye == goodbye_again);

    // boolean coercion
    assert(Str{"h"});
    assert(!Str{});

    // comparison operators
    Str a {"a"};
    Str ab {"ab"};
    assert(a < ab);
    assert(a <= ab);
    assert(ab > a);
    assert(ab >= a);
    assert(a == a);
    assert(a != ab);
    assert(a <= a);
    assert(a >= a);

    return 0;
}

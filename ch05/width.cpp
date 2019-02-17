// 5.8.1/92
// Compute the width of a multi-line message (i.e. the max string length)

#include <algorithm>
#include <string>
#include <vector>

#include "width.h"

using std::max;
using std::string;
using std::vector;

string::size_type width(const vector<string>& v) {
    string::size_type maxlen = 0;
    for (string s : v)
        maxlen = max(maxlen, s.size());
    
    return maxlen;
}

// 5.8.2/94
// Concatenate two multi-line messages vertically

#include <string>
#include <vector>

using std::string;
using std::vector;

vector<string> vcat(const vector<string>& top, const vector<string>& bottom) {
    // copy the `top` picture
    vector<string> ret = top;

    // copy entire `bottom` picture
    ret.insert(ret.end(), bottom.begin(), bottom.end());
    
    return ret;
}

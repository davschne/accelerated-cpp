// 6.1/101
// Find any URLs in an input string

#include <algorithm>
using std::find;
using std::find_if;
using std::search;

#include <cctype>
using std::isalnum;
using std::isalpha;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include "find_urls.h"

typedef string::const_iterator iter;

// Is the given character a valid URL character?
bool not_url_char(char c) {
    // characters, in addition to alphanumerics, that can appear in a URL
    // We use the `static` storage class to avoid initializing the value each time the function is called.
    static const string url_ch {"~;/?:@=&$-_.+!*'(),"};

    // see whether `c` can appear in a URL
    return !(
        isalnum(c)
        // `find` looks for a value (3rd arg) in a container.
        // If found, it will return an iterator to that element; otherwise it returns its 2nd arg.
        || find(url_ch.begin(), url_ch.end(), c) != url_ch.end()
    );
}

// Find the end of a URL, returning an iterator one past the end.
iter url_end(iter b, iter e) {
    // `find_if` looks for a value for which a predicate (3rd arg) returns true.
    return find_if(b, e, not_url_char);
}

// Find the beginning of a URL, returning an iterator to its first character.
iter url_beg(iter b, iter e) {
    // Note the `static` storage class.
    static const string sep {"://"};

    iter i {b};
    // Search for the separator in the range [i, e).
    // `search` uses iterators to look for a subsequence, like this:
    //   `search(haystack_start, haystack_end, needle_start, needle_end)`
    // If the subsequence isn't found, it returns its 2nd arg.
    while ((i = search(i, e, sep.begin(), sep.end())) != e) {
        // make sure the separator isn't at the beginning or end of the line
        if (i != b && i + sep.size() != e) {
            // `beg` marks the beginning of the protocol name
            iter beg {i};
            // backtrack to the get the protocol name
            // `beg[-1]` is equivalent to `*(beg - 1)`
            while (beg != b && isalpha(beg[-1]))
                --beg;

            // is there at least one appropriate character before and after the separator?
            if (beg != i && !not_url_char(i[sep.size()]))
                return beg;
        }
        // the separator we found wasn't part of a URL; advance `i` past this separator
        i += sep.size();
    }
    return e;
}

vector<string> find_urls(const string& s) {
    vector<string> ret;
    iter b {s.begin()},
         e {s.end()};
    
    // look through the entire input
    while (b != e) {
        // look for one or more letters followed by ://
        b = url_beg(b, e);

        // if we found a URL
        if (b != e) {
            // get the rest of the URL
            iter after {url_end(b, e)};

            // remember the URL
            ret.push_back(string(b, after));

            // advance `b` and check for more URLs
            b = after;
        }
    }
    return ret;
}

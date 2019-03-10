#include <algorithm>
using std::swap;

// 8.2.2/145
// input iterator: sequential read-only access
template <class In, class X>
In find(In begin, In end, const X& x) {
    while (begin != end && *begin != x)
        ++begin
    return begin;
}

// 8.2.3/146
// output iterator: sequential write-only access
template <class In, class Out>
Out copy(In begin, In end, Out dest) {
    while (begin != end)
        *dest++ = *begin++;
    return dest;
}

// 8.2.4/147
// forward iterator: sequential read-write access
template <class For, class X>
void replace(For beg, For end, const X& x, const X& y) {
    while (beg != end) {
        if (*beg == x)
            *beg = y;
        ++beg;
    }
}

// 8.2.5/148
// bidirectional iterator: reversible access
template <class Bi>
void reverse(Bi begin, Bi end) {
    while (begin != end) {
        --end;
        if (begin != end)
            swap(*begin++, *end);
    }
}

// 8.2.6/148
// random-access iterator
template <class Ran, class X>
bool binary_search(Ran begin, Ran end, const X& x) {
    while (begin < end) {
        // find the midpoint of the range
        Ran mid = begin + (end - begin) / 2;
        // see which part of the range contains `x`; keep looking only in that part
        if (x < *mid)
            end = mid;
        else if (*mid < x)
            begin = mid + 1;
        // if we got here, then *mid == x, so we're done
        else
            return true;
    }
    return false;
}

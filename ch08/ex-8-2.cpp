// 8-2. Implement the following library algorithms, which we used in Chapter 6 and described in 6.5/121. Specify what kinds of iterators they require. Try to minimize the number of distinct iterator operations that each function requires. After you have finished your implementation, see B.3/322 to see how well you did.

#include <algorithm>
using std::swap;

namespace Alg {
    // equal(b, e, b2)
    template <class In>
    bool equal(In begin, In end, In begin2) {
        while (begin != end) {
            if (*begin++ != *begin2++) {
                return false;
            }
        }
        return true;
    }

    // find(b, e, t)
    template <class In, class T>
    In find(In begin, In end, const T& val) {
        while (begin != end && *begin != val) {
            ++begin;
        }
        return begin;
    }

    // copy(b, e, d)
    template <class In, class Out>
    void copy(In begin, In end, Out dest) {
        while (begin != end) {
            *dest++ = *begin++;
        }
    }

    // remove_copy_if(b, e, d, p)
    template <class In, class Out, class Pred>
    void remove_copy_if(In begin, In end, Out dest, Pred pred) {
        while (begin != end) {
            if (!pred(*begin)) {
                *dest++ = *begin++;
            } else {
                ++begin;
            }
        }
    }

    // transform(b, e, d, f)
    template <class In, class Out, class Fn>
    void transform(In begin, In end, Out dest, Fn fn) {
        while (begin != end) {
            *dest++ = fn(*begin++);
        }
    }

    // accumulate(b, e, t)
    template <class In, class T>
    T accumulate(In begin, In end, T val) {
        while (begin != end) {
            val += *begin;
        }
        return val;
    }

    // search(b, e, b2, e2)
    template <class In>
    In search(In haystack_begin, In haystack_end, In needle_begin, In needle_end) {
        while (haystack_begin != haystack_end) {
            // Make copies of the iterators to check for matches.
            In haystack_it {haystack_begin};
            In needle_it {needle_begin};
            while (
                haystack_it != haystack_end
                && needle_it != needle_end
                && *haystack_it == *needle_it
            ) {
                ++haystack_it;
                ++needle_it;
            }
            // If we traversed the entire needle, then we've found it!
            if (needle_it == needle_end) {
                return needle_begin;
            }
            ++haystack_begin;
        }
        // not found
        return haystack_end;
    }

    // find_if(b, e, p)
    template <class In, class Pred>
    In find_if(In begin, In end, Pred pred) {
        while (begin != end && !pred(*begin)) {
            ++begin;
        }
        return begin;
    }

    // remove_copy(b, e, d, t)
    template <class In, class Out, class T>
    void remove_copy(In begin, In end, Out dest, const T& val) {
        while (begin != end) {
            if (*begin != val) {
                *dest++ = *begin++;
            } else {
                ++begin;
            }
        }
    }

    // remove(b, e, t)
    template <class Forward, class T>
    Forward remove(Forward begin, Forward end, const T& val) {
        // `begin` will be our "write" pointer
        // invariant: no element before `begin` matches `val`
        // `search_it` will run ahead, looking for elements that don't match val
        Forward search_it {begin};
        while (search_it != end) {
            if (*search_it != val) {
                *begin++ = *search_it++;
            } else {
                ++search_it;
            }
        }

        return begin;
    }

    // partition(b, e, p)
    template <class Bi, class Pred>
    Bi partition(Bi begin, Bi end, Pred pred) {
        // idea: proceed forward from beginning and backward from end, swapping elements as needed
        --end;
        // loop invariants:
        // - all elements before `begin` return `true` for the predicate
        // - all elements after `end` return `false` for the predicate
        // - `*begin` and `*end` (and any elements in between) have yet to be examined
        while (begin != end) {
            if (pred(*begin)) {
                // If `*begin` returns true for the predicate, just advance the pointer.
                ++begin;
            } else {
                // Otherwise, we need to look at `end` to find an element to swap for `*begin`.
                // We march it backward until we find such an element or the pointers converge.
                while (begin != end && !pred(*end)) {
                    --end;
                }
                // If we found an element to swap, we perform the swap and advance `begin`.
                // We don't also decrement `end`, because we don't want to risk having the pointers cross.
                if (begin != end) {
                    swap(*begin++, *end);
                }
            }
        }
        // At this point, `begin == end`, and we've examined all the other elements.
        // We only need to know whether `*begin` returns true for the predicate.
        return pred(*begin) ? ++begin : begin;
    }
}

#include <vector>
using std::vector;

template <class Input, class Expected>
struct TestCase {
    Input input;
    Expected expected;
};

void test_equal() {
    vector<int> ints_1 {1, 2, 3, 4};
    vector<int> ints_2 {1, 2};
    assert(Alg::equal(ints_1.begin(), ints_1.end(), ints_1.begin()));
    assert(!Alg::equal(ints_1.begin(), ints_1.end(), ints_2.begin()));
}

void test_find() {
    vector<int> ints {0, 1, 2};
    assert(*Alg::find(ints.begin(), ints.end(), 2) == 2);
    assert(Alg::find(ints.begin(), ints.end(), 5) == ints.end());
}

void test_copy() {
    vector<int> input {1, 2, 3};
    vector<int> output(input.size());
    Alg::copy(input.cbegin(), input.cend(), output.begin());
    for (vector<int>::size_type i {0}; i != input.size(); ++i) {
        assert(input[i] == output[i]);
    }
}

void test_remove_copy_if() {
    vector<int> input {1, 2, 3};
    vector<int> expected {2, 3};
    vector<int> output(expected.size());
    auto isOne {[](const int& val) { return val == 1; }};
    Alg::remove_copy_if(input.cbegin(), input.cend(), output.begin(), isOne);
    for (vector<int>::size_type i {0}; i != input.size(); ++i) {
        assert(output[i] == expected[i]);
    }
}

void test_transform() {}

void test_accumulate() {}

void test_search() {}
void test_find_if() {}
void test_remove_copy() {}
void test_remove() {}
void test_partition() {}

int main() {
    test_equal();
    test_find();
    test_copy();
    test_remove_copy_if();
    test_transform();
    test_accumulate();
    test_search();
    test_find_if();
    test_remove_copy();
    test_remove();
    test_partition();
    return 0;
}

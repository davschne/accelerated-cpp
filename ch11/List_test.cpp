#include <cassert>
#include <vector>

#include "List.h"

using namespace std;

int main() {
    // make a single-element List
    List<int> list1 {1};
    assert(list1.size() == 1);

    // make a 2-element List from an iterator
    vector<int> v {1, 2};
    List<int> list2 {v.begin(), v.end()};
    assert(list2.size() == 2);

    // copy a List wholesale
    List<int> list2_copy {list2};
    // copy a List using its iterators
    List<int> list1_copy {list1.begin(), list1.end()};

    // compare Lists
    assert(list1 == list1_copy);
    assert(list2 == list2_copy);
    assert(list1 != list2);

    // add an element to the end of a List
    List<int> list3 {list2};
    list3.push_back(3);
    assert(list3.size() == 3);

    return 0;
}

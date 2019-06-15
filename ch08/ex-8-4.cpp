// 8-4. Implement the `swap` function that we used in 8.2.5/148. Why did we call `swap` rather than exchange the values of `*beg` and `*end` directly?

template <class T>
void swap(T& a, T& b) {
    const T temp {a};
    a = b;
    b = temp;
}

#include "assertion.h"

int main() {
    int a {1};
    int b {2};
    swap(a, b);
    assert_eq(a, 2);
    assert_eq(b, 1); 
}

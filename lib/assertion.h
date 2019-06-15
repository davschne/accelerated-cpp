#ifndef ASSERTION_h
#define ASSERTION_h

#include <sstream>

void assert_not(bool assertion) {
    if (assertion) {
        throw "Error: expected false, found true";
    }
}

template <class Value>
void assert_eq(Value a, Value b) {
    if (a != b) {
        // std::ostringstream oss;
        // oss << "Error: " << a << " != " << b;
        throw "expected ==";
    }
}

// template <class Value>
// void assert_eq(Value* a, Value* b) {
//     if (a != b) {
//         std::ostringstream oss;
//         oss << "Error: " << a << "* != " << b << "*";
//         throw oss.str();
//     }
// }

template <class Value>
void assert_ne(Value a, Value b) {
    // std::ostringstream oss;
    // oss << "Error: " << a << " == " << b;
    if (a == b) {
        throw "expected !=";
    }
}

// template <class Value>
// void assert_ne(Value* a, Value* b) {
//     std::ostringstream oss;
//     oss << "Error: " << a << "* == " << b << "*";
//     if (a == b) {
//         throw oss.str();
//     }
// }

#endif

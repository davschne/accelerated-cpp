// Exercise 4-2. Write a program to calculate the squares of `int` values up to 100. The program should write two columns: The first lists the value; the second contains the square of that value. Use `setw` to manage the output so that the values line up in columns.

#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;
using std::setw;

const int END = 100;

int main() {
    for (int val = 0; val <= END; ++val) {
        const int square = val * val;
        cout << setw(3) << val << setw(6) << square << endl;
    }
    return 0;
}

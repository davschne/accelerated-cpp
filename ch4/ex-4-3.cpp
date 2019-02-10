// Exercise 4-3. What happens if we rewrite the previous program to allow values up to but not including 1000 but neglect to change the arguments to `setw`? Rewrite the program to be more robust in the face of changes that allow i to grow without adjusting the `setw` arguments.

#include <iostream>
#include <iomanip>
#include <cmath>

using std::cout;
using std::endl;
using std::setw;
using std::log10;
using std::floor;

const int start = 500;
const int end = 1000;
const int pad = 1;

// Calculate the number of digits in the decimal representation of the given integer.
int num_digits(const int val) {
    return floor(log10(val)) + 1;
}

int main() {
    // Calculate the number of characters in the largest numbers we'll need to represent in each column.
    int val_col_width = num_digits(end);
    int squares_col_width = num_digits(end * end);

    for (int val = start; val <= end; ++val) {
        const int square = val * val;
        cout << setw(val_col_width) << val
             << setw(pad + squares_col_width) << square
             << endl;
    }

    return 0;
}

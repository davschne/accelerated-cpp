// Exercise 2-5. Write a set of "*" characters so that they form a square, a rectangle, and a triangle.

#include <iostream>

using std::cout;
using std::endl;

/*
Desired output:
*****
*   *
*   *
*   *
*****

***********
*         *
***********

*
**
* *
*  *
*   *
******
*/

void print_square(const int side) {
    for (int row = 0; row != side; ++row) {
        for (int col = 0; col != side; ++col) {
            // are we on the border?
            if (row == 0 || row == side - 1 ||
                col == 0 || col == side - 1)
                cout << '*';
            else
                cout << ' ';
        }
        cout << endl;
    }
};

void print_rectangle(const int width, const int height) {
    for (int row = 0; row != height; ++row) {
        for (int col = 0; col != width; ++col) {
            // are we on the border?
            if (row == 0 || row == height - 1 ||
                col == 0 || col == width - 1)
                cout << '*';
            else
                cout << ' ';
        }
        cout << endl;
    }
}

void print_triangle(const int base) {
    for (int row = 0; row != base; ++row ) {
        const int col_width = row + 1;
        for (int col = 0; col != col_width; ++col) {
            if (row == base - 1 // base row: all *'s
                || col == 0
                || col == col_width - 1
            )
                cout << '*';
            else
                cout << ' ';
        }
        cout << endl;
    }
}

int main() {
    const int square_side = 5;
    const int rect_width  = 11;
    const int rect_height = 3;
    const int tri_base    = 6;

    print_square(square_side);
    cout << endl;
    print_rectangle(rect_width, rect_height);
    cout << endl;
    print_triangle(tri_base);

    return 0;
}

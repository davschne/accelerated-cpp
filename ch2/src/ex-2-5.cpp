// Exercise 2-5. Write a set of "*" characters so that they form a square, a rectangle, and a triangle.

#include <cmath>
#include <iostream>

using std::cout;
using std::endl;

using std::ceil;

/*
Desired output:
********
*      *
*      *
********

******
*    *
*    *
******

   *
  * *
 *   *
*******
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
    // height is half the base, rounding up
    const int height = ceil(float(base) / 2);
    for (int row = 0; row != height; ++row ) {
        const int col_width = base - (height - row);
        for (int col = 0; col != col_width + 1; ++col) {
            if (row == height - 1 // base row: all *'s
                || col == (height - 1) - row
                || col == (height - 1) + row
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
    const int tri_base    = 10;

    print_square(square_side);
    cout << endl;
    print_rectangle(rect_width, rect_height);
    cout << endl;
    print_triangle(tri_base);

    return 0;
}

// Exercise 2-9. Write a program that asks the user to enter two numbers and tells the user which number is larger than the other.

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;

int get_input_as_int() {
    int value;
    cin >> value;
    return value;
}

int main() {
    cout << "Enter a number: ";
    int num1;
    cin >> num1;

    cout << "Enter another number: ";
    int num2;
    cin >> num2;

    if (num1 == num2) {
        cout << num1 << " is equal to " << num2;
    } else if (num1 > num2) {
        cout << num1 << " is greater than " << num2;
    } else {
        cout << num2 << " is greater than " << num1;
    }
    cout << endl;

    return 0;
}

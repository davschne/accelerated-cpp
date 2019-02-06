// Exercise 2-9. Write a program that asks the user to enter two numbers and tells the user which number is larger than the other.

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::stoi;

int get_input_as_int() {
    string raw_input;
    cin >> raw_input;
    return stoi(raw_input);
}

int main() {
    cout << "Enter a number: ";
    const int num1 = get_input_as_int();
    // cout << endl;
    cout << "Enter another number: ";
    // cout << endl;
    const int num2 = get_input_as_int();

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

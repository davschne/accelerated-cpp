// 3-2. Write a program to compute and print the quartiles (that is, the quarter of the numbers with the largest values, the next highest quarter, and so on) of a set of integers.

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

string get_ordinal(int cardinal) {
    switch (cardinal) {
        case 1: return "First";
        case 2: return "Second";
        case 3: return "Third";
        case 4: return "Fourth";
        // Better to throw an error here, I'd think; but haven't learned that yet.
        default: return "";
    }
}

void print_quartile(const vector<int>& values, int quartile) {
    cout << get_ordinal(quartile) << " quartile: ";
    int start = (quartile - 1) * values.size() / 4;
    int end = quartile * values.size() / 4;
    for (int i = start; i < end; ++i) {
        cout << values[i] << ' ';
    }
    cout << endl;
}

int main() {
    cout << "Enter four or more integers, separated by spaces, followed by end-of-file:" << endl;

    vector<int> values;
    int value;
    while (cin >> value) {
        values.push_back(value);
    }

    if (values.size() < 4) {
        cout << "Must enter at least four integers." << endl;
        return 1;
    }

    std::sort(values.begin(), values.end());

    for (int quartile = 1; quartile < 5; ++quartile) {
        print_quartile(values, quartile);
    }

    return 0;
}

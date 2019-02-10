// Exercise 4-5. Write a function that reads words from an input stream and stores them in a `vector`. Use that function both to write programs that count the number of words in the input, and to count how many times each word occurred.

// a. Count the number of words in an input.

#include <iostream>
#include <string>
#include <vector>

#include "store_input.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

int main() {
    cout << "Enter words, followed by end-of-file:" << endl;

    vector<string> words;
    if (store_input(cin, words)) {
        cout << "words received: " << words.size() << endl;
        return 0;
    } else {
        cout << "Input error" << endl;
        return 1;
    }
}

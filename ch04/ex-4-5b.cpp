// Exercise 4-5. Write a function that reads words from an input stream and stores them in a `vector`. Use that function both to write programs that count the number of words in the input, and to count how many times each word occurred.

// b. Count the occurrences of each word.

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "store_input.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::setw;
using std::sort;

int max_word_length(const vector<string>& words) {
    int max = 0;
    for (string word : words) {
        if (word.size() > max) {
            max = word.size();
        }
    }
    return max;
}

int main() {
    cout << "Enter words, followed by end-of-file:" << endl;

    vector<string> words;
    if (!store_input(cin, words)) {
        cout << "Input error" << endl;
        return 1;
    }

    // Sort the list of words so duplicates are adjacent.
    sort(words.begin(), words.end());

    // Get the length of the longest word.
    const int max_length = max_word_length(words);

    // Print the number of occurrences of each word.
    cout << "Occurrences of each word:" << endl;

    // invariant: word `prev` has occurred `count` times so far
    string prev = "";
    int count = 0;
    for (string word : words) {
        if (word == prev) {
            ++count;
        } else {
            if (prev.size()) {
                cout << setw(max_length) << prev << " : " << count << endl;
            }
            prev = word;
            count = 1;
        }
    }
    // We have to do this one more time after the end of the loop.
    if (prev.size()) {
        cout << setw(max_length) << prev << " : " << count << endl;
    }

    return 0;
}

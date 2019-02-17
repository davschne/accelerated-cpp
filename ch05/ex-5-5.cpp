// 5.5. Write a function named `center(const vector<string>&)` that returns a picture in which all the lines of the original picture are padded out to their full width, and the padding is as evenly divided as possible between the left and right sides of the picture. What are the properties of pictures for which such a function is useful? How can you tell whether a given picture has those properties?

#include <string>
#include <vector>

#include "width.h"

using std::string;
using std::vector;

vector<string> center(const vector<string>& lines) {
    const auto max_width = width(lines);
    const bool even = max_width % 2 == 0;

    vector<string> output;

    for (string line : lines) {
        const auto row_width = line.size();
        const auto extra_spaces = max_width - row_width;
        if (extra_spaces == 0) {
            output.push_back(line);
        } else {
            const auto left_pad = extra_spaces / 2;
            const auto right_pad = extra_spaces - left_pad;
            const string padded {string(left_pad, ' ') + line + string(right_pad, ' ')};
            output.push_back(padded);
        }
    }

    return output;
}

// Sample program using the function:

#include <iostream>

using std::getline;
using std::cin;
using std::cout;

int main() {
    vector<string> lines;
    string s;
    while (getline(cin, s)) {
        lines.push_back(s);
    }

    const auto centered = center(lines);
    
    for (string line : centered) {
        cout << line << '\n';
    }

    return 0;
}

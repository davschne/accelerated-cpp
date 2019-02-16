// Exercise 2-3. Rewrite the framing program to ask the user to supply the amount of spacing to leave between the frame and the greeting.

#include <iostream>
#include <string>

// say what standard-library names we use
using std::cin;
using std::endl;
using std::cout;
using std::string;
using std::stoi;

void print_message_with_frame(string message, const int pad) {
    // the number of rows and columns to write
    const int rows = pad * 2 + 3;
    const string::size_type cols = message.size() + pad * 2 + 2;

    // write `rows` rows of output
    // invariant: we have written `r` rows so far
    for (int r = 0; r != rows; ++r) {
        string::size_type c = 0;

        // invariant: we have written `c` characters so far in the current row
        while (c != cols) {
            // is it time to write the message?
            if (r == pad + 1 && c == pad + 1) {
                cout << message;
                c += message.size();
            } else {
                // are we on the border?
                if (r == 0 || r == rows - 1 ||
                    c == 0 || c == cols - 1)
                    cout << "*";
                else
                    cout << " ";
                ++c;
            }
        }
        cout << endl;
    }
}

int main() {
    // ask for the person's name
    cout << "Please enter your first name: ";

    // read the name
    string name;
    cin >> name;

    // build the message that we intend to write
    const string greeting = "Hello, " + name + "!";

    // ask for the padding size
    // cout << endl;
    cout << "What size padding shall we use for the frame? ";

    // read the value
    string pad_input;
    cin >> pad_input;

    // parse as int
    const int pad = stoi(pad_input);

    // write a blank line to separate the output from the input
    cout << endl;

    print_message_with_frame(greeting, pad);
    
    return 0;
}

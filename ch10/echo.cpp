// 10.4/179 Echo argument(s) on stdout.

#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    // If there are command-line arguments, write them.
    if (argc > 1) {
        cout << argv[1]; // Write the first argument.

        // Write each remaining argument with a space before it.
        for (int i = 2; i != argc; ++i) {
            cout << " " << argv[i]; // argv[i] is a char*
        }
        cout << endl;

        return 0;
    }
}

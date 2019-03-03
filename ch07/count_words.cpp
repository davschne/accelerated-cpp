// 7.2/124 Count each unique word provided to stdin

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <map>
using std::map;

#include <string>
using std::string;

int main() {
    string s;
    // store each word and an associated counter
    map<string, int> counters;

    // read the input, keeping track of each word and how often we see it
    while (cin >> s)
        ++counters[s];
        
    // write the words and associated counts
    for (auto it = counters.cbegin(); it != counters.cend(); ++it) {
        cout << it->first << "\t" << it->second << endl;
    }
    return 0;
}

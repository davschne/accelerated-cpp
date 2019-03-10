// 7-1. Extend the program `count_words` to produce its output sorted by occurrence count. That is, the output should group all the words that occur once, followed by those that occur twice, and so on.

#include <algorithm>
using std::sort;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include <map>
using std::map;

#include <string>
using std::string;

#include <utility>
using std::pair;

#include <vector>
using std::vector;

int main() {
    string s;
    // store each word and an associated counter
    map<string, int> counters;

    // read the input, keeping track of each word and how often we see it
    while (cin >> s)
        ++counters[s];

    // type representing an element (key, val) of the map `counters`
    typedef pair<string, int> element;

    // copy the elements of the map to an array and sort it by occurrence count
    vector<element> vec(counters.cbegin(), counters.cend());
    sort(vec.begin(), vec.end(), [](element a, element b) {
        return a.second < b.second;
    });
        
    // write the words and associated counts
    for (auto it = vec.cbegin(); it != vec.cend(); ++it) {
        cout << it->first << "\t" << it->second << endl;
    }
    return 0;
}

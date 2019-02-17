// 5-9. Write a program to write the words in the input that do not contain any uppercase letters followed by the words that contain one or more uppercase letters.

#include <cctype>
#include <iostream>
#include <string>
#include <list>

using std::cin;
using std::cout;
using std::endl;
using std::isupper;
using std::string;
using std::list;

typedef list<string> collection;

bool all_lowercase(const string& s) {
    for (auto c : s) {
        if (isupper(c)) {
            return false;
        }
    }
    return true;
}

collection extract_lowercase(collection& words) {
    collection lowercase;
    auto iter = words.begin();
    while (iter != words.end()) {
        auto word = *iter;
        if (all_lowercase(word)) {
            lowercase.push_back(word);
            iter = words.erase(iter);
        } else {
            ++iter;
        }
    }
    return lowercase;
}

int main() {
    collection words;
    string s;
    while (cin >> s) {
        words.push_back(s);
    }

    collection all_lowercase = extract_lowercase(words);

    for (string word : all_lowercase)
        cout << word << ' ';
    for (string word : words)
        cout << word << ' ';
    
    cout << endl;
    return 0;
}

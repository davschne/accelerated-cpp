// 6-2. Write a program to test the `find_urls` function.

#include <iostream>
using std::cout;
using std::endl;

#include <numeric>
using std::accumulate;

#include <string>
using std::string;

#include <vector>
using std::vector;
using vec = std::vector<string>;

#include <unordered_set>
using set = std::unordered_set<string>;

#include "find_urls.h"

struct TestCase {
    string input;
    set expected;
};

int main() {
    vector<TestCase> cases {
        TestCase {
            "Visit us on the web at http://malware.com/hackme and subscribe!",
            set {"http://malware.com/hackme"}
        },
        TestCase {
            "Thanks for visiting https://spyware.org . Download your files here: ftp://spyware.org/infectme",
            set {"https://spyware.org", "ftp://spyware.org/infectme"}
        },
        TestCase {
            "Edge cases like a://b are fun. Not every ://is a url://",
            set {"a://b"}
        }
    };

    for (const TestCase& test_case : cases) {
        vector<string> result {find_urls(test_case.input)};
        set result_set(result.begin(), result.end());
        const set& expected = test_case.expected;

        if (result_set != test_case.expected) {
            cout << "Test case failed." << endl;
            cout << "result: " << accumulate(result.cbegin(), result.cend(), string {}) << endl;
            cout << "expected: " << accumulate(expected.cbegin(), expected.cend(), string {}) << endl;
            return 1;
        }
    }

    cout << "All tests passed!" << endl;
    return 0;
}

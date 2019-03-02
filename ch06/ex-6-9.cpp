// 6-9. Use a library algorithm to concatenate all the elements of a `vector<string>`.

#include <numeric>
using std::accumulate;

#include <string>
using std::string;

#include <vector>
using std::vector;

string concat(const vector<string>& vec) {
    return accumulate(vec.begin(), vec.end(), string());
}

#include <iostream>

int main() {
    vector<string> vec { "hello,", " ", "goodbye!"};
    std::cout << concat(vec) << std::endl;

    return 0;
}

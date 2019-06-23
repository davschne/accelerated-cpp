#include <iostream>

#include "String_list.h"

using namespace std;

int main(int argc, char** argv) {
    String_list ls(argv, argc);
    for (auto s : ls) {
        cout << s << endl;
    }
}

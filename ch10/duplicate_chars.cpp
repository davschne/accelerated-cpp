// 10.6.2/185

#include <algorithm>
#include <cstring>

using namespace std;

char* duplicate_chars(const char* p) {
    // allocate enough space; remember to add one for the null terminator
    size_t length = strlen(p) + 1;
    char* result = new char[length];

    // copy into our newly allocated space and return pointer to first element
    copy(p, p + length, result);
    return result;
}

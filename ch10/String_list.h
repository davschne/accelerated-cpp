// Ex. 10-4: Write a class that implements a list that holds strings.
// Ex. 10-5: Write a bidirectional iterator for your `String_list` class.

#ifndef STRING_LIST_h
#define STRING_LIST_h

#include <list>
#include <string>

class String_list {
public:
    using const_iterator = std::list<std::string>::const_iterator;
    using size_type = std::list<std::string>::size_type;

    String_list(char** ss, size_t size) : strings(ss, ss + (size)) {}
    const_iterator begin() const { return strings.begin(); }
    const_iterator end() const { return strings.end(); }
    size_type size() const { return strings.size(); }

private:
    std::list<std::string> strings;
};

#endif

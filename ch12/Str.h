#ifndef Str_h
#define Str_h

#include <algorithm>
#include <cstring>
#include <iostream>
#include <exception>

#include "Vec.h"

class Str {
    // FRIENDS
    
    // grant this overload of `operator>>` access to `Str`'s private members
    friend std::istream& operator>>(std::istream&, Str&);

public:
    // TYPE ALIASES
    using size_type = Vec<char>::size_type;
    using iterator = Vec<char>::iterator;
    using const_iterator = Vec<char>::const_iterator;
    
    // CONSTRUCTORS

    // default constructor; not synthesized, because we're declaring other constructors
    Str() { }
    // create a `Str` containing `n` copies of `c`
    Str(size_type n, char c) : data {n, c} { }
    // create a `Str` from a null-terminated array of `char`
    Str(const char* cp) {
        std::copy(cp, cp + std::strlen(cp), std::back_inserter(data));
    }
    // create a `Str` from the range denoted by iterators `b` and `e`
    template<class In>
    Str(In b, In e) {
        std::copy(b, e, std::back_inserter(data));
    }

    // CONVERSION

    // for use in boolean tests while preventing conversion to arithmetic type
    operator void*() const {
        return (void*) size();
    }

    // OPERATORS
    char& operator[](size_type i) { return data[i]; }
    const char& operator[](size_type i) const { return data[i]; }
    Str& operator+=(const Str& s) {
        std::copy(s.data.begin(), s.data.end(), std::back_inserter(data));
        return *this;
    }
    bool operator==(const Str& s) const {
        if (size() != s.size()) return false;
        for (size_type i = 0; i != size(); ++i) {
            if ((*this)[i] != s[i]) return false;
        }
        return true;
    }
    bool operator!=(const Str& s) const {
        return !(*this == s);
    }
    bool operator<(const Str& s) const {
        const size_type min_size = std::min(size(), s.size());
        // traverse the shorter string, comparing character-wise
        for (size_type i = 0; i != min_size; ++i) {
            char this_c = (*this)[i];
            char that_c = s[i];
            if (this_c == that_c) continue;
            return this_c < that_c;
        }
        // If we reach this point, we've exhaused the shorter string
        // and all characters are the same. The shorter subsequence is "less".
        return size() < s.size();
    }
    bool operator>(const Str& s) const {
        const size_type min_size = std::min(size(), s.size());
        // traverse the shorter string, comparing character-wise
        for (size_type i = 0; i != min_size; ++i) {
            char this_c = (*this)[i];
            char that_c = s[i];
            if (this_c == that_c) continue;
            return this_c > that_c;
        }
        // If we reach this point, we've exhaused the shorter string
        // and all characters are the same. The shorter subsequence is "less".
        return size() > s.size();
    }
    bool operator<=(const Str& s) const {
        return !(*this > s);
    }
    bool operator>=(const Str& s) const {
        return !(*this < s);
    }

    // OTHER FUNCTIONS
    size_type size() const { return data.size(); }

    iterator begin() { return data.begin(); }
    const_iterator begin() const { return data.begin(); }
    iterator end() { return data.end(); }
    const_iterator end() const { return data.end(); }

    size_type copy(char* dest, size_type count, size_type pos = 0) const {
        if (pos > size()) {
            throw std::out_of_range("copy starting position out of range");
        }
        // we can't copy characters from past the end of the string
        const size_type actual_count = std::min(size(), count);
        std::copy(data.begin() + pos, data.begin() + actual_count, dest);
        return actual_count;
    }

private:
    Vec<char> data;
};


// OPERATORS (that need to be defined outside the class body)
std::istream& operator>>(std::istream& is, Str& s) {
    // obliterate existing value(s)
    s.data.clear();

    // read and discard leading whitespace
    char c;
    while (is.get(c) && isspace(c))
        ;

    // if still something to read, do so until next whitespace character
    if (is) {
        do s.data.push_back(c);
        while (is.get(c) && !isspace(c));
        
        // if we read whitespace, then put it back on the stream
        if (is)
            is.unget();
    }

    return is;
}

std::ostream& operator<<(std::ostream& os, const Str& s) {
    for (auto c : s) {
        os << c;
    }
    return os;
}

Str operator+(const Str& s, const Str& t) {
    Str r {s};
    r += t;
    return r;
}

#endif

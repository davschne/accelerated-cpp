#ifndef STR_H
#define STR_H

//14.4/264-265, 14.4.1/267

// implementation of string that shares the underlying data when possible

#include <cstring>
#include <iostream>
#include "Ptr.h"
#include "Vec.h"

class Str {
    friend std::istream& operator>>(std::istream&, Str&);
public:
    using size_type = Vec<char>::size_type;

    Str& operator+=(const Str& s) {
        // since we're modifying the underlying data, we have to make a copy
        data.make_unique();
        std::copy(s.data->begin(), s.data->end(), std::back_inserter(*data));
        return *this;
    }

    Str(): data {new Vec<char>} { }
    Str(const char* cp): data {new Vec<char>} {
        std::copy(cp, cp + std::strlen(cp), std::back_inserter(*data));
    }

    Str(size_type n, char c): data {new Vec<char>(n, c)} { }

    template<class In>
    Str(In i, In j): data {new Vec<char>} {
        std::copy(i, j, std::back_inserter(*data));
    }

    // Since a consumer may modify `data` through the (non-const) reference, we need to copy it.
    char& operator[](size_type i) {
        data.make_unique();
        return (*data)[i];
    }
    // No copying is necessary when return a constant reference.
    const char& operator[](size_type i) const {
        return (*data)[i];
    }

    size_type size() const {
        return data->size();
    }

private:
    Ptr<Vec<char>> data;
};

std::ostream& operator<<(std::ostream& os, const Str& s) {
    for (Str::size_type i = 0; i != s.size(); ++i)
        os << s[i];
    return os;
}

Str operator+(const Str& s, const Str& t) {
    Str r {s};
    r += t;
    return r;
}

// specialization of the `clone` function defined in Ptr.h to work with class `Vec` (which has no
// `clone` member)
template<>
Vec<char>* clone(const Vec<char>* vp) {
    return new Vec<char>(*vp);
}

#endif

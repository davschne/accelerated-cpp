#include "Grad.h"

using namespace std;

// default constructor
// implicitly calls Core's default constructor
Grad::Grad(): thesis {0} { }

// build from istream
Grad::Grad(istream& is) { read(is); }

istream& Grad::read(istream& in) {
    read_common(in);
    in >> thesis;
    read_hw(in, homework);
    return in;
}

double Grad::grade() const {
    return min(Core::grade(), thesis);
}

Grad* Grad::clone() const {
    return new Grad(*this);
}

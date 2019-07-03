#ifndef GRAD_h
#define GRAD_h

#include "Core.h"

class Grad : public Core {
public:
    Grad();
    Grad(std::istream&);

    std::istream& read(std::istream&) override;
    double grade() const override;

protected:
    Grad* clone() const override;

private:
    double thesis;
};

#endif

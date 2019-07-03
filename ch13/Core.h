#ifndef CORE_h
#define CORE_h

#include <iostream>
#include <string>
#include <vector>

class Core {
    friend class Student_info;
public:
    Core();
    Core(std::istream&);
    virtual ~Core() { }

    std::string name() const;

    virtual std::istream& read(std::istream&);
    virtual double grade() const;

protected:
    // accessible to derived classes
    virtual Core* clone() const;
    std::istream& read_common(std::istream&);
    double midterm, final;
    std::vector<double> homework;

private:
    // accessible only to Core
    std::string n;
};

std::istream& read_hw(std::istream&, std::vector<double>&);

// compare by grade (works for Core and derived classes like Grad)
bool compare_grades(const Core&, const Core&);

#endif

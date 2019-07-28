#ifndef PICTURE_H
#define PICTURE_H

#include <iostream>
#include <string>
#include <vector>

#include "Ptr.h"

// forward declarations
class Picture;
class Pic_base;
class String_Pic;
class Frame_Pic;
class HCat_Pic;
class VCat_Pic;

// operations on Pictures:

// create a Picture by framing an existing Picture
Picture frame(const Picture& pic);
// create a Picture by concatenating two Pictures horizontally
Picture hcat(const Picture& left, const Picture& right);
// create a Picture by concatenating two Pictures vertically
Picture vcat(const Picture& top, const Picture& bottom);
// write a Picture to an output stream
std::ostream& operator<<(std::ostream& os, const Picture& pic);

class Picture {
    friend std::ostream& operator<<(std::ostream&, const Picture&);
    friend Picture frame(const Picture&);
    friend Picture hcat(const Picture&, const Picture&);
    friend Picture vcat(const Picture&, const Picture&);

public:
    Picture(const std::vector<std::string>& = std::vector<std::string> {});

private:
    Picture(Pic_base*);
    Ptr<Pic_base> p;
};

// abstract base class
class Pic_base {
    friend std::ostream& operator<<(std::ostream&, const Picture&);
    friend class String_Pic;
    friend class Frame_Pic;
    friend class HCat_Pic;
    friend class VCat_Pic;

    // type representing indices of the rows of the image
    using ht_sz = std::vector<std::string>::size_type;
    // type representing indices of the columns of the image
    using wd_sz = std::string::size_type;

    // get the height of the picture
    virtual ht_sz height() const = 0;
    // get the width of the picture
    virtual wd_sz width() const = 0;
    // write a row of the image to an output stream, optionally padding the right with spaces
    virtual void display(std::ostream&, ht_sz, bool) const = 0;

public:
    // no public interface, except destructor
    virtual ~Pic_base() { }

protected:
    // write spaces to an output stream using a start and end indices
    static void pad(std::ostream& os, wd_sz beg, wd_sz end);
};

class String_Pic : public Pic_base {
    friend class Picture;
    // data representation: a vector of strings representing rows of characters
    std::vector<std::string> data;

    String_Pic(const std::vector<std::string>& v);

    wd_sz width() const;
    ht_sz height() const;

    void display(std::ostream& os, ht_sz row, bool do_pad) const;
};

class Frame_Pic : public Pic_base {
    friend Picture frame(const Picture&);

    // data representation: a reference-counted smart pointer to the underlying Pic_base
    Ptr<Pic_base> p;

    Frame_Pic(const Ptr<Pic_base>& pic);

    wd_sz width() const;
    ht_sz height() const;

    void display(std::ostream& os, ht_sz row, bool do_pad) const;
};

class HCat_Pic: public Pic_base {
    friend Picture hcat(const Picture&, const Picture&);

    // data representation: left and right sub-pictures
    Ptr<Pic_base> left, right;

    HCat_Pic(const Ptr<Pic_base>& l, const Ptr<Pic_base>& r);

    wd_sz width() const;
    ht_sz height() const;

    void display(std::ostream& os, ht_sz row, bool do_pad) const;
};

class VCat_Pic: public Pic_base {
    friend Picture vcat(const Picture&, const Picture&);

    // data representation: top and bottom sub-pictures
    Ptr<Pic_base> top, bottom;

    VCat_Pic(const Ptr<Pic_base>& t, const Ptr<Pic_base>& b);

    wd_sz width() const;
    ht_sz height() const;

    void display(std::ostream& os, ht_sz row, bool do_pad) const;
};

#endif

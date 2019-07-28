#include <iostream>
#include <string>
#include <vector>

#include "Ptr.h"
#include "Picture.h"

using namespace std;

Picture::Picture(const vector<string>& v) :
    p {new String_Pic(v)}
{ }

Picture::Picture(Pic_base* ptr) : p {ptr} { }

// operations on Pictures:

// create a Picture by framing an existing Picture
Picture frame(const Picture& pic) {
    return new Frame_Pic(pic.p);
}
// create a Picture by concatenating two Pictures horizontally
Picture hcat(const Picture& left, const Picture& right) {
    return new HCat_Pic(left.p, right.p);
}
// create a Picture by concatenating two Pictures vertically
Picture vcat(const Picture& top, const Picture& bottom) {
    return new VCat_Pic(top.p, bottom.p);
}
// write a Picture to an output stream
ostream& operator<<(ostream& os, const Picture& pic) {
    const auto height = pic.p->height();
    for (Pic_base::ht_sz i = 0; i != height; ++i) {
        pic.p->display(os, i, false);
        os << endl;
    }
    return os;
}

// write spaces to an output stream using a start and end indices
void Pic_base::pad(ostream& os, wd_sz beg, wd_sz end) {
    while (beg != end) {
        os << ' ';
        ++beg;
    }
}

String_Pic::String_Pic(const vector<string>& v) : data {v} { }

String_Pic::wd_sz String_Pic::width() const {
    Pic_base::wd_sz n {0};
    for (Pic_base::ht_sz i {0} ; i != data.size(); ++i) {
        n = max(n, data[i].size());
    }
    return n;
}

String_Pic::ht_sz String_Pic::height() const {
    return data.size();
}

void String_Pic::display(ostream& os, ht_sz row, bool do_pad) const {
    wd_sz start {0};

    // write the row if we're still in range
    if (row < height()) {
        os << data[row];
        start = data[row].size();
    }

    // pad the output if necessary
    if (do_pad) {
        pad(os, start, width());
    }
}

Frame_Pic::Frame_Pic(const Ptr<Pic_base>& pic) : p {pic} { }

Frame_Pic::wd_sz Frame_Pic::width() const {
    return p->width() + 4;
}

Frame_Pic::ht_sz Frame_Pic::height() const {
    return p->height() + 4;
}

void Frame_Pic::display(ostream& os, ht_sz row, bool do_pad) const {
    if (row >= height()) {
        // out of range
        if (do_pad)
            pad(os, 0, width());
    } else {
        if (row == 0 || row == height() - 1) {
            // top or bottom row
            os << string(width(), '*');
        } else if (row == 1 || row == height() - 2) {
            // second from top or bottom row
            os << '*';
            pad(os, 1, width() - 1);
            os << '*';
        } else {
            // interior row
            os << "* ";
            p->display(os, row - 2, true);
            os << " *";
        }
    }
}

HCat_Pic::HCat_Pic(const Ptr<Pic_base>& l, const Ptr<Pic_base>& r) : left {l}, right {r} { }

HCat_Pic::wd_sz HCat_Pic::width() const {
    return left->width() + right->width();
}
HCat_Pic::ht_sz HCat_Pic::height() const {
    return max(left->height(), right->height());
}

void HCat_Pic::display(ostream& os, ht_sz row, bool do_pad) const {
    left->display(os, row, do_pad || row < right->height());
    right->display(os, row, do_pad);
}

VCat_Pic::VCat_Pic(const Ptr<Pic_base>& t, const Ptr<Pic_base>& b) : top {t}, bottom {b} { }

VCat_Pic::wd_sz VCat_Pic::width() const {
    return max(top->width(), bottom->width());
}
VCat_Pic::ht_sz VCat_Pic::height() const {
    return top->height() + bottom->height();
}

void VCat_Pic::display(ostream& os, ht_sz row, bool do_pad) const {
    wd_sz w {0};
    if (row < top->height()) {
        // we're in the top subpicture
        top->display(os, row, do_pad);
        w = top->width();
    } else if (row < height()) {
        // we're in the bottom subpicture
        bottom->display(os, row - top->height(), do_pad);
        w = bottom->width();
    }
    if (do_pad) {
        pad(os, w, width());
    }
}

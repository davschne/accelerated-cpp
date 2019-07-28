#include "Picture.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

static const vector<string> text {
    "      .'`'.",
    "  .-./ _=_ \\.-.",
    " {  (,(oYo),) }}",
    " {{ |   \"   |} }",
    " { { \\(---)/  }}",
    " {{  }'-=-'{ } }",
    " { { }._:_.{  }}",
    " {{  } -:- { } }",
    " {_{ }`===`{  _}",
    "((((\\)     (/))))",
};


int main() {
    Picture p {text};
    Picture q {frame(p)};
    Picture r {hcat(p, q)};
    Picture s {vcat(q, r)};
    cout << frame(hcat(s, vcat(r, q))) << endl;
}

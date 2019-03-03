// 7.4/129 Generate sentences based on user-supplied grammar rules

/**
 * Example grammar:
 * 
 * Categories   | Rules
 * --------------------
 * <noun>         cat
 * <noun>         dog
 * <noun-phrase>  <noun>
 * <noun-phrase>  <adjective> <noun-phrase>
 * <adjective>    large
 * <adjective>    brown
 * <verb>         jumps
 * <verg>         sits
 * <location>     on the stairs
 * <location>     under the sky
 * <location>     wherever it wants
 * <sentence>     the <noun-phrase> <verb> <location>
 */

#include <cstdlib>
using std::rand;

#include <iostream>
using std::istream;

#include <map>;
using std::map;

#include <stdexcept>
using std::domain_error;
using std::logic_error;

#include <string>
using std::getline;
using std::string;

#include <vector>
using std::vector;

using Rule = vector<string>;
using Rule_collection = vector<Rule>;
using Grammar = map<string, Rule_collection>;

// read a grammar from a given input stream
Grammar read_grammar(istream& in) {
    Grammar ret;
    string line;

    // read the input
    while (getline(in, line)) {
        // split the input into words
        vector<string> entry {string(line)};
        if (!entry.empty()) {
            // use the category to store the associated rule
            const string& category {entry[0]}; 
            Rule rule {Rule(entry.cbegin() + 1, entry.cend())};
            ret[category].push_back(rule);
        }
    }
    return ret;
}

// Is the string bracketed (i.e. does it represent a category)?
bool bracketed(const string& s) {
    return s.size() > 1 && s[0] == '<' && s[s.size() - 1] == '>';
}

// return a random integer in the range [0, n)
int nrand(int n) {
    if (n <= 0 || n > RAND_MAX) {
        throw domain_error("Argument to nrand is out of range");
    }

    const int bucket_size = RAND_MAX / n;
    int r;

    do
        r = rand() / bucket_size;
    while (r >= n);

    return r;
}

void gen_aux(const Grammar& g, const string& word, vector<string>& ret) {
    if (!bracketed(word)) {
        // `word` is not a category
        ret.push_back(word);
    } else {
        // `word` is a category
        // locate the rule that corresponds to `word`
        auto it = g.find(word);
        if (it == g.cend()) {
            throw logic_error("empty rule");
        }

        // fetch the set of possible rules
        const Rule_collection& c = it->second;

        // from which we select one at random
        const Rule& r = c[nrand(c.size())];

        // recursively expand the selected rule
        for (auto rule : r) {
            gen_aux(g, rule, ret);
        }
    }
}

// generate a <sentence> using the supplied grammar
vector<string> gen_sentence(const Grammar& g) {
    vector<string> ret;
    gen_aux(g, "<sentence>", ret);
    return ret;
}

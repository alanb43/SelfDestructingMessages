#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#include "redact.h"

using std::string;
using std::vector;
using std::istringstream;

/* Returns a string, takes a const ref to a string as the single param. String
 * returned has a # in place of every character of the original message. */
string redact_all_chars(const string& unchanged) {
    string out;
    for (size_t i = 0; i < unchanged.size(); ++i) {
        out += "#";
    }
    return out;
}

/* Returns a string, takes a const ref to string as single param. Redacts only
 * alphanumeric characters. */
string redact_alphabet_digits(const string& unchanged) {
    string out;
    for (auto ch : unchanged) {
        if (isalnum(ch)) {
            out += "#";
        }
        else {
            out += ch;
        }
    }
    return out;
}

/* Takes a const ref to a string (message) and a const ref to a vector of
 * strings containing words to be redacted in the message. Redacts each word
 * from any part of the original message. */
string redact_words(const string& unchanged,
    const vector<string>& words_to_redact) {
    string out = unchanged;
    for (auto redactable : words_to_redact) {
        string redacted;
        for (size_t i = 0; i < redactable.size(); ++i) {
            redacted += "#";
        }
        while (out.find(redactable) != string::npos) {
            size_t index = out.find(redactable);
            size_t index2 = index + redacted.size();  /* where to continue from after
                                                       * redacted portion placed in
                                                       * out string */
            out = out.substr(0, index) + redacted + out.substr(index2);
            std::cout << out << std::endl;
        }
    }
    return out;
}
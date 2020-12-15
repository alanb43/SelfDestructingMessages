#ifndef REDACT_H
#define REDACT_H

#include <string>
#include <vector>

using std::string;
using std::vector;

string redact_all_chars(const string& unchanged);

string redact_alphabet_digits(const string& unchanged);

string redact_words(const string& unchanged,
    const vector<string>& words_to_redact);

#endif

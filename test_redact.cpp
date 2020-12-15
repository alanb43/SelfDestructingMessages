#include <iostream>
using std::cout; using std::endl;
#include <string>
using std::string;
#include <vector>
using std::vector;

#include "redact.h"

int main() {
    // Compile with:
    // g++ -Wall -std=c++14 -g test_redact.cpp redact.cpp
    string s = "The double agent is Josh, who is sitting at (42.73, -84.48). Don't let him get to the university!";

    cout << s << endl;

    cout << redact_all_chars(s) << endl;

    cout << redact_alphabet_digits(s) << endl;

    vector<string> redacted_words = { "sit", "Josh", "slinky" };
    cout << redact_words(s, redacted_words) << endl;

    /* Expected output:
    The double agent is Josh, who is sitting at (42.73, -84.48). Don't let him get to the university!
    #################################################################################################
    ### ###### ##### ## ####, ### ## ####### ## (##.##, -##.##). ###'# ### ### ### ## ### ##########!
    The double agent is ####, who is ###ting at (42.73, -84.48). Don't let him get to the univer###y!
    */

}

#include <iostream>
using std::cout; using std::endl;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <cassert>
#include <stdexcept>
using std::invalid_argument; using std::out_of_range;
#include<sstream>
using std::stringstream;

#include "self_destructing.h"
#include "redact.h"

int main() {
    // Compile with:
    // g++ -Wall -std=c++14 -g test_self_destructing.cpp self_destructing.cpp redact.cpp
    vector<string> m = {
        "The plan is go!!!",
        "Attack - at - midnight",
        "Bring 97 cookies!" };

    SelfDestructingMessage sdm(m, 2);
    cout << "Size is " << sdm.size() << endl; // Size is 3

    vector<string> redacted_lines = sdm.get_redacted();
    string redacted_first_line = redact_alphabet_digits(m[0]);
    assert(redacted_first_line == redacted_lines[0]); // Should be true

    cout << "Views remaining on first line: "
        << sdm.number_of_views_remaining(0) << endl;
    // Views remaining on first line: 2

    cout << sdm[0] << endl;
    // The plan is go!!!

    cout << "Views remaining on first line (after operator[]): "
        << sdm.number_of_views_remaining(0) << endl;
    // Views remaining on first line (after operator[]): 1
    cout << "Views remaining on second line (after operator[]): "
        << sdm.number_of_views_remaining(1) << endl;
    // Views remaining on second line (after operator[]): 2

    sdm[0];
    sdm[2];

    try {
        sdm[0];
    }
    catch (invalid_argument& e) {
        cout << "Can't access first line again." << endl;
    }
    // Can't access first line again.

    try {
        sdm[-1];
    }
    catch (out_of_range& e) {
        cout << "No negative indices." << endl;
    }
    // No negative indices.

    try {
        sdm[3];
    }
    catch (out_of_range& e) {
        cout << "No too large indicies." << endl;
    }
    // No too large indicies.


    cout << "redacted message:" << endl << sdm;
    // Note the zero padded number of access left for each line.
    /*
    redacted message:
    00: ### #### ## ##!!!
    02: ###### - ## - ########
    01: ##### ## #######!
    */

    SelfDestructingMessage sdm2;
    cout << "Default Size: " << sdm2.size() << endl;
    // Default Size: 0

    SelfDestructingMessage sdm3(sdm);
    cout << "Copy Constructed:" << endl << sdm3;
    /*
    Copy Constructed:
    00: ### #### ## ##!!!
    02: ###### - ## - ########
    01: ##### ## #######!
    */



    cout << "Old message has no views left:" << endl << sdm;
    /*
    Old message has no views left:
    00: ### #### ## ##!!!
    00: ###### - ## - ########
    00: ##### ## #######!
    */

    SelfDestructingMessage sdm4 = sdm3;
    cout << "Left side of assignment:" << endl << sdm4;
    /*
    Left side of assignment:
    00: ### #### ## ##!!!
    02: ###### - ## - ########
    01: ##### ## #######!
    */

    cout << "Right side of assignment:" << endl << sdm3;
    /*
    Right side of assignment:
    00: ### #### ## ##!!!
    00: ###### - ## - ########
    00: ##### ## #######!
    */

    string additional_lines[3] = { "One more line",
                                 "two more line",
                                 "three more line" };
    sdm4.add_array_of_lines(additional_lines, 3);
    cout << "After add_array_of_lines:" << endl << sdm4;
    /*
    After add_array_of_lines:
    00: ### #### ## ##!!!
    02: ###### - ## - ########
    01: ##### ## #######!
    02: ### #### ####
    02: ### #### ####
    02: ##### #### ####
    */

    stringstream ss("one very long line to add via stream");
    ss >> sdm4;
    cout << "After stream insertion:" << endl << sdm4;
    /*
    After stream insertion:
    00: ### #### ## ##!!!
    02: ###### - ## - ########
    01: ##### ## #######!
    02: ### #### ####
    02: ### #### ####
    02: ##### #### ####
    02: ### #### #### #### ## ### ### ######
    */

}

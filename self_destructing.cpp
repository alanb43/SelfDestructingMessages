#include <string>
#include <vector>
#include <ios>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <algorithm>

#include "self_destructing.h"
#include "redact.h"

using std::string;
using std::vector;
using std::invalid_argument;
using std::out_of_range;
using std::ostream;
using std::endl;
using std::getline;

/* Returns void, takes two refs to SelfDestructingMessage(s) and swaps their main
 * components. */
void swap(SelfDestructingMessage& sdm1, SelfDestructingMessage& sdm2) {
    sdm1.messages_ = sdm2.messages_;
    sdm1.num_allowed_views_ = sdm2.num_allowed_views_;
    sdm1.allowed_views_left_ = sdm2.allowed_views_left_;
}

/* No-arg constructor. Initializes messages vector to empty and number of times
 * a message can be viewed to 0 */
SelfDestructingMessage::SelfDestructingMessage() {
    messages_ = {};
    num_allowed_views_ = 0;
}

/* Constructor assigning pre-determined messages and number of times a message
 * can be viewed. Adds starting values for vector tracking number of views the
 * messages have left */
SelfDestructingMessage::SelfDestructingMessage(vector<string> m, long n) {
    messages_ = m;
    num_allowed_views_ = n;
    int num_messages_ = messages_.size();
    for (int i = 0; i < num_messages_; ++i) {
        allowed_views_left_.push_back(num_allowed_views_);
    }
}

/* Copy constructor, transfers main private class info to new object using swap
 * function and sets the number of remaining views for all messages in the
 * original object to zero. */
SelfDestructingMessage::SelfDestructingMessage(SelfDestructingMessage& sdm) {
    swap(*this, sdm);
    for (size_t i = 0; i < sdm.messages_.size(); ++i) {
        sdm.allowed_views_left_[i] = 0;
    }
}

/* Returns vector of strings containing redacted-form messages: uses
 * redact_alphabetic_digits from redact.cpp/.h to redact all alphanumeric
 * characters from each string in the messages vector. */
vector<string> SelfDestructingMessage::get_redacted() {
    vector<string> redacted;
    for (auto message : messages_) {
        redacted.push_back(redact_alphabet_digits(message));
    }
    return redacted;
}

/* Returns the number of views a message has left until it is locked forever.
 * Message index is the parameter. */
long SelfDestructingMessage::number_of_views_remaining(size_t message_index) {
    return allowed_views_left_[message_index];
}

/* Returns void, takes an array of strings and its size as parameters and adds
 * the strings in the array to the messages vector as well as the number of
 * allowed views to the views left vector. */
void SelfDestructingMessage::add_array_of_lines(string ary[], long ary_size) {
    for (long i = 0; i < ary_size; ++i) {
        messages_.push_back(ary[i]);
        allowed_views_left_.push_back(num_allowed_views_);
    }
}

/* Returns a const ref to a string, takes a size_t value representing an index
 * as a param. Either returns the message at the index or throws an error based
 * on whether the index was incorrect or if the message is locked. */
const string& SelfDestructingMessage::operator[](size_t index) {
    if (index >= messages_.size() || index < 0) {
        throw out_of_range("Index out of range");
    }
    else if (allowed_views_left_[index] == 0) {
        throw invalid_argument("No views remaining");
    }
    allowed_views_left_[index]--;
    return messages_[index];
}

/* Returns void, takes a reference to a SelfDestructingMessage. Same
 * functionality as copy constructor, using swap function to move main values to
 * new object but through assignment. */
SelfDestructingMessage& SelfDestructingMessage::operator=(SelfDestructingMessage sdm) {
    swap(*this, sdm);
    for (size_t i = 0; i < sdm.messages_.size(); ++i) {
        sdm.allowed_views_left_[i] = 0;
    }
    return *this;
}

/* Returns a reference to an ostream, takes a reference to an ostream and a
 * reference to a SelfDestructingMessage. Ostream outputs the views left for a
 * message and the associated redacted message using << operator. */
ostream& operator<<(ostream& os, SelfDestructingMessage& sdm) {
    vector<string> redacted = sdm.get_redacted();
    for (size_t i = 0; i < redacted.size(); ++i) {
        os << "0" << sdm.number_of_views_remaining(i) << ": " << redacted[i]
            << endl;
    }
    return os;
}

/* Returns a ref to an istream, takes a ref to an istream and a ref to a
 * SelfDestructingMessage as params. Allows for new messages to be added to the
 * SelfDestructingMessage object using the >> operator. */
istream& operator>>(istream& is, SelfDestructingMessage& sdm) {
    string new_msg;
    char c;
    while (is.get(c)) {
        new_msg += c;
    }
    sdm.messages_.push_back(new_msg);
    sdm.allowed_views_left_.push_back(sdm.num_allowed_views_);
    return is;
}
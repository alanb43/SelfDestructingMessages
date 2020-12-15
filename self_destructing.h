#ifndef SELF_DESTRUCTING_H
#define SELF_DESTRUCTING_H

#include <string>
#include <vector>
#include <ios>
#include <iostream>

using std::string;
using std::vector;
using std::ostream;
using std::istream;

/* Creates a Self Destructing Message Capsule that stores messages & the amount
 * of times they can be viewed until being locked forever, with methods and
 * overloaded operators for user accessibility.*/
class SelfDestructingMessage {
private:
	vector<string> messages_;
	long num_allowed_views_;
	vector<long> allowed_views_left_;

public:
	// Constructors
	SelfDestructingMessage();
	SelfDestructingMessage(vector<string>, long);
	SelfDestructingMessage(SelfDestructingMessage&);
	// Methods
	long size() { return messages_.size(); }
	vector<string> get_redacted();
	long number_of_views_remaining(size_t);
	void add_array_of_lines(string[], long);
	// Operators & Friends
	const string& operator[](size_t);
	SelfDestructingMessage& operator=(SelfDestructingMessage);
	friend ostream& operator<<(ostream&, SelfDestructingMessage&);
	friend istream& operator>>(istream&, SelfDestructingMessage&);
	friend void swap(SelfDestructingMessage&, SelfDestructingMessage&);
};

void swap(SelfDestructingMessage&, SelfDestructingMessage&);

#endif

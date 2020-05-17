/*
File: string.cpp
Description:
Course: 150018 C++ Workshop, Exercise 4, Question 2
Author: Dan Zilberstein
Students: eli iluz 311201354
		& avishay farkash 205918790
*/

#include <cstring>
#include "String.h"
#include "IndexExeption.h"
#pragma warning( disable : 4996)

using namespace std;
// C-string based Constructor (CTOR)
String::String(const char* s) : str(nullptr) {       // initialize the fields
	setString(s);
}
// Copy CTOR
String::String(const String& other) : str(nullptr) { // initialize the fields
	setString(other.str);
}
// Move CTOR
String::String(String&& other) : str(other.str) {    // initialize with other's data
   // Avoid temp object DTOR removing the dynamic data which is now used in our object
	other.str = nullptr;
}
// Destructor (DTOR)
String::~String() {
	delete[] str; // delete operators handle nullptr by themselves
	str = nullptr;
}

// String getter (Viewer) which returns a dynamic c-string (char array)
// The caller is responsible to free this array after using it
char* String::getString() const {
	if (str == nullptr) return nullptr;  // there is nothing to return...
	unsigned int length = strlen(str) + 1; // calculate the length
	char* temp = new char[length];         // allocate the char array
	strncpy(temp, str, length);            // copy the content
	return temp;
}

// String setter (Modifier)
void String::setString(const char* s) {
	// Protect when setting to the same char array
	if (s == str) return;
	delete[] str; // Free old string dynamic data memory

	if (s != nullptr) { // Create new dynamic char array and copy the content
		unsigned int length = strlen(s) + 1; // calc the length
		str = new char[length];              // allocate new array
		strncpy(str, s, length);             // copy the content
	}
	else // Nullify the string pointer
		str = nullptr;
}

// Copy assignment operator
String& String::operator = (const String& s) {
	if (this == &s) return *this; // Protection from assigning the object to itself
	delete[] str;
	str = nullptr;
	setString(s.str);
	// Allow chained assignments
	return *this;
}

// Move assignment operator
String& String::operator = (String&& s) {
	delete[] str; // Free old string dynamic data memory
	str = s.str;  // Update the pointer
	s.str = nullptr; // Avoid temp object DTOR removing the data now used in our object
	return *this;
}
// Operators

String& String::operator += (const String& rhs) {
	if (rhs.str == nullptr || strlen(rhs.str) == 0) // nothing to add
		return *this;

	if (str == nullptr) { // we have nothing => like a copy ctor
		setString(rhs.str);
		return *this;
	}

	// Create new c-string with appropriate length
	char* temp = new char[strlen(str) + strlen(rhs.str) + 1];
	strcpy(temp, str);     // copy there our original string
	strcat(temp, rhs.str); // concatenate there the second string
	delete[] str;          // free our old memory
	str = temp;            // set now to the new string
	return *this;
}

String operator + (String lhs, const String& rhs) {
	lhs += rhs; // Concatenate second string to the first (local - by value)
	return lhs; // return by value - it will use Move Ctor
}

String& String::operator *= (unsigned int rhs) {
	if (str == nullptr || rhs == 1 || strlen(str) == 0) // nothing to replicate
		return *this;

	if (rhs == 0) { // empty us
		delete[] str;
		str = nullptr;
		return *this;
	}

	// Create new c-string with appropriate length
	char* temp = new char[strlen(str) * rhs + 1];
	strcpy(temp, str);      // First time - copy myself to there
	while (--rhs != 0)       // While there are more replications to do
		strcat(temp, str);  //    concatenate myself to there (again and again)

	delete[] str;          // free our old memory
	str = temp;            // set now to the new string
	return *this;
}

int String::operator[](const String& cIndex) const
{
	if (cIndex.getString() == nullptr || cIndex.getString()[0] == 0)
		throw nullptr;

	int i;
	bool isFound = false;
	for (i = 0; !isFound && str[i] != 0; i++)
		for (int j = 0; cIndex.getString()[j] != 0 && (isFound = cIndex.getString()[j] == str[j + i]); j++);

	if(!isFound)
		throw cIndex;

	return i - 1;
}

String operator*(String lhs, unsigned int rhs) {
	lhs *= rhs; // Replicate inside the first (local - by value)
	return lhs; // return by value - it will use Move Ctor
}

ostream& operator<<(ostream& out, String& output)
{
	if (output.str != nullptr)
		out << output.str;
	out << "";

	return out;
}

std::istream& operator>>(std::istream& in, String& input)
{
	char temp[101];  //assumes that the input string not bigger than 100 letters

	in.getline(temp, 101);

	input.setString(temp);

	return in;
}

bool String::operator == (const String& rhs) const {
	return !strcmp(str, rhs.str);
}

bool String::operator!=(const String& rhs) const
{
	return !(str == rhs.str);
}

bool String::operator>=(const String& rhs) const
{
	return (strcmp(str, rhs.str) > -1);
}

bool String::operator<=(const String& rhs) const
{
	return (strcmp(str, rhs.str) < 1);
}

bool String::operator>(const String& rhs) const
{
	return !(*this <= rhs);
}

bool String::operator<(const String& rhs) const
{
	return !(*this >= rhs);
}

// Public functions

String& String::insert(int index, const char* str) const
{
	if (index >= strlen(this->str))
		throw IndexException(index, strlen(this->str));

	char* temp = new char[index + 1];

	strncpy(temp, this->str, index);
	temp[index] = 0;
	String* insStr = new String(temp);

	delete[] temp;
	temp = nullptr;

	return (*insStr += String(str));
}

int String::length() const {
	return strlen(str);
}

void String::print() const {
	if (str != nullptr)
		cout << str;
	cout << endl;
}


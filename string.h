/*
File: string.h
Description:
Course: 150018 C++ Workshop, Exercise 4, Question 2
Author: Dan Zilberstein
Students: eli iluz 311201354
		& avishay farkash 205918790
*/
#ifndef __STRING_H
#define __STRING_H

#include <iostream>


class String {
private:
	char* str;                      // Internal data container - for dynamic c-string
	void setString(const char* s);   // Modifier - for internal usage
public:
	// constructors
	String(const char* s = nullptr); // Default and from c-string
	String(const String& s);         // Copy ctor
	String(String&& s);              // Move ctor
	~String();                       // Dtor

	char* getString() const;         // Viewer

	// Operators
	String& operator = (const String&);     // Copy Assignment
	String& operator = (String&&);          // Move Assignment
	bool operator == (const String&) const; // Equality
	bool operator != (const String&) const; // Inequality
	bool operator >= (const String&) const; // First not smaller than second
	bool operator <= (const String&) const; // First not bigger than second
	bool operator > (const String&) const; // First bigger than second
	bool operator < (const String&) const; // First smaller than second
	String& operator += (const String&);    // Addition to object by concatenation
	friend String operator + (String, const String&); // Symmetric addition as friend
	String& operator *= (unsigned int);     // Multiplication by replicating
	friend String operator * (String, unsigned int);  // Symmetric multiplication as friend
	friend std::ostream& operator << (std::ostream& out, String&); //input operator
	friend std::istream& operator >> (std::istream& in, String&); //input operator
	// gets a c - string for index
	// return the index of the first letter of the the first appearance
	int operator [] (const String&) const;

	// Public functions

	// the function gets index and c - string
	// and return a new string with the original string til the index
	// and the input string from there(the function doesn't change the original string)
	String& insert(int index, const char* str) const;

	int length() const; // Length of the string
	void print() const; // Print the string
};

std::ostream& operator << (std::ostream& out, String&);
String operator + (String, const String&); // Declaration of addition operator (global)
String operator * (String, unsigned int);  // Declaration of mulitiplication oeprator (global)

#endif // __STRING_H


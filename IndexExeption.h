/*
File: indexExeption
Description:
Course: 150018 C++ Workshop, Exercise 4, Question 2
Author: Dan Zilberstein
Students: eli iluz 311201354
		& avishay farkash 205918790
*/
#ifndef IE_H
#define IE_H

struct IndexException {
	unsigned int index;
	unsigned int maxIndex;
	IndexException(int ind, int max) : index(ind), maxIndex(max) {}
};

#endif // !IE_H


/*
File: main.cpp
Description:
Course: 150018 C++ Workshop, Exercise 4, Question 2
Author: Dan Zilberstein
Students: eli iluz 311201354
		& avishay farkash 205918790
*/
#include <iostream>
#include <iomanip>
#include "String.h"
#include "indexExeption.h"



using namespace std;

// These are all of the main menu options.  Note that the numbers:
// 0, 1, 2, etc., show up /nowhere/ in the code, even though the
// user will see them on the screen, and will input them for
// choosing a menu option.
// Add your menu options according the the exercise requirements
enum MenuOption {
	EXIT_MENU,
	CREATE_TWO_STRINGS,
	COMPARE,
	INSERT,
	SEARCH,
	// a neat trick for for-loop initial and final values
	FIRST_MENU_OPTION = EXIT_MENU,
	LAST_MENU_OPTION = SEARCH
};

// These strings will be seen by the user, on the main menu.  They
// must be kept consistent with the operations of menu_option
// above.
const char* const menuOptionStrings[] = {
	"exit the program",
	"input two strings(A,B)",
	"compare A and B",
	"insert A to B and do opposite by index",
	"search B in A",
};

// Function main - this is the entry code for the program
// It prints menu and performs the action according to the chosen option.
int main(void) {
	MenuOption chosen;

	String a(""), b("");
	// Everything happens inside of this do-while loop, until the user
	//     has decided to exit (or an error occurs).
	do {
		cout << endl << "Menu options:" << endl << endl;

		const int menuIndent = 10;

		// The user will see:
		//
		//           0 -- exit
		//           1 -- input two strings(A,B)
		//           2 -- compare A and B
		// etc.
		//
		// The casts are for doing the "++" as an int type since
		// they are not allowed as a MenuOption type.
		for (chosen = FIRST_MENU_OPTION; chosen <= LAST_MENU_OPTION;
			chosen = (MenuOption)((int)chosen + 1)) {
			cout << setw(menuIndent) << " " << chosen << " -- ";
			cout << menuOptionStrings[chosen] << endl;
		}
		cout << endl;

		int chosenInt;
		cout << "Please choose a menu option: ";
		cin >> chosenInt;
		// After the user has input an int, it is cast to a
		//   MenuOption variable.
		chosen = (MenuOption)chosenInt;

		

		switch (chosen)
		{
		case CREATE_TWO_STRINGS:
			cout << endl << "A = ";
			cin.get();
			cin >> a;
			cout << endl << "B = ";
			cin >> b;
			cout << endl;
			break;
		case COMPARE:
			if (a == b)
				cout << endl << "A = B";
			else if (a < b)
				cout << endl << "A < B";
			else
				cout << endl << "A > B";
			cout << endl;
			break;
		case INSERT:
			int index;

			cout << endl << "Enter a index to insert from: ";
			cin >> index;

			cout << endl << "B to A: ";
			try
			{
				cout << "\"" << a.insert(index, b.getString()) << "\"" << endl;
			}
			catch (IndexException exp)
			{
				cout << endl << "ERROR: the index[" << exp.index << "] out of A range(" << exp.maxIndex << ")" << endl;
			}

			cout << endl << "A to B: ";
			try
			{
				cout << "\"" << b.insert(index, a.getString()) << "\"" << endl;
			}
			catch (IndexException exp)
			{
				cout << endl << "ERROR: the index[" << exp.index << "] out of B range(" << exp.maxIndex << ")" << endl;
			}

			break;
		case SEARCH:

			cout << endl;
			try {
				cout << "B appears first time in A from index - [" << a[b] << "]" << endl;
			}
			catch (void*)
			{
				cout << "ERROR: no string in B." << endl;
			}
			catch (String str)
			{
				cout << "ERROR: \"" << str << "\" not found in A." << endl;
			}
			break;
		default:
			break;
		}
	} while (chosen != EXIT_MENU);

	return 0;
}

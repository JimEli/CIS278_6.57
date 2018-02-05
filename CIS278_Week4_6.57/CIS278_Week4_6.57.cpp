/*************************************************************************
* Title: Computer-Assisted Instruction
* File: CIS278_Week4_6.57.cpp
* Author: James Eli
* Date: 1/19/2018
*
* Exercise 6.57 on page 281 (Computer-Assisted Instruction) The use of 
* computers in education is referred to as computer-assisted instruction 
* (CAI). Write a program that will help an elementary-school student to 
* learn multiplication. Use the rand function to produce two positive 
* one-digit integers. The program should then prompt the user with a 
* question, such as
*   How much is 6 times 7?
* The student then inputs the answer. Next, the program checks the 
* student’s answer. If it’s correct, display the message "Very good!" 
* and ask another multiplication question. If the answer is wrong, display 
* the message "No. Please try again." And let the student try the same 
* question repeatedly until the student finally gets it right. A separate 
* function should be used to generate each new question. This function 
* should be called once when the application begins execution and each 
* time the user answers the question correctly.

* Notes:
*  (1) Compiled with MS Visual Studio 2017 Community (v141).
*
* Submitted in partial fulfillment of the requirements of PCC CIS-278.
*************************************************************************
* Change Log:
*   01/19/2018: Initial release. JME
*************************************************************************/
#include <iostream>  // cin/cout/endl
#include <string>    // string
#include <ctime>     // time for random seed
#include <random>    // random

using namespace std;

int getAnswer(string question) 
{
	// Validate input of answer.
	while (true)
	{
		// Temporary holds user input.
		int number;

		cout << question;
		// Get user input of product number and quantity.
		cin >> number;
		if (number == -1)
			// Exit.
			return -1;

		// Eat trailing chars in stream.
		while (cin.peek() != '\n')
		{
			if (cin.peek() == -1)
				break;
			cin.ignore(1, '\n');
		}

		// Check for non-integer input.
		if (cin.fail())
		{
			// Clear failure flag and discard any remaining input.
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Please enter only integer values.\n";
		}
		else
		{
			// Check answer within limits.
			if (number < 0 || number > 81)
				cout << "Answer must be between 0 and 81.\n";
			else
				return number;
		}
	}
}

// Make up a multiplication problem, determine answer and ask quetion. 
bool askMultiplication(void) 
{
	int multiplicand, multiplier, result, answer;
	// Random number generator [0 - 9].
	auto rn = []{ return int(10 * rand() / (RAND_MAX + 1.0)); };

	// Make up question, determine correct answer.
	multiplicand = rn();
	multiplier = rn();
	result = multiplicand * multiplier;

	// Repaet same question until the student finally gets it right. 
	do {
		// Display question, get an answer.
		answer = getAnswer("How much is " + to_string(multiplicand) + " times " + to_string(multiplier) + "? ");

		if (answer == -1)
			return false;
		else if (answer == result)
			// If it’s correct, display the message 
			cout << "Very good!\n";
		else
			// If the answer is wrong, display
			cout << "No. Please try again.\n";
	} while (answer != result);

	return true;
}

int main()
{
	// Seed the rng.
	srand((unsigned)time(0));

	// Repeat sking questions.
	while(askMultiplication());

 	return 0;
}

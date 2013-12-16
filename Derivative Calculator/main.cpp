// main.cpp - Derivative Calculator Main Program entry point
// By Sean J. Lane

// TOTAL LINES OF CODE: 820

#include <iostream>
#include <string>
#include "Derivative.h"
#include "Polynomial.h"

using namespace std;

#define DEFAULT 1

void TakeDerivative(const string& baseExpression);

void main()
{
	cout << "************************ Derivative Simplifier Program ************************" << endl << endl;

	// Test functionality
	cout << "Functionality test: 5x^3+3x^3";
	TakeDerivative("5x^3+3x^3");
	cout << endl;

	// Test functionality
	cout << "Functionality test: 4x^3*2x^55";
	TakeDerivative("4x^3*2x^55");
	cout << endl;

	// Test functionality
	cout << "Functionality test: 4x^3/2x^55";
	TakeDerivative("4x^3/2x^55");
	cout << endl;

	// Test functionality
	cout << "Functionality test: sin(5x^3*3x^4)";
	TakeDerivative("sin(5x^3*3x^4)");
	cout << endl;

	// Test functionality
	cout << "Functionality test: cos(5x^3*3x^4)";
	TakeDerivative("cos(5x^3*3x^4)");
	cout << endl;

	// Test functionality
	cout << "Functionality test: exp(5x^3)";
	TakeDerivative("exp(5x^3)");
	cout << endl;

	// Test functionality
	cout << "Functionality test: log(5x^3)";
	TakeDerivative("log(5x^3)");

	// Run a simple loop to get user input
	int i = DEFAULT;
	while (i == DEFAULT)
	{
		// Recieve user input as an Derivative
		string input;
		cout << "*******************************************************************";
		cout << endl << endl << "Please enter an expression: ";
		getline(cin,input);
		TakeDerivative(input);

		// control variable to control loop
		cout << "Enter another expression? 1 for yes, 0 for no: ";
		cin >> i;
		cin.ignore();
		cout << endl;
	}

	cout << endl << endl;
	system("pause");
}
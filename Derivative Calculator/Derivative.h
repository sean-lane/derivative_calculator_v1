// Derivative.h - Derivative class declaration
// By Sean J. Lane

#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Derivative
{
public:
	// Default constructor
	Derivative()
	{
		Constant = Exponent = NULL;
		Variable = "";
		Operation = ' ';
	}

	// Init-constructor (using string)
	Derivative(float& constant, const string& variable, float& exponent, const char& operation)
	{
		Constant = constant;
		Exponent = exponent;
		Variable = variable;
		Operation = operation;
	}

	// Pure virtual method to take derivative of different classes
	virtual void TakeDerivative() = 0;

	// function to print each result
	virtual void Print() = 0;

	// Public Data members for usage in subclass to subclass functions
	float Exponent;
	float Constant;
	string Variable;
	char Operation;
};
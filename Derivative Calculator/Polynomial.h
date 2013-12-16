// Polynomial.h - Polynomial derivative class declaration
// Written by Sean J. Lane

#pragma once

#include "Derivative.h"

using namespace std;

class Polynomial: public Derivative
{
public:
	// Default constructor for class
	Polynomial()
	{
		Constant = NULL;
		Variable = "";
		Exponent = NULL;
		Operation = ' ';
	}

	// Init-constructor for class
	Polynomial(float& constant, const string& variable, float& exponent, const char& operation) : Derivative(constant,variable,exponent,operation)
	{
		Constant = constant;
		Variable = variable;
		Exponent = exponent;
		Operation = operation;
	}

	// Derivative function; different for each type of input
	virtual void TakeDerivative()
	{
		Constant = (Constant*Exponent);
		Exponent--;
	}

	// function to print each result
	virtual void Print()
	{
		// if function to weed out unecessary spaces
		if (Operation != ' ')
		{
			cout << Constant << Variable << "^" << Exponent << Operation;
		}
		else
		{
			cout << Constant << Variable << "^" << Exponent;
		}
	}
};
// Quotient.h - Quotient derivative class declaration
// Written by Sean J. Lane

#pragma once

#include "Derivative.h"
#include "Polynomial.h"

using namespace std;

#define DEFAULT 1

class Quotient: public Derivative
{
public:
	// Default constructor for class
	Quotient();

	// Init-constructor for class
	Quotient(const Polynomial& expression1, const Polynomial& expression2)
	{
		Expression1 = expression1;
		Expression2 = expression2;
		Constant = DEFAULT;
		Variable = expression1.Variable;
		Exponent = DEFAULT;
		Operation = NULL;
	}

	// Pure virtual method to take derivative of different classes
	virtual void TakeDerivative()
	{
		// initialize intermediate variable for number manipulation: f(x), g(x), f'(x), and g'(x)
		Intermediate1 = Expression1;
		Intermediate2 = Expression2;
		Expression1.TakeDerivative();
		Expression2.TakeDerivative();

		// put variables into Quotient rule
		Expression1.Constant = Expression1.Constant * Intermediate2.Constant;
		Expression2.Constant = Expression2.Constant * Intermediate1.Constant;
		Constant = ((Expression1.Constant - Expression2.Constant) / (Intermediate2.Constant * Intermediate2.Constant));
		Exponent = ((Expression1.Exponent + Intermediate2.Exponent) - (Intermediate2.Exponent + Intermediate2.Exponent));
		Variable = Expression2.Variable;
		Operation = Expression2.Operation;
	}

	// function to print current output
	virtual void Print()
	{
		// Print result (one combined polynomial)
		cout << Constant << Variable << "^" << Exponent << Operation;
	}

private:
	Polynomial Expression1, Expression2, Intermediate1, Intermediate2;
};
// Chain.h - chain rule class implementation
// By Sean J. Lane

#pragma once

#include "Derivative.h"
#include "Chain.h"

using namespace std;

class Trig: public Derivative
{
public:
	// Default constructor for class
	Trig();

	// init-constructor for class
	Trig(string& expression, float& constant, string& variable, float& exponent, char& operation) : Derivative(constant,variable,exponent,operation)
	{
		// Initialize class data members
		Expression = expression;
		TrigVector = Parse(Expression);
		
		// Initialize default derivative variables
		Constant = constant;
		Variable = variable;
		Exponent = exponent;
		Operation = operation;
	}

	// virtual method to take derivative of different classes
	virtual void TakeDerivative()
	{
		// Within subclasses, take individual derivatives
		for (unsigned int i = 0; i < TrigVector.size(); i++)
		{
			TrigVector[i]->TakeDerivative();
		}

		// Take derivative of Trig object
		Constant = (Constant * Exponent);
		Exponent = (Exponent - 1);

		
	}

	// function to print each result
	virtual void Print()
	{
		// Print new trig expression
		if (Variable == "c")
		{
			cout << Constant << "cos(" << Expression << ")^" << Exponent << "(";
		}
		else
		{
			cout << Constant << "-sin(" << Expression << ")^" << Exponent << "(";
		}

		// print vector for chain rule
		for (unsigned int i = 0; i < TrigVector.size(); i++)
		{
				TrigVector[i]->Print();
		}
		cout << ")" << Operation;
	}
private:
	string Expression;
	vector<Derivative*> TrigVector;
};
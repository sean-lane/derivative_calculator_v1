// Chain.h - chain rule class implementation
// By Sean J. Lane

#pragma once

#include "Derivative.h"
#include "Polynomial.h"

using namespace std;

#define FUNC_SIN "S"
#define FUNC_COS "C"
#define FUNC_EXP "E"
#define FUNC_LOG "L"
#define FUNC_NEG_SIN "-S"

// include parse function to handle interior of chain polynomial
vector<Derivative*> Parse(const string& baseExpression1);

class Chain: public Derivative
{
public:
	// Default constructor for class
	Chain();

	// init-constructor for class
	Chain(const string& expression, float& constant, string& variable, float& exponent, char& operation) : Derivative(constant,variable,exponent,operation)
	{
		// Initialize class data members
		Expression = expression;
		ChainVector = Parse(Expression);

		// Delete extra space from parsing expression
		string::iterator pos = Expression.begin();
		pos += (Expression.size() - DEFAULT);
		Expression.erase(pos);
		
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
		for (unsigned int i = 0; i < ChainVector.size(); i++)
		{
			ChainVector[i]->TakeDerivative();
		}

		// Take derivative of chain rule object
		Constant = (Constant * Exponent);

		// Calculate trig derivative if necessary
		if (Variable == FUNC_SIN)
		{
			Variable = FUNC_COS;
		}
		else if (Variable == FUNC_COS)
		{
			Variable = FUNC_NEG_SIN; // negative sin
		}
	}

	// function to print each result
	virtual void Print()
	{
		if (Variable != FUNC_LOG)
		{
			// Print new trig expression
			if (Variable == FUNC_COS)
			{
				// Don't display the one in front of functions if its there
				if (Constant == DEFAULT)
				{
					cout << "cos(" << Expression << ")" << "(";
				}
				else
				{
					cout << Constant << "cos(" << Expression << ")" << "(";
				}
			}
			else if (Variable == FUNC_NEG_SIN)
			{
				// Same procedure as sin
				if (Constant == DEFAULT)
				{
					cout << "-" << "sin(" << Expression << ")" << "(";
				}
				else
				{
					cout << "-" << Constant << "sin(" << Expression << ")" << "(";
				}
			}
			// Print exp function if exp is current case
			else if (Variable == FUNC_EXP)
			{
				if (Constant == DEFAULT)
				{
					cout << "exp(" << Expression << ")" << "(";
				}
				else
				{
					cout << Constant << "exp(" << Expression << ")" << "(";
				}
			}
			else
			{
				cout << Constant << "(" << Expression << ")^" << Exponent << "(";
			}

			// print vector
			for (unsigned int i = 0; i < ChainVector.size(); i++)
			{
					ChainVector[i]->Print();
			}
			cout << ")" << Operation;
		}
		// Handle log function situations
		else
		{
			cout << (ChainVector[NULL]->Exponent + DEFAULT) << "/" << ChainVector[NULL]->Variable << Operation;
		}
	}

private:
	string Expression;
	vector<Derivative*> ChainVector;
};
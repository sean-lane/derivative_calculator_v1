// main.cpp - Derivative Calculator Main Program entry point
// By Sean J. Lane

#include <iostream>
#include <string>
#include "Derivative.h"
#include "Polynomial.h"

using namespace std;

vector<Derivative*> Parse(const string& baseExpression1);

void TakeDerivative(const string& baseExpression)
{
	string expression = baseExpression;

	// Initialize vector to catch result
	vector<Derivative*> derivatives;

	// Parse input into polynomial classes (polynomial, trig, function) by passing to Derivative class
	derivatives = Parse(expression);

	// Within subclasses, implement derivative() function. Use virtual method for varied subclasses
	for (unsigned int i = NULL; i < derivatives.size(); i++)
	{
		derivatives[i]->TakeDerivative();
	}

	// Simplify the final vector
	for (unsigned int i = NULL; i < derivatives.size(); i++)
	{
		for (unsigned int j = NULL; j < derivatives.size(); j++)
		{
			if ((derivatives[i]->Variable == derivatives[j]->Variable)&&(derivatives[i]->Exponent == derivatives[j]->Exponent)&&(derivatives[i]->Variable == "x")&&(i != j))
			{
				// Push from vector into intermediate polynomials
				float constant = derivatives[i]->Constant;
				float exponent = derivatives[i]->Exponent;
				string variable = derivatives[i]->Variable;
				char operation = derivatives[j]->Operation;

				// simplify the constants of the two polynomials
				if (derivatives[i]->Operation == '+')
				{
					constant += derivatives[j]->Constant;
				}
				else
				{
					constant -= derivatives[j]->Constant;
				}

				// Push new Product object into the vector in place of polynomial at i
				derivatives[j] = (new Polynomial(constant,variable,exponent,operation));

				// Delete polynomial at j
				vector<Derivative*>::iterator pos = derivatives.begin();
				pos += i;
				derivatives.erase(pos);
			}
		}
	}
	
	// simply out 0th power vector elements and 0 constant elements, and elements with no variable (just constant & exponent)
	for (unsigned int i = NULL; i < derivatives.size(); i++)
	{
		if ((derivatives[i]->Exponent == NULL)&&(derivatives[i]->Constant != NULL))
		{
			// Delete polynomial at j
			vector<Derivative*>::iterator pos = derivatives.begin();
			pos += i;
			derivatives.erase(pos);
			continue;
		}
		if (derivatives[i]->Constant == NULL)
		{
			// Delete polynomial at j
			vector<Derivative*>::iterator pos = derivatives.begin();
			pos += i;
			derivatives.erase(pos);
			continue;
		}
		if (derivatives[i]->Variable == "")
		{
			// Delete polynomial at j
			vector<Derivative*>::iterator pos = derivatives.begin();
			pos += i;
			derivatives.erase(pos);
			continue;
		}
	}

	// Print resulting vector
	cout << endl << endl << "The derivative of that expression is: ";
	for (unsigned int i = NULL; i < derivatives.size(); i++)
	{
		derivatives[i]->Print();
	}

	// output 0 if nothing is left in the vector
	if (derivatives.empty() == true)
	{
		cout << "0";
	}

	cout << endl << endl;
}
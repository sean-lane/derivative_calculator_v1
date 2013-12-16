// Parse.cpp - Parse function implementation
// By Sean J. Lane

#include <string>
#include <vector>
#include "Derivative.h"
#include "Polynomial.h"
#include "Product.h"
#include "Quotient.h"
#include "Chain.h"

using namespace std;

#define NUMBERS "0123456789"
#define OPERATION1 "+- "
#define OPERATION2 "*/"
#define PARENTHESES "()"
#define VARIABLE "xyz"
#define EXPONENT "^"
#define SPECIAL_FUNCTIONS "scle"
#define CHAIN_VARIABLE "R"
#define SIN 's'
#define COS 'c'
#define EXP 'e'
#define LOG 'l'

float NumberExchange(string& value);

vector<Derivative*> Parse(const string& baseExpression1)
{
	// initialize vector to store expressions
	vector<Derivative*> ExpVector;
	string baseExpression = baseExpression1;

	// append a space onto the end of the base expression to simplify parsing
	baseExpression.append(" ");

	// initialize string and char to catch digits as they are sent out by the for loop, int variables for simple parsing logic
	string constant;
	string variable;
	string exponent;
	string chainRule;
	char operation;
	int checkSpecial = NULL;
	int chainRuleLogic = NULL;
	char currentValue;

	// initialize logic variables to define what different characters are
	string numbers = NUMBERS;
	string operation1 = OPERATION1;
	string operation2 = OPERATION2;
	string parentheses = PARENTHESES;
	string variableSet = VARIABLE;
	string exponentChar = EXPONENT;
	string specialFunctions = SPECIAL_FUNCTIONS;

	// Counter for logic
	int logic = NULL;

	// For loop to iterate through base Derivative; pull out individual Derivatives
	for(string::iterator pos = baseExpression.begin(); pos != baseExpression.end(); pos++)
	{
		// Counter for logic
		logic++;

		// Run normal logic if exponent carot is not the previous char
		if (checkSpecial == NULL)
		{
			// pull value from iterator
			currentValue = *pos;

			// Scan for numbers; if found, append number to a "constant" variable
			if(numbers.find(currentValue) != string::npos) 
			{
				constant.append(1,currentValue);
				continue;
			}
				
			// Scan for variables; if found, append letter to a "variable" variable
			if(variableSet.find(currentValue) != string::npos)
			{
				variable.append(1,currentValue);
				continue;
			}

			// Scan for exponent carot; if found, set exponent logic variable to one
			if(exponentChar.find(currentValue) != string::npos)
			{
				checkSpecial = 1;
				continue;
			}

			// Scan for a parentheses; start chain rule logic if found, 
			if(parentheses.find(currentValue) != string::npos)
			{
				// Scan for index of next parentheses
				int nextParentheses = baseExpression.find(")", logic) - 1;
				chainRule = baseExpression.substr(logic, (nextParentheses - logic + 1));
				pos += (nextParentheses - logic + 2);
				logic += (nextParentheses - logic + 2);
				chainRuleLogic = 1;
				continue;
			}

			// Scan for letters beginning with special functions
			if(specialFunctions.find(currentValue) != string::npos)
			{
				// Scan for the first letter of every function
				if (currentValue == SIN)
				{
					variable = FUNC_SIN;
				}
				else if (currentValue == COS)
				{
					variable = FUNC_COS;
				}
				else if (currentValue == EXP)
				{
					variable = FUNC_EXP;
				}
				else
				{
					variable = FUNC_LOG;
				}

				// move pos past function
				pos += 2;
				logic += 2;
				continue;
			}

			// Scan for a plus or minus sign; signals end of polynomial
			if(operation1.find(currentValue) != string::npos)
			{
				if (chainRuleLogic == NULL)
				{
					// turn input into numbers for initializing subclasses
					float intermediate1, intermediate2;
				
					// Use NumberExchange function to pass strings into a float
					intermediate1 = NumberExchange(constant);
					intermediate2 = NumberExchange(exponent);
				
					// Send input into polynomial subclass (currentValue acts as operator)
					ExpVector.push_back(new Polynomial(intermediate1,variable,intermediate2, currentValue));
					constant = variable = exponent = "";
					operation = ' ';
					continue;
				}
				else
				{
					// turn exponent into a number, initalize actual variables for chain class
					float intermediate1 = NumberExchange(exponent);
					float intermediate2 = NumberExchange(constant);
					string chain = CHAIN_VARIABLE;

					// define parenthetical function as a normal chain rule if no variables are present
					if (variable.empty() == true)
					{
						// chain = r;
						variable = chain;
					}

					// Send input into Chain subclass (currentValue acts as operator)
					ExpVector.push_back(new Chain(chainRule, intermediate2, variable, intermediate1, currentValue));
					constant = variable = exponent = "";
					operation = ' ';
					chainRuleLogic = NULL;
					continue;
				}
			}

			// if a multiplcation or division sign is found
			if(operation2.find(currentValue) != string::npos)
			{
				// if input has a variable but does not start with the letter of any of the special functions, 
				// it must be a Polynomial
				if ((variable.empty() != true)&&(variable.find(SPECIAL_FUNCTIONS) == string::npos))
				{
					// Use NumberExchange to turn strings into float
					float intermediate1 = NumberExchange(constant);
					float intermediate2 = NumberExchange(exponent);

					// Define one intermediate polynomial with current data
					ExpVector.push_back(new Polynomial(intermediate1,variable,intermediate2,currentValue));
					constant = variable = exponent = "";
					operation = ' ';
					continue;
				}
			}
		}

		// Run special exponent logic if exponent char is found
		else if (checkSpecial == 1)
		{
			// continue scanning through string
			currentValue = *pos;

			// look for +, -, *, /, or space; if found, stop putting numbers in exponent, roll back pos by one, 
			// and let the normal function logic continue parsing
			if((operation1.find(currentValue) == string::npos)&&(operation2.find(currentValue) == string::npos))
			{
				exponent.append(1,currentValue);
				continue;
			}
			else
			{
				checkSpecial = NULL;
				pos--;
				logic--;
			}
		}
	}

	// Simplification process for Product rule
	for (unsigned int i = NULL; i < ExpVector.size(); i++)
	{
		if (ExpVector[i]->Operation == '*')
		{
			float constant, exponent;

			// Push from vector into intermediate polynomials
			constant = ExpVector[i]->Constant;
			exponent = ExpVector[i]->Exponent;
			variable = ExpVector[i]->Variable;
			operation = ExpVector[i]->Operation;

			Polynomial intermediate1(constant,variable,exponent,operation);

			constant = ExpVector[i+1]->Constant;
			exponent = ExpVector[i+1]->Exponent;
			variable = ExpVector[i+1]->Variable;
			operation = ExpVector[i+1]->Operation;

			Polynomial intermediate2(constant,variable,exponent,operation);

			// Push new Product object into the vector in place of polynomial at i
			ExpVector[i] = (new Product(intermediate1, intermediate2));

			// Delete polynomial at i+1
			vector<Derivative*>::iterator pos = ExpVector.begin();
			pos += (i+1);
			ExpVector.erase(pos);
		}
	}

	// Simplification process for Quotient rule
	for (unsigned int i = NULL; i < ExpVector.size(); i++)
	{
		if (ExpVector[i]->Operation == '/')
		{
			float constant, exponent;

			// Push from vector into intermediate polynomials
			constant = ExpVector[i]->Constant;
			exponent = ExpVector[i]->Exponent;
			variable = ExpVector[i]->Variable;
			operation = ExpVector[i]->Operation;

			Polynomial intermediate1(constant,variable,exponent,operation);

			constant = ExpVector[i+1]->Constant;
			exponent = ExpVector[i+1]->Exponent;
			variable = ExpVector[i+1]->Variable;
			operation = ExpVector[i+1]->Operation;

			Polynomial intermediate2(constant,variable,exponent,operation);

			// Push new Product object into the vector in place of polynomial at i
			ExpVector[i] = (new Quotient(intermediate1, intermediate2));

			// Delete polynomial at i+1
			vector<Derivative*>::iterator pos = ExpVector.begin();
			pos += (i+1);
			ExpVector.erase(pos);
		}
	}

	// Return final vector
	return ExpVector;
}
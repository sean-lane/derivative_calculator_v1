// NumberExchange.cpp - string to float exchange function (and error prevention)
// By Sean J. Lane

#include <string>

using namespace std;

// Simple string value to float function for constant and exponent fields
float NumberExchange(string& value)
{
	float intermediate1;
	// Use stof() function to turn string into float
	// Do not use stof() function if no numbers are in the string
	if (value.empty() != true)
	{
		intermediate1 = stof(value);
		return intermediate1;
	}
	// if constant is empty, append a 1 to handle empty data fields
	else
	{
		value.append("1");
		intermediate1 = stof(value);
		return intermediate1;
	}
}
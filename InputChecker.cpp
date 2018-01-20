#include "InputChecker.h"
#include<cctype>
#include<iostream>
#define EXIT -99

bool InputChecker::inputMatches(string strUserInput, string strTemplate)
{
	if (strTemplate.length() != strUserInput.length())
		return false;

	// Step through the user input to see if it matches
	for (unsigned int nIndex = 0; nIndex < strTemplate.length(); nIndex++)
	{
		switch (strTemplate[nIndex])
		{
		case '#': // match a digit
			if (!isdigit(strUserInput[nIndex]))
				return false;
			break;
		case '_': // match a whitespace
			if (!isspace(strUserInput[nIndex]))
				return false;
			break;
		case '@': // match a letter
			if (!isalpha(strUserInput[nIndex]))
				return false;
			break;
		case '?': // match anything
			break;
		default: // match the exact character
			if (strUserInput[nIndex] != strTemplate[nIndex])
				return false;
		}
	}

	return true;
}

bool InputChecker::inputExiting(int number1,int number2,int data)
{
	if (data != number1 && data != number2) {
		std::cout << "Nepostojeca opcija, pokusajte ponovo." << std::endl;
		return false;
	}
	return true;
}

bool InputChecker::inputPin(string pin) const
{
	return (pin.size()!=4);
}

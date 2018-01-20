#pragma once
#include<string>
using std::string;

class InputChecker
{
public:
	InputChecker()=default;
	bool inputMatches(string strUserInput, string strTemplate);
	bool inputExiting(int number1,int number2,int data);
	bool inputPin(string pin) const;
};


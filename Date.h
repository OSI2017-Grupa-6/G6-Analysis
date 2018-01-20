#pragma once
#include<string>
class Date
{
	int day, month, year;
	
public:
	Date();
	Date(int, int, int);
	bool check_date();
	std::string correct_date(std::string);
	operator std::string();
	Date string_to_date(std::string);
	~Date();
};

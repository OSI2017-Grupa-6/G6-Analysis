#pragma once
#include<string>
class Date
{
	int day, month, year;
	
public:
	Date(int, int, int);
	bool check_date();
	operator std::string() const;
	Date string_to_date(std::string);
	~Date();
};

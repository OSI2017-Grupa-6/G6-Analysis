#pragma once

class Date
{
	int day, month, year;
	
public:
	Date(int, int, int);
	bool check_date();
	operator string() const;
	Date string_to_date(string);
	~Date();
};

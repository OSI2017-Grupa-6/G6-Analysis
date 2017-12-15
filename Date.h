#pragma once

class Date
{
	int day, month, year;
	
public:
	Date(int, int, int);
	int get_day() { return day; }
	int get_month() { return month; }
	int get_year() { return year; }
	bool check_date(int, int, int);
	operator string() const;
	Date string_to_date(string);
	~Date();
};
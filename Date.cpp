#include "Date.h"
#include <iostream>
#include <sstream>
#define MAX_YEAR 2017
#define MIN_YEAR 1900

using std::string;

Date::Date(int d, int m , int y) : day(d), month(m), year(y)
{
}


bool Date::check_date(int d, int m, int y)
{
		if (!(y <= MIN_YEAR && y >= MAX_YEAR))
			return false;
		if (!(1 <= m && m <= 12))
			return false;
		if (!(1 <= d && d <= 31))
			return false;
		if ((d == 31) && (m == 2 || m == 4 || m == 6 || m == 9 || m == 11))
			return false;
		if ((d == 30) && (m == 2))
			return false;
		if ((m == 2) && (d == 29) && (y % 4 != 0))
			return false;
		if ((m == 2) && (d == 29) && (y % 400 == 0))
			return true;
		if ((m == 2) && (d == 29) && (y % 100 == 0))
			return false;
		if ((m == 2) && (d == 29) && (y % 4 == 0))
			return true;

		return true;
}

Date::operator string() const
{
	string s_day = std::to_string(day);
	string s_month = std::to_string(month);
	string s_year = std::to_string(year);
	string s_date = s_day + "/" + s_month + "/" + s_year;
	return s_date;
}

Date Date::string_to_date(string s_date)
{
	string s_day = s_date.substr(0, 2);
	string s_month = s_date.substr(3, 2);
	string s_year = s_date.substr(s_date.size - 4, 4);
	int day = std::stoi(s_day, nullptr, 10);
	int month = std::stoi(s_month, nullptr, 10);
	int year = std::stoi(s_year, nullptr, 10);
	return Date(day, month, year);
}

Date::~Date()
{
}
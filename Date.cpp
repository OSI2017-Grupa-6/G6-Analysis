#include "Date.h"
#include <iostream>
#include <sstream>
#define MAX_YEAR 2019
#define MIN_YEAR 1970


Date::Date() : day(1), month(1), year(1970)
{
}

Date::Date(int d, int m , int y) : day(d), month(m), year(y)
{
}


bool Date::check_date()
{
		if (year < MIN_YEAR || year > MAX_YEAR)
			return false;
		if (month < 1 || month > 12)
			return false;
		if (day < 1 || day > 31)
			return false;
		if ((day == 31) && (month == 2 || month == 4 || month == 6 || month == 9 || month == 11))
			return false;
		if ((day == 30) && (month == 2))
			return false;
		if ((month == 2) && (day == 29) && !(year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)))
			return false;
		return true;
}

Date::operator std::string()
{
	std::string s_day = std::to_string(day);
	std::string s_month = std::to_string(month);
	std::string s_year = std::to_string(year);
	std::string s_date = s_day + "-" + s_month + "-" + s_year;
	if( s_date.size() < 10 )
		s_date=correct_date(s_date);
	return s_date;
}

std::string Date::correct_date(std::string s_date)
{
	std::string s_day;
	std::string s_month;
	std::string s_year;
	int first=0, last;
	last = s_date.find(".");
	if (last > s_date.size()) last = s_date.find("/");
	if (last > s_date.size()) last = s_date.find("-");
	s_day=s_date.substr(first, last-first);
	if (s_day.size() == 1) 
		s_day="0"+s_day;
	first = last + 1;
	last = s_date.find_last_of(".");
	if (last > s_date.size()) last = s_date.find_last_of("/");
	if (last > s_date.size()) last = s_date.find_last_of("-");
	s_month = s_date.substr(first, last-first);
	if (s_month.size() == 1)
		s_month = "0" + s_month;
	first = last + 1;
	s_year = s_date.substr(first, s_date.size());
	if (s_year.size() == 2)
		s_year = "19" + s_year;
	std::string date;
	date = s_day + "-" + s_month + "-" + s_year;
	return date;
}

Date Date::string_to_date(std::string s_date)
{
	if (s_date.size() < 10)
		s_date=correct_date(s_date);
	std::string s_day = s_date.substr(0, 2);
	std::string s_month = s_date.substr(3, 2);
	std::string s_year = s_date.substr(s_date.size() - 4, 4);
	int day = std::stoi(s_day, nullptr, 10);
	int month = std::stoi(s_month, nullptr, 10);
	int year = std::stoi(s_year, nullptr, 10);
	return Date(day, month, year);
}

Date::~Date()
{
}

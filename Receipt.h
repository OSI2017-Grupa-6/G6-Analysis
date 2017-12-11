#pragma once
#include<string>
#include<iostream>
#include<fstream>
class Receipt
{
public:
	Receipt(std::string, std::string, double, double, double, double);
	Receipt format(const char*);///not finished
	Receipt(const Receipt&) = default;
	Receipt& operator=(const Receipt&) = default;
private:
	std::string buyers_name;
	//Date date;
	std::string product_key;
	double product_sold;
	double product_price;
	double total_price;
	double pdv;
public:
	static Receipt null_receipt;
};


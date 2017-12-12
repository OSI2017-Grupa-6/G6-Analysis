#pragma once
#include<string>
#include<iostream>
#include<fstream>
#include<vector>
class Receipt
{
public:
	Receipt(std::string, double, double);
	Receipt(std::string, std::string, std::vector<std::string>, std::vector<double>, std::vector<double>, double, double);
	Receipt format(const char*);///not finished
	Receipt(const Receipt&) = default;
	Receipt& operator=(const Receipt&) = default;
private:
	std::string buyers_name;
	std::string receipts_name;
	//Date date;
	std::vector<std::string> product_key;
	std::vector<double> product_sold;
	std::vector<double> product_price;
	double total_price;
	double pdv;
public:
	static Receipt null_receipt;
};



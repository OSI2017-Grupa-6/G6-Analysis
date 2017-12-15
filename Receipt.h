#pragma once
#include<string>
#include<iostream>
#include<fstream>
#include<vector>
class Receipt
{
public:
	Receipt(std::string, double, double);
	Receipt(std::string, std::string, std::vector<std::string>, std::vector<double>, std::vector<double>,
		std::vector<double>, double, double, double);

	Receipt(const Receipt&) = default;
	Receipt(Receipt&&) = default;
	Receipt& operator=(const Receipt&) = default;

	friend Receipt format(const char*);
	bool validate();
	std::string getReceiptName();
private:
	std::string buyers_name;
	std::string receipts_name;
	//Date date;
	std::vector<std::string> product_key;
	std::vector<double> product_sold;
	std::vector<double> product_price;
	std::vector<double> product_total;
	double total_price;
	double pdv;
	double payment;
public:
	static Receipt null_receipt;
};



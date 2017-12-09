#pragma once
#include<string>
class Receipt
{
public:
	Receipt(std::string,std::string,std::string,double,double,double,double);
private:
	std::string receipt_name;
	std::string buyers_name;
	//Date date;
	std::string product_key;
	double product_sold; 
	double product_price;
	double total_price;
	double pdv;
};


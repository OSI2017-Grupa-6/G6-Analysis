#include "Receipt.h"



Receipt::Receipt(std::string name, std::string key, double sold, double price, double total, double pdv) :pdv(pdv)
{
	//Date
	buyers_name = name;
	product_key = key;
	product_sold = sold;
	product_price = price;
	total_price = total;
}

Receipt format(const char* file)  //not finished
{

	std::string file_name = "dadasf", buyers_name;
	double sold, price, pdv;
	//Date date;
	Receipt r(file_name, file_name, 0.0, 0.0, 0.0, 0.0);
	return r;
}
Receipt Receipt::null_receipt("", "", 0.0, 0.0, 0.0, 0.0);
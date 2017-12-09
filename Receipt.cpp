#include "Receipt.h"

using std::string;

Receipt::Receipt(string receipt,string name, string key, double sold, double price, double total, double pdv):pdv(pdv)
{
	//Date
	receipt_name=receipt;
	buyers_name=name;
	product_key=key;
	product_sold=sold;
	product_price=price;
	total_price=total;
}


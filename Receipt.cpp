#include "Receipt.h"



Receipt::Receipt(std::string name, std::string key, double sold, double price, double total, double pdv):pdv(pdv)
{
	//Date
	buyers_name=name;
	product_key=key;
	product_sold=sold;
	product_price=price;
	total_price=total;
}


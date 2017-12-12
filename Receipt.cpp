#include "Receipt.h"
using std::string;
using std::vector;


Receipt::Receipt(std::string name, double total, double pdv) :pdv(pdv)
{
	//Date
	buyers_name = name;

	total_price = total;
}
Receipt::Receipt(string name, string buyer, vector<string> products, vector<double> prices,
	vector<double> amount, double total, double pdv) :Receipt(buyer, total, pdv)
{
	receipts_name = name;
	product_key = products;
	product_price = prices;
	product_sold = amount;
}
Receipt Receipt::format(const char* file)  //not finished
{

	std::string file_name = file, buyers_name;
	double sold, price, pdv;
	//Date date;
	char temp;
	std::string skip, take, name;
	std::ifstream myFile;
	myFile.open(file);
	//need to check if file is empty
	myFile >> skip;
	if (skip != "Kupac:")
		return Receipt::null_receipt;
	myFile >> name;
	myFile.get(temp);
	if (temp != '\n')
		return Receipt::null_receipt;
	myFile >> skip;
	if (skip != "Datum:")
		return Receipt::null_receipt;
	myFile.get(temp);
	myFile >> skip;//Date
				   //check Date
	myFile.get(temp);
	if (temp != '\n')
		return Receipt::null_receipt;
	myFile.get(temp);
	if (temp != '\n')
		return Receipt::null_receipt;
	char c[100];
	myFile.getline(c, 30);
	if (strcmp(c, "\t       Racun") != 0)
		return Receipt::null_receipt;
	myFile.get(temp);
	if (temp != '\n')
		return Receipt::null_receipt;
	myFile.getline(c, 80);
	if (strcmp(c, "Proizvod - kolicina - cijena - ukupno") != 0)
		return Receipt::null_receipt;

	Receipt r(file_name, 0.0, 0.0);
	return r;
}

Receipt Receipt::null_receipt("", 0.0, 0.0);
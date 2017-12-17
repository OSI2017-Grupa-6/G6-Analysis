#include "Receipt.h"
using std::string;
using std::vector;
#include<algorithm>
#define MIN 0
#define MAX 1000000
#define PDV 0.17

Receipt::Receipt(std::string name, double total, double pdv):pdv(pdv),date(1,1,1970)
{
	buyers_name=name;

	total_price=total;
}
Receipt::Receipt(string name,string buyer, vector<string> products, vector<double> prices, 
	vector<double> amount,vector<double> total_product,double total,double pdv,double pay,Date d):Receipt(buyer,total,pdv)
{
	receipts_name = name;
	product_key = products;
	product_price = prices;
	product_sold = amount;
	product_total = total_product;
	payment = pay;
	date = d;
}
bool Receipt::validate()
{
	double sum=0.0;
	for (int i = 0; i < product_key.size(); ++i) {
		sum += product_total[i];
		if (product_price[i] * product_sold[i] != product_total[i])
			return false;
	}
	if (sum != total_price)
		return false;
	if (sum*PDV != pdv)
		return false;
	if (total_price + pdv != payment)
		return false;
	return true;
}

std::string Receipt::getReceiptName() const 
{
	return receipts_name;
}

void Receipt::erase(int i)
{
	product_key.erase(product_key.begin() + i);
	product_sold.erase(product_sold.begin() + i);
	product_price.erase(product_price.begin() + i);
	product_total.erase(product_total.begin() + i);
}

void Receipt::erase_buyer()
{
	buyers_name = "";
}

Receipt format1(const char* file)  //not finished
{
	string _file = file;
	std::string file_name = _file.substr(7, _file.size()) , buyers_name;
	vector<string> products;
	vector<double>  prices, amount, total_product;
	double total, pdv, pay;
	double tmp;
	Date d(1,1,1970);
//helper:
	char temp;
	std::string skip, take;

	std::ifstream myFile;
	myFile.open(file);
	//need to check if file is empty
	myFile >> skip;
	if (skip != "Kupac:")
		return Receipt::null_receipt;
	myFile.get(temp);
	if (temp != ' ')
		return Receipt::null_receipt;
	myFile >> buyers_name; //1.saving name
	myFile.get(temp);
	if (temp != '\n')
		return Receipt::null_receipt;
	myFile >> skip;
	if (skip != "Datum:")
		return Receipt::null_receipt;
	myFile.get(temp);
	if (temp != ' ')
		return Receipt::null_receipt;

	myFile >> skip;
	d=d.string_to_date(skip);
	if(!d.check_date())
		return Receipt::null_receipt;
	 //2.saving date
	myFile.get(temp);
	if (temp != '\n')
		return Receipt::null_receipt;
	myFile.get(temp);
	if (temp != '\n')
		return Receipt::null_receipt;
	char c[256];
	myFile.getline(c, 30);
	if (strcmp(c, "\t       Racun") != 0)
		return Receipt::null_receipt;
	myFile.get(temp);
	if (temp != '\n')
		myFile.get(temp);
	if (temp != '\n')
		return Receipt::null_receipt;
	myFile.getline(c, 80);
	if (strcmp(c, "Proizvod - kolicina - cijena - ukupno") != 0)
		return Receipt::null_receipt;
	char end;
	short begin_line, end_line;
	do{
		begin_line = myFile.tellg();
		myFile >> take;
		myFile.get(temp);
		if (temp != ' ')
		return Receipt::null_receipt;
		myFile >> skip;
		take += skip;
		products.push_back(take); //3.products name

		myFile >> temp;           //4.products amount
		if (temp != '-')
			return Receipt::null_receipt;
		myFile >> tmp;
		if (tmp<MIN || tmp>MAX)
			return Receipt::null_receipt;
		amount.push_back(tmp);

		myFile >> temp;         //5.products price
		if (temp != '-')
			return Receipt::null_receipt;
		myFile >> tmp;
		if (tmp<MIN || tmp>MAX)
			return Receipt::null_receipt;
		prices.push_back(tmp);

		myFile >> temp;         //5.products total
		if (temp != '-')
			return Receipt::null_receipt;
		myFile >> tmp;
		if (tmp<MIN || tmp>MAX)
			return Receipt::null_receipt;
		total_product.push_back(tmp);
		
		end_line=myFile.tellg();
		myFile.get(temp);
		if (temp != '\n')
			return Receipt::null_receipt;
		end = myFile.peek();
	} while (end>='0' && end<='9' || end>='a' && end<='z' || end>='A' && end<='Z');
	short length = end_line - begin_line;
	myFile.getline(c,200);
	string line="";
	for (int i = 0; i <39; i++)
		line+= "-";
	if (strcmp(line.c_str(), c) != 0)
		return Receipt::null_receipt;

	myFile >> skip;
	if(skip!="Ukupno:")
		return Receipt::null_receipt;
	myFile.get(temp);
	if (temp != ' ')
		return Receipt::null_receipt;
	myFile >> total;
	myFile.get(temp);
	if (temp != '\n')
		return Receipt::null_receipt;

	myFile >> skip;
	if (skip != "PDV:")
		return Receipt::null_receipt;
	myFile.get(temp);
	if (temp != ' ')
		return Receipt::null_receipt;
	myFile >> pdv;
	myFile.get(temp);
	if (temp != '\n')
		return Receipt::null_receipt;


	myFile.get(c, 20);
	if (strcmp("Ukupno za placanje:", c)!=0)
		return Receipt::null_receipt;
	myFile.get(temp);
	if (temp != ' ')
		return Receipt::null_receipt;
	myFile >> pay;

	Receipt r(file_name,buyers_name,products,prices,amount,total_product,total,pdv,pay,d);
	return r;
}
Receipt Receipt::null_receipt("", 0.0, 0.0);
int Receipt::format(const char *name)
{
	std::ifstream file;
	file.open(name);
	std::string tmp;
	file >> tmp;
	if (tmp.compare("Kupac:") == 0)
	{
		file.seekg(-1, file.end);
		file >> tmp;
		if (tmp.compare("=") == 0)
		{
			file.close();
			return 4;
		}
		file.close();
		return 1;
	}
	if (tmp.substr(0, 5) == "Sifra")
	{
		file.close();
		return 5;
	}

	std::string p;
	std::getline(file, p);
	file >> tmp;
	if (tmp.compare("Poslovnica:") == 0)
	{
		std::getline(file, p);
		file >> tmp;
		if (tmp.compare("Kupac:") == 0)
		{
			file.close();
			return 3;
		}
		file.close();
		return 2;
	}
	file.close();
	return 0;

}

void Receipt::load_format1(const char *name)
{
	std::ifstream file;
	file.open(name);
	std::string tmp, tmp2;
	string _file(name);
		receipts_name = _file.substr(7, _file.size());
	
	double x;
	file >> tmp >> buyers_name;
	file >> tmp >> tmp;
	date=date.string_to_date(tmp);
	file >> tmp;
	file.ignore(40);
	while (true)
	{
		file >> tmp >> tmp2;
		if (tmp.compare("---------------------------------------") == 0)
			break;
		product_key.push_back(tmp + " " + tmp2);
		file >> tmp >> x;
		product_sold.push_back(x);
		file >> tmp >> x;
		product_price.push_back(x);
		file >> tmp >> x;
		product_total.push_back(x);
	}
	file >> total_price;
	file >> tmp >> pdv;
	file >> tmp >> tmp >> tmp >> payment;
	file.close();
}

void Receipt::load_format2(const char *name)
{
	std::ifstream file;
	file.open(name);
	std::string tmp, tmp2;
	double x;
	string _file(name);
	receipts_name = _file.substr(7, _file.size());
	do { file >> tmp; } while (tmp.compare("Kupac:") != 0);
	file >> buyers_name;
	file.ignore(80);
	while (true)
	{
		file >> tmp >> tmp2;
		if (tmp.compare("---------------------------------------") == 0)
			break;
		product_key.push_back(tmp + " " + tmp2);
		file >> tmp >> x;
		product_sold.push_back(x);
		file >> tmp >> x;
		product_price.push_back(x);
		file >> tmp >> x;
		product_total.push_back(x);
	}
	file >> total_price;
	file >> tmp >> pdv >> tmp >> tmp >> tmp >> payment >> tmp >> tmp;
	date=date.string_to_date(tmp);
	file.close();
}

void Receipt::load_format3(const char *name)
{
	std::ifstream file;
	file.open(name);
	std::string tmp, tmp2;
	double x;
	
	string _file(name);
	receipts_name = _file.substr(7, _file.size());
	do { file >> tmp; } while (tmp.compare("Kupac:") != 0);
	file >> buyers_name;
	file >> tmp >> tmp;
	date=date.string_to_date(tmp);
	while (tmp.compare("----------------------------------") != 0)
		file >> tmp;
	while (true)
	{
		file >> tmp >> tmp2;
		if (tmp.compare("----------------------------------") == 0)
			break;
		product_key.push_back(tmp + " " + tmp2.substr(0, tmp2.find_first_of("=")));
		tmp2.erase(0, tmp2.find_first_of("="));
		tmp2.erase(0, tmp2.find_first_not_of("="));
		x = (double)atof(tmp2.c_str());
		product_sold.push_back(x);
		tmp2.erase(0, tmp2.find_first_of("="));
		tmp2.erase(0, tmp2.find_first_not_of("="));
		x = (double)atof(tmp2.c_str());
		product_price.push_back(x);
		tmp2.erase(0, tmp2.find_first_of("="));
		tmp2.erase(0, tmp2.find_first_not_of("="));
		x = (double)atof(tmp2.c_str());
		product_total.push_back(x);
	}
	file >> total_price >> tmp >> pdv >> tmp >> tmp >> tmp >> payment;

	file.close();

}

void Receipt::load_format4(const char *name)
{
	std::ifstream file;
	file.open(name);
	std::string tmp, tmp2;
	double x;
	string _file(name);
	receipts_name = _file.substr(7, _file.size());
	file >> tmp >> buyers_name >> tmp >> tmp;
	date=date.string_to_date(tmp);
	while (tmp.compare("---------------------------------------") != 0)
		file >> tmp;
	while (true)
	{
		file >> tmp >> tmp2;
		if (tmp.compare("---------------------------------------") == 0)
			break;
		product_key.push_back(tmp + " " + tmp2);
		file >> tmp >> x;
		product_sold.push_back(x);
		file >> tmp >> x;
		product_price.push_back(x);
		file >> tmp >> x;
		product_total.push_back(x);
	}
	file >> total_price >> tmp >> pdv >> tmp >> tmp >> tmp >> tmp >> payment;
	file.close();
}

void Receipt::load_format5(const char *name)
{
	std::ifstream file;
	file.open(name);
	std::string tmp;
	double x;
	string _file(name);
	receipts_name = _file.substr(7, _file.size());
	buyers_name = "";
	file.ignore(28);
	file >> tmp;
	do {
		product_key.push_back(tmp.substr(0, tmp.find_first_of(",")));
		tmp.erase(0, tmp.find_first_of(",") + 1);
		x = (double)atof(tmp.c_str());
		product_sold.push_back(x);
		tmp.erase(0, tmp.find_first_of(",") + 1);
		x = (double)atof(tmp.c_str());
		product_price.push_back(x);
		tmp.erase(0, tmp.find_first_of(",") + 1);
		x = (double)atof(tmp.c_str());
		product_total.push_back(x);
		file >> tmp;
	} while (tmp.length()>2);
	total_price = pdv = payment = 0;
	file.close();
}
void Receipt::format_checker(const char *name)
{

	switch (format(name))
	{
	case 1: load_format1(name); break;
	case 2: load_format2(name); break;
	case 3: load_format3(name); break;
	case 4: load_format4(name); break;
	case 5: load_format5(name); break;
	default:
		break;
	}

}

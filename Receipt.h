#pragma once
#include<string>
#include<iostream>
#include<fstream>
#include<vector>
#include"Date.h"

class Receipt
{
public:
	Receipt(std::string,  double, double);
	Receipt(std::string, std::string, std::vector<std::string>,std::vector<double>,std::vector<double>, 
		std::vector<double>,double,double, double,Date);

	Receipt(const Receipt&) = default;
	Receipt(Receipt&&) = default;
	Receipt& operator=(const Receipt&) = default;
	
	bool validate();

	std::string getReceiptName() const ;
	inline std::vector<std::string> getProductKey()const  { return product_key; };
	inline std::vector<double> getProductSold() const  { return product_sold; }
	inline std::vector<double> getProductPrice() const { return product_price; }
	inline std::vector<double> getProductTotal() const { return product_total; }
	inline double getTotalPrice() const { return total_price; }
	inline double getPdv() const { return pdv; }
	inline double getPayment() const { return payment; };
	inline std::string getBuyer() const { return buyers_name; }
	inline int getSize() const { return product_sold.size(); }
	inline Date getDate() const { return date; }
	void erase(int);
	void erase_buyer();
	void format_checker(const char*);

private:
	std::string buyers_name;
	std::string receipts_name;
	Date date;
	std::vector<std::string> product_key;
	std::vector<double> product_sold;
	std::vector<double> product_price;
	std::vector<double> product_total;
 	double total_price;
	double pdv;
	double payment;


	int format(const char *name);
	void load_format1(const char *name);
	void load_format2(const char *name);
	void load_format3(const char *name);
	void load_format4(const char *name);
	void load_format5(const char *name);
public:
	static Receipt null_receipt;
};



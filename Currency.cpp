#include "Currency.h"
#include <iostream>
#include <fstream>
#include <string>


void set_currency()
{
	bool flag = false;
	std::string currency;
	do {
		std::cout << "Izaberite valutu sistema!\n\nMoguce opcije su:\n\tKM (konvertibilna marka)\n\t€ (euro)" << std::endl;
		std::cin >> currency;
		if ((currency.compare("KM") == 0 || currency.compare("€") == 0))
			flag = true;
	} while (!flag);
	std::ofstream file;
	file.open("Valuta.txt");
	if (file)
		file << currency;
	file.close();
}

void check_currency()
{
	int length = 0;
	std::ifstream file("Valuta.txt", std::ifstream::binary);
	if (file)
	{
		file.seekg(0, file.end);
		length = file.tellg();
		file.close();
	}
	if (length == 0)
		set_currency();

}

std::string get_currency()
{
	std::string currency="";
	std::ifstream file("Valuta.txt");
	if (file)
		file >> currency;
	file.close();
	return currency;
}

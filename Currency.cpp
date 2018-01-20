#include <iostream>
#include <fstream>
#include <string>
#include "Currency.h"

void set_currency()
{
	bool flag = false;
	std::string currency;
	do {
		std::cout << "Izaberite valutu sistema!\nMoguce opcije su:\n\tKM (konvertibilna marka)\n\tE (euro)\n\t$ (americki dolar)" << std::endl;
		std::cin >> currency;
		if ((currency.compare("KM") == 0 || currency.compare("E") == 0) || currency.compare("$") == 0)
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
	if (length == 0) {
		std::cout << "\nNakon sto uspjesno podesite valutu, molimo Vas da napustite sistem kako bi se izmjene sacuvale.\n";
		set_currency();
		std::cout << "\nUspjesno ste podesili valutu.Odjavite se i napustite sistem." << std::endl;
	}
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

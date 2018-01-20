#include "Analyst.h"
#include"InputChecker.h"
#include "Windows.h"
#include<iostream>

#include "Load.h"
#define MAX_LENGTH_OF_NAME 30
using std::string;

Analyst::Analyst(string name,string lastName,string pin,int usergroup,string username):
	UsersGroup(name, lastName, pin, usergroup, username) {}
int Analyst::options()
{
	int option;
	do {
		do {
			std::cout << "\nUnesite (0) da se odjavite sa sistema!" << std::endl;
			std::cout << "\nOpcija 1: Pregled za proizvod\nOpcija 2: Pregled za kupca\nOpcija 3: Pregled za mjesec" << std::endl;
			option = input_int(std::cin);
			std::cout << std::endl;
		} while (option != 0 && option != 1 && option != 2 && option != 3);
		switch (option)
		{
		case 1: look_for_product(); break;
		case 2: look_for_buyer(); break;
		case 3: look_for_month(); break;
		default:	std::cout << "Nepostojeca opcija, pokusajte ponovo." << std::endl; break;
		}
	} while (option == 1 || option == 2 || option == 3);
	return LOGOUT;
}
bool Analyst::look_for_buyer()
{
	string buyer;
	std::cout << "Ime kupca:";
	std::getline(std::cin, buyer);
	std::cout << buyer;
	 return searching_for("Pregled za kupca",buyer);
}

bool Analyst::look_for_product()
{
	string product;
	std::cout << "Ime proizvoda:";
	std::getline(std::cin,product);
	std::cout << std::endl;
	return searching_for("Pregled za proizvod",product);
}
bool Analyst::look_for_month()
{
	InputChecker check;
	string month;
	do {
		std::cout << "Unesite brojne vrijednost mjeseca i godine u formatu mm-yyyy\n";
		std::getline(std::cin, month);
	} while (!check.inputMatches(month, "##-####"));
	return searching_for("Pregled za mjesec", month);
}


bool Analyst::searching_for(const char * file, std::string name)
{
	string folder(file);
	string search_path = folder + "/*.*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
		} while (fd.cFileName != (name + ".txt") && ::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	if (fd.cFileName != (name + ".txt")) {
		std::cout << "Nije pronadjen!" << std::endl;
		return false;
	}
	std::ifstream f;
	search_path = file;
	folder = fd.cFileName;
	search_path += "\\" + folder;
	f.open(search_path);
	std::cout << f.rdbuf();
	f.close();
	return true;
}

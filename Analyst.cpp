#include "Analyst.h"
#include "Windows.h"
#include<iostream>
#define MAX_LENGTH_OF_NAME 30
using std::string;

Analyst::Analyst(string name,string lastName,string pin,int usergroup,string username):
	UsersGroup(name, lastName, pin, usergroup, username) {}

bool Analyst::look_for_buyer()
{
	string buyer;
	std::cout << "Ime kupca:";
	std::cin.ignore();
	std::getline(std::cin, buyer);
	
	string folder = "Pregled za kupca";
	string search_path =folder + "/*.*";
	 WIN32_FIND_DATA fd;
	 HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	 if (hFind != INVALID_HANDLE_VALUE) {
		 do {
		 } while (fd.cFileName != (buyer+".txt") && ::FindNextFile(hFind, &fd)  );
		 ::FindClose(hFind);
	 }
	 if (fd.cFileName != (buyer+".txt")) {
		 std::cout << "Nije pronadjen!"<<std::endl;
		 return false;
	 }
	 std::ifstream f;
	 folder = fd.cFileName;
	 f.open("Pregled za kupca\\"+ folder);
	 std::cout << f.rdbuf();
	 f.close();
	 return true;
}

bool Analyst::look_for_product()
{
	string product;
	char product_name[MAX_LENGTH_OF_NAME+1];
	std::cout << "Ime proizvoda:";
	std::cin.ignore();
	std::getline(std::cin,product);
	std::cout << std::endl;
	string folder = "Pregled za proizvod";
	string search_path = folder + "/*.*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
		} while (fd.cFileName != (product+ ".txt") && ::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	if (fd.cFileName != (product + ".txt")) {
		std::cout << "Nije pronadjen!"<<std::endl;
		return false;
	}
	std::ifstream f;
	folder = fd.cFileName;
	f.open("Pregled za proizvod\\" + folder);
	std::cout << f.rdbuf();
	f.close();
	return true;
}

int Analyst::options()
{
	int option;
	do {
		std::cout << "\nOpcija (1): Pregled za proizvod\nOpcija (2): Pregled za kupca" << std::endl;
		std::cin >> option;
		std::cout<<std::endl;
		if (option == 1)
			look_for_product();
		else if (option == 2)
			look_for_buyer();
	} while ( option==1 || option==2);
	return LOGOUT;
}

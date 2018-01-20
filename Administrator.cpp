#include "Administrator.h"
#include"Currency.h"

#include<experimental/filesystem>
#include<fstream>

using std::string;
using std::cout;
using std::cin;
using std::endl;

#define ACCOUNT_SIZE 5

Administrator::Administrator(string name, string lastName, string pin, int usergroup, string username) :
	UsersGroup(name, lastName, pin, usergroup, username)
{}
int Administrator::options()
{
	check_currency();
	int answer;
	do {
		do {
			std::cout << "\nOpcija (0): odjava sa sistema" << std::endl;
			std::cout << "\nOpcija (1): Dodaj nalog\nOpcija (2): Pregled liste korisnika\nOpcija (3): Brisanje naloga" << std::endl;
			std::cout << "Opcija (4): Azuriranje naloga\n";
			std::cin >> answer;
		} while (answer != 0 && answer != 1 && answer != 2 && answer != 3 && answer != 4);

		switch (answer)
		{
		case(1): addAccount(); break;
		case(2):getListOfUsers() ? std::cout << "" : std::cout << "Postojeca lista korisnika je prazna."; break;
		case(3):deleteAccount() ? std::cout << "\nUspjesno ste obrisali nalog." : std::cout << "\nNeuspjesno brisanje.\n"; break;
		case(4):updateAccount()? std::cout << "" :std::cout << "\nUspjesno ste azurirali nalog.\n"; break;
		}
	} while (answer == 1 || answer == 2 || answer == 3 || answer == 4);
	return LOGOUT;
}

//public functions
bool Administrator::addAccount()
{
	std::vector<string> vec;
	string check;
	adding_info("Korisnici.txt",vec, check);
	std::ofstream dat("Korisnici.txt", std::ios::app);
	dat << '\n';
	dat << check << endl;
	dat.close();

	return true;
}

bool Administrator::deleteAccount()
{
		std::vector<string> vec;
		string temp;
		vec.push_back("");
		vec.push_back("");
		std::cout << "Informacije o korisniku ciji nalog zelite da obrisete:" << std::endl;
		std::cout << "Korisnicko ime:" << std::endl;
		std::cin >> vec[0];
		do {
			std::cout << "Pin:" << std::endl;
			std::cin >> vec[1];
		} while (_p.inputPin(vec[1]));
		int location;
		int size;
		looking_for_delete(vec, "Korisnici.txt",&location,&size);
		if (location == -1)
		{
			return false;
		}
		delete_user(location,size, "Korisnici.txt");
		return true;
}

bool Administrator::getListOfUsers()
{
	int i = 0;
	std::ifstream file;
	std::vector<string> vec;
	for (int i = 0; i < ACCOUNT_SIZE; ++i)
		vec.push_back("");
	file.open("Korisnici.txt");
	if (file.is_open() == false)
		return false;
	char _line[80];
	string line;
	std::cout << "\nLista korisnika:\n\n";
	while (!file.eof()) {
		file.getline(_line, 80, '\n');
		line = _line;
		user_information(vec, line);
		
		if (vec[0][0] != '^') {
			if (line != "") {
				std::cout << ++i << ".korisnik:" << std::endl;
				UsersGroup u(vec[2], vec[3], vec[0], std::stoi(vec[4]), vec[1]);
				std::cout << u << std::endl;
			}
		}
	}
	file.close();
	return true;
}

bool Administrator::updateAccount()
{
	std::vector<string> vec;
	string temp;
	for (int i = 0; i<ACCOUNT_SIZE; ++i)
		vec.push_back("");
	std::cout << "Informacije o korisniku ciji nalog zelite da azurirate:" << std::endl;
	std::cout << "Korisnicko ime:" << std::endl;
	std::cin >> vec[0];
	do {
		std::cout << "Pin:" << std::endl;
		std::cin >> vec[1];
	} while (_p.inputPin(vec[1]));
	int location;
	int size;
	looking_for_delete(vec, "Korisnici.txt", &location, &size);
	if (location == -1)
	{
		std::cout << "\nKorisnik nije pronadjen.\n";
		return false;
	}
	std::cout << "\nKorisnik je pronadjen.\n";
  
	delete_user(location,size, "Korisnici.txt");

	copy_file("Korisnici.txt");
	std::ofstream   file; 
	file.open("Korisnici.txt", std::ios::app);
	vec.clear();

	std::cout << "Unesite nove informacije:\n";
	std::string check;
	adding_info("Korisnici.txt",vec, check);
	file << check;
	file.close();
	return true;
}

//helper methods

std::string Administrator::looking(std::vector<std::string>& vec, const char * file) const
{
	std::ifstream dat(file);
	if (dat.is_open() == false) {
		cout << "Greska prilikom otvaranja fajla!";
		return "";
	}
	char _line[80];
	string line;
	while (!dat.eof()) {
		dat.getline(_line, 80, '\n');
		line = _line;
		if (line.find(vec[0]) != std::string::npos)
		{
			return "";
		}
		
	}
	dat.close();
	if (line== "") line = "empty";
	return line;
}

void Administrator::looking_for_delete(std::vector<std::string>& vec, const char * file, int * location,int* size) const
{
	std::ifstream dat(file);
	if (dat.is_open() == false) {
		cout << "Greska prilikom otvaranja fajla!";
		return;
	}
	char _line[80];
	string line;
	while (!dat.eof()) {
		dat.getline(_line, 80, '\n');
		line = _line;
		if (line.find(vec[0]) != std::string::npos)
		{
			*location = dat.tellg();
			*location=*location- line.size()-3;
			dat.close();
			*size = line.size()+1;
			return;
		}

	}
	dat.close();
	*location = -1;
}

bool Administrator::adding_info(const char* file,std::vector<std::string>& vec, std::string & check) const
{
	std::string temp;
	bool flag = false;
	do {
		cout << "Korisnicko ime:";    cin >> temp;
		if (!flag)
			vec.push_back(temp);
		else
			vec[0] = temp;
		temp = looking(vec, file);
		if (temp == "") {
			cout << "Nalog vec postoji!" << std::endl;
			flag = true;
		}
	} while (temp == "");
	do {
		cout << endl << "PIN(4 broja):";
		cin >> temp;
	} while (_p.inputPin(temp));
	vec.push_back(temp);

	cout << endl << "Ime:";               
	cin >> temp;
	vec.push_back(temp);
	cout << endl << "Prezime:";  
	cin >> temp;
	vec.push_back(temp);
	int ug;

		do {
			cout << endl << "Korisnicka grupa(administrator(-1) / analiticar(-2)):";
			cin >> ug;
		} while (ug != USER_ADMIN && ug != USER_ANALYST);

	cout << endl;
	string tmp = std::to_string(ug);
	check = "UN:" + vec[0] + "NA:" + vec[2] + "LN:" + vec[3] + "P:" + vec[1] + "UG:" + tmp;
	return true;
}

void Administrator::copy_file(const char * file)
{
	std::experimental::filesystem::rename(file, "Delete.txt");
	std::ifstream dat;
	dat.open("Delete.txt");
	std::ofstream dat_new;
	dat_new.open(file);
	char _line[80];
	string line;
	while (!dat.eof()) {
		dat.getline(_line, 80, '\n');
		line = _line;
		if (line.find('^') == std::string::npos)
		{
			//dat_new<< '\n';
			dat_new << _line;
			dat_new << '\n';
		}

	}
	dat.close();
	std::experimental::filesystem::remove("Delete.txt");
	dat_new.close();
}

void Administrator::delete_user(int location, int size,const char * _file)
{
	std::ofstream file;                              
	file.open(_file, std::ios::in);
	file.seekp(location);
	file << "\n";
	for (int i = 1; i < size - 1; ++i)
		file << '^';
	file << "\n";
	file.close();
}


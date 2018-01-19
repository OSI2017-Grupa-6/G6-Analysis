#include "Administrator.h"
#include"Currency.h"
#include<fstream>
#include "Load.h"
using std::string;
using std::cout;
using std::cin;
using std::endl;

#define ACCOUNT_SIZE 5

Administrator::Administrator(string name, string lastName, string pin, int usergroup, string username) :
	UsersGroup(name, lastName, pin, usergroup, username)
{}

bool Administrator::addAccount(int first_acc)
{
	std::vector<string> vec;
	string temp;
	cout << "Korisnicko ime:";    cin >> temp;
	vec.push_back(temp);
	
	temp = looking(vec, "Korisnici.txt");
	if (temp == "") {
		cout << "Nalog vec postoji!"<<std::endl; return false;
	}

	do {
		cout << endl << "PIN(4 broja):";
		cin >> temp;
	} while (temp.size() != 4);
	vec.push_back(temp);

	cout << endl << "Ime:";                 cin >> temp;
	vec.push_back(temp);
	cout << endl << "Prezime:";    cin >> temp;
	vec.push_back(temp);
	int ug;
	if (first_acc == 0)
		do {
			cout << endl << "Korisnicka grupa(administrator(-1) / analiticar(-2)):";
			cin >> ug;
		} while (ug != USER_ADMIN && ug != USER_ANALYST);
	else ug = -1;      // first account  must be admin
	cout << endl;
	string tmp = std::to_string(ug);
	std::string check = "UN:" + vec[0] + "NA:" + vec[2] + "LN:" + vec[3] + "P:" + vec[1] + "UG:" + tmp;
	std::ofstream dat("Korisnici.txt", std::ios::app);
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
		std::cout << "Informacije o korisniku kojeg zelite da obrisete:" << std::endl;
		std::cout << "Korisnicko ime:" << std::endl;
		std::cin >> vec[0];
		std::cout << "Pin:" << std::endl;
		std::cin >> vec[1];
		int location;
		int size;
		looking_for_delete(vec, "Korisnici.txt",&location,&size);
		if (location == -1)
		{
			return false;
		}
		std::ofstream file;
		file.open("Korisnici.txt",std::ios::in);
		file.seekp(location);
		file << "\n";
		for (int i = 1; i < size-1; ++i)
			file << '0';
		file << "\n";
		file.close();
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
		
		if (vec[0][0] != '0') {
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


int Administrator::options()
{
	check_currency();
	int answer;
	do {
		do {
			std::cout << "\nOpcija (1): Dodaj nalog\nOpcija (2): Pregled liste korisnika\nOpcija (3): Brisanje naloga" << std::endl;
			answer=input_int(std::cin);
			if (answer != 0 && answer != 1 && answer != 2 && answer != 3)
				std::cout << "Ne postojeca opcija, pokusajte ponovo:" << std::endl;
		} while (answer != 0 && answer != 1 && answer!=2 && answer!=3);
		
		switch (answer)
		{
		case(1): addAccount(); break;
		case(2):getListOfUsers() ? std::cout<<"" : std::cout << "Postojeca lista korisnika je prazna."; break;
		case(3):deleteAccount() ? std::cout<<"\nUspjesno ste obrisali nalog." : std::cout << "\nNeuspjeno brisanje.\n"; break;
		}
	} while (answer==1 || answer==2 || answer==3);
	return LOGOUT;
}

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


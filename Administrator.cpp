#include "Administrator.h"
#include<fstream>

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
	std::cout << std::endl << "Lista korisnika:" << std::endl << std::endl;
	char _line[80];
	string line;
	while (!file.eof()) {
		file.getline(_line, 80, '\n');
		line = _line;
		user_information(vec, line);
		if (line != "") {
			std::cout << ++i<< ".korisnik:" << std::endl;
			UsersGroup u(vec[2], vec[3], vec[0], std::stoi(vec[4]), vec[1]);
			std::cout << u << std::endl;
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
			std::cout << "\nOpcija (1): Dodaj nalog\nOpcija (2): Pregled liste korisnika" << std::endl;
			std::cin >>answer;
		} while (answer != 0 && answer != 1 && answer!=2);
		if (answer==1)
			addAccount();
		if (answer == 2)
			if(getListOfUsers()==false)
				std::cout<<"Lista je prazna!"<<std::endl;
	} while (answer==1 || answer==2);
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


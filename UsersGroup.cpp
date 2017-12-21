#include "UsersGroup.h"

#include<iostream>
#include<fstream>

#define ACCOUNT_SIZE 5
using std::cout;
using std::endl;
using std::cin;
using std::string;
UsersGroup::UsersGroup(string name, string lastName, string username, int usergroup, string pin):
	name(name), lastName(lastName), username(username), userGroup(usergroup), pin(pin)
{
}
bool UsersGroup::login()
{
	
		string tempN, tempLN, tempPin, tempU = "";
		std::vector<std::string> vec;
		for (int i = 0; i < ACCOUNT_SIZE; ++i)
			vec.push_back("");
		string line;
		do{
			std::cout << "Korisnicko ime:" << std::endl;
			std::cin >> vec[0];
		do{
			cout << "PIN(4 broja)" << endl;  cin >>vec[1];
		} while (vec[1].size() != 4);
		int location;
		line = looking(vec, "Korisnici.txt");
		if (line == "") {
			cout << "\nPrijava nije uspijela!!" << std::endl;
			cout << "Da li zelite pokusati ponovo ili napustiti sistem? (1)/(0)" << std::endl;
			int i;
			cin >> i;
			if (i == 0) return false;
		}
	} while (line == "");
	user_information(vec, line);
	username = vec[0];
	pin = vec[1];
	name = vec[2];
	lastName = vec[3];
    userGroup = std::stoi(vec[4]);
	std::cout << "Ukucajte (0) da biste se odjavili sa sistema!"<<std::endl;
		return true;
}

string UsersGroup::looking(std::vector<string>& vec, const char * file) const
{
	int flag = 0;
	std::ifstream dat(file);
	if (!dat) {
		cout << "Greska prilikom otvaranja fajla!";
		return "";
	}
	std::vector<string> temp;
	for (int i = 0; i < ACCOUNT_SIZE; ++i)
		temp.push_back("");
	char _line[80];
	string line;
	while (!dat.eof()) {
		dat.getline(_line, 80, '\n');
		line = _line;
		if (line == "") continue;
		user_information(temp, line);
		if (temp[0]==vec[0]) {
			do {
				if (vec[1]==temp[1]) {
					cout << "\nUpjesno ste se prijavili!"<<endl;
					flag = 1;
				}
				else cout << "Pogresan pin!" << endl;
			} while (!line.find(vec[1]));
			break;
		}
	}
	if (flag == 0) return "";
	dat.close();
	return line;
}

void UsersGroup::user_information(std::vector<std::string>& temp, std::string line) const
{
	if (line== "") return;
	int first = line.find("UN:");
	int last = line.find("NA:");
	temp[0] = line.substr(first + 3, last - first-3);//username
	first = line.find("NA:");
	last = line.find("LN:");
	temp[2] = line.substr(first + 3, last - first-3);//name
	first = line.find("LN:");
	last = line.find("P:"); 
	temp[3] = line.substr(first + 3, last - first-3);//last name
	first = line.find("P:");
	last = line.find("UG:");
	temp[1] = line.substr(first + 2, last - first-2);//pin
	temp[4] = line.substr(last+ 3);
}

void UsersGroup::cast(const UsersGroup &u)
{
	name = u.name;
	lastName = u.lastName;
	username = u.username;
	pin = u.pin;
	userGroup = u.userGroup;
}

std::ostream & operator<<(std::ostream &stream, const UsersGroup &u)
{
	stream << "Ime: " << u.name;
	stream << std::endl << "Prezime: " << u.lastName << std::endl;
	stream << "Korisnicko ime: " << u.username << std::endl;
	//stream << "Pin: " << u.pin << std::endl;
	stream << "Korisnicka grupa: ";
	if (u.userGroup == -1)
		stream << "administrator" << std::endl;
	else stream << "analiticar" << std::endl;
	return stream;
}


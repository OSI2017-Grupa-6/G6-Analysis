#include "UsersGroup.h"

#include<iostream>
#include<fstream>

using std::cout;
using std::endl;
using std::cin;
using std::string;
UsersGroup::UsersGroup(string name, string lastName, string pin, int usergroup, string username):
	name(name), lastName(lastName), pin(pin), userGroup(usergroup), username(username)
{
}
bool UsersGroup::login()
{
	cout << "Username:" << endl;
	cin >> username;

	do {
		cout << "PIN(4 number)" << endl;  cin >> pin;
	} while (pin.size() != 4);

	std::ifstream dat("User information.txt");
	if (!dat) {
		cout << "Error while opening file!";
		return false;
	}
	char _line[80];
	string line;
	while (!dat.eof()) {
		dat.getline(_line, 80, '\n');
		 line=_line;

		 if (line.find(username) != std::string::npos) {
			 cout << "Account  exists!" << endl;
			 do{
				 if (line.find(pin) != std::string::npos) {
					 cout << "Sucessfull login";
				 }
				 else cout << "Wrong pin!" << endl;
			 } while (!line.find(pin));
			 break;
		 }
		
	}
	unsigned int first=line.find("NA:");
	unsigned int last = line.find("LN:");
	name = line.substr(first+3,last - first+3);
	first = line.find("LN:");
	last = line.find ("P:");
	lastName = line.substr(first+2, last - first+2);
	first = line.find("UG:");
	userGroup = stoi(line.substr(first+3));
	dat.close();

		return true;

}

void UsersGroup::cast(const UsersGroup &u)
{
	name = u.name;
	lastName = u.lastName;
	username = u.username;
	pin = u.pin;
	userGroup = u.userGroup;
}

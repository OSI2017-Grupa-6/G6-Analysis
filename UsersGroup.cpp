#include "UsersGroup.h"

#include<iostream>
#include<fstream>

using std::cout;
using std::endl;
using std::cin;
using std::string;
UsersGroup::UsersGroup(string name, string lastName, string pin, int usergroup, string username) :
	name(name), lastName(lastName), pin(pin), userGroup(usergroup), username(username)
{
}
bool UsersGroup::login()
{

	string tempN, tempLN, tempPin, tempU = "";
	std::vector<std::string> vec;
	string line;
	vec.push_back(tempU);
	do {
		cout << "Name:" << endl;
		cin >> tempN;
		cout << "Last Name:" << endl;
		cin >> tempLN;

		do {
			cout << "PIN(4 number)" << endl;  cin >> tempPin;
		} while (tempPin.size() != 4);
		vec.push_back(tempPin);
		vec.push_back(tempN);
		vec.push_back(tempLN);
		line = looking(vec, "User information.txt");
		if (line == "") {
			cout << "Unsuccessfull login!!" << std::endl;
			cout << "Do you want to try again or exit? 1/0" << std::endl;
			int i;
			cin >> i;
			if (i == 0) return false;
		}
	} while (line == "");
	unsigned int first = line.find("UN:");
	unsigned int last = line.find("NA:");
	username = line.substr(first + 3, last - first);
	name = tempN;
	lastName = tempLN;
	pin = tempPin;
	first = line.find("UG:");
	userGroup = stoi(line.substr(first + 3));
	return true;

}

string UsersGroup::looking(std::vector<string> vec, const char * file) const
{
	int flag = 0;
	std::ifstream dat(file);
	if (!dat) {
		cout << "Error while opening file!";
		return "";
	}
	char _line[80];
	string line;
	while (!dat.eof()) {
		dat.getline(_line, 80, '\n');
		line = _line;

		if (line.find(vec[2]) != std::string::npos &&line.find(vec[3]) != std::string::npos) {
			cout << "Account  exists!" << endl;
			do {
				if (line.find(vec[1]) != std::string::npos) {
					cout << "Sucessfull login" << endl;
					flag = 1;
				}
				else cout << "Wrong pin!" << endl;
			} while (!line.find(vec[1]));
			break;
		}
	}
	if (flag == 0) return "";
	dat.close();
	return line;
}

void UsersGroup::cast(const UsersGroup &u)
{
	name = u.name;
	lastName = u.lastName;
	username = u.username;
	pin = u.pin;
	userGroup = u.userGroup;
}

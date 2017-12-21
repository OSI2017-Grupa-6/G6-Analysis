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
			std::cout << "Username:" << std::endl;
			std::cin >> vec[0];
		do{
			cout << "PIN(4 number)" << endl;  cin >>vec[1];
		} while (vec[1].size() != 4);
		int location;
		line = looking(vec, "User information.txt");
		if (line == "") {
			cout << "Unsuccessfull login!!" << std::endl;
			cout << "Do you want to try again or exit? 1/0" << std::endl;
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
	std::cout << "Enter (0) for logging out!"<<std::endl;
		return true;
}

string UsersGroup::looking(std::vector<string>& vec, const char * file) const
{
	int flag = 0;
	std::ifstream dat(file);
	if (!dat) {
		cout << "Error while opening file!";
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
					cout << "Sucessfull login"<<endl;
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
	stream << "Name: " << u.name;
	stream << std::endl << "Last name: " << u.lastName << std::endl;
	stream << "Username: " << u.username << std::endl;
	//stream << "Pin: " << u.pin << std::endl;
	stream << "Users group: ";
	if (u.userGroup == -1)
		stream << "aministrator" << std::endl;
	else stream << "analyst" << std::endl;
	return stream;
}


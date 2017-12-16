#include "Administrator.h"
#include<fstream>

using std::string;
using std::cout;
using std::cin;
using std::endl;

Administrator::Administrator(string name, string lastName, string pin, int usergroup, string username) :
	UsersGroup(name, lastName, pin, usergroup, username)
{}

bool Administrator::addAccount()
{
	cout << "User name:";    cin >> username;
	cout << endl << "Name:";                 cin >> name;
	cout << endl << "Last name:";    cin >> lastName;

	do {
		cout << endl << "PIN(4 broja):";
		cin >> pin;
	} while (pin.size() != 4);
	do {
		cout << endl << "User group:";
		cin >> userGroup;
	} while (userGroup != USER_ADMIN && userGroup != USER_ANALYST);

	cout << endl;
	string temp = std::to_string(userGroup);
	std::string check = "UN:" + username + "NA:" + name + "LN:" + lastName + "P:" + pin + "UG:" + temp;

	std::ifstream dat("User information.txt");
	if (dat.is_open() == false) {
		cout << "Error while opening file!";
		return false;
	}
	char line[80];
	while (!dat.eof()) {
		dat.getline(line, 80, '\n');
		if (strcmp(line, check.c_str()) == 0) {
			cout << "Account already exists!";
			return false;
		}
	}
	dat.close();
	std::ofstream dat1("User information.txt", std::ios::app);

	dat1 << check << endl;
	dat1.close();

	return true;
}

int Administrator::options()
{
	int answer;
	do {
		do {
			std::cout << std::endl<<"Do you want to create account? 1/0"<<" ";
			std::cin >> answer;
		} while (answer != 0 && answer != 1);
		if (answer)
			addAccount();
	} while (answer != 0);
	return LOGOUT;
}


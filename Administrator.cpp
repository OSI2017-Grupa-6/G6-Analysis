#include "Administrator.h"
#include<fstream>

using std::string;
using std::cout;
using std::cin;
using std::endl;

Administrator::Administrator(string name, string lastName, string pin, int usergroup, string username) :
	UsersGroup(name, lastName, pin, usergroup, username)
{}

bool Administrator::addAccount(int first_acc)
{
	std::vector<string> vec;
	string temp;
	cout << "Username:";    cin >> temp;
	vec.push_back(temp);
	do {
		cout << endl << "PIN(4 broja):";
		cin >> temp;
	} while (temp.size() != 4);
	vec.push_back(temp);
	
	temp = looking(vec, "User information.txt");
	if (temp == "") {
		cout << "Account already exists!"; return false;
	}
	cout << endl << "Name:";                 cin >> temp;
	vec.push_back(temp);
	cout << endl << "Last name:";    cin >> temp;
	vec.push_back(temp);
	int ug;
	if (first_acc == 0)
		do {
			cout << endl << "User group:";
			cin >> ug;
		} while (ug != USER_ADMIN && ug != USER_ANALYST);
	else ug = -1;      // first account  must be admin
	cout << endl;
	string tmp = std::to_string(ug);
	std::string check = "UN:" + vec[0] + "NA:" + vec[2] + "LN:" + vec[3] + "P:" + vec[1] + "UG:" + tmp;
	std::ofstream dat("User information.txt", std::ios::app);
	dat << check << endl;
	dat.close();

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

std::string Administrator::looking(std::vector<std::string>& vec, const char * file) const
{
	std::ifstream dat(file);
	if (dat.is_open() == false) {
		cout << "Error while opening file!";
		return "";
	}
	char _line[80];
	string line;
	while (!dat.eof()) {
		dat.getline(_line, 80, '\n');
		line = _line;
		if (line.find(vec[0]) != std::string::npos && line.find(vec[1]) != std::string::npos) {
			return "";
		}
		
	}
	dat.close();
	if (line== "") line = "empty";
	return line;
}


#include "CreateAccount.h"



CreateAccount::CreateAccount()
{

	

}


CreateAccount::~CreateAccount()
{
	
}

bool CreateAccount::addAccount()
{
	cout << "User name:";    cin >> userName;
	cout << endl << "Name:";                 cin >> name;
	cout << endl << "Last name:";    cin >> lastName;

	do {
		cout << endl << "PIN(4 broja):";
        cin >> pin;
	} while (strlen(pin) != 4);
	cout << endl << "User group:";   cin >> userGroup;

	cout << endl;

	char check[80];
	strcpy(check, userName);
	strcat(check, name);
	strcat(check, lastName);
	strcat(check, pin);
	strcat(check, userGroup);
	
	ifstream dat("User information.txt", ios::in);
	if (!dat) {
		cout << "Greska u otvaranju!";
		return false;
	}
	char line[80];
	
	while (dat) {
		cout << "111";
		dat.getline(line, 80, '\n');
		if (strcmp(line, check) == 0) {
			cout << "Account already exists!";
			return false;
		}
	}

	dat.close();
	ofstream dat1("User information.txt", ios::app);
	
	
	
	dat1 << check << endl;
	dat1.close();

	return true;
	}


		



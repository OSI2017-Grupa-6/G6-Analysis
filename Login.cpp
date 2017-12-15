#include "Login.h"



Login::Login()
{
}


Login::~Login()
{
}

bool Login::login()
{
	cout << "Username:" << endl;   cin >> userName;

	do {
		cout << "PIN(4 number)" << endl;  cin >> pin;
	} while (strlen(pin) != 4);

	ifstream dat("User information.txt", ios::in);
	if (!dat) {
		cout << "Greska u otvaranju!";
		return false;
	}
	char line[80];

	while (dat) {
		dat.getline(line, 80, '\n');
		if (strstr(line, userName)) {
			cout << "Account  exists!"<<endl;
			do {
				if (strstr(line, pin))
					cout << "Sucessfull login";
				else cout << "Pin nije dobar" << endl;
			} while (!strstr(line, pin));
			return false;

		}
		if (strstr(line, "administrator")) {

			char c;

			cout << "Opcija 1: Podesavanje valute" << endl;
			cout << "Opcija 2: Kreiranje korisnickog naloga" << endl;
			do {
				cout << "Unesite 1 ili 2" << endl;
				cin >> c;
			} while (c != 1 && c != 2);
			//if(c==1)pozovi funkciju podesavanje valute
			//if(c==2)pozovi funkciju upravljanje nalozima	
			
		}
		

		//else izvoz podataka u txt fajlove

	}

	dat.close();

	return true;
}

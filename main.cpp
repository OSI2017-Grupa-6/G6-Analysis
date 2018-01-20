#include"Processing.h"
#include"Administrator.h"
#include"Analyst.h"
#include"UsersGroup.h"
#include"InputChecker.h"
#include<cctype>
#include<iostream>
#include<vector>

#define LOGOUT 0
#define EXIT "-99"
void ClearScreen()
{
	int n;
	for (n = 0; n < 10; n++)
		std::cout << "\n\n\n\n\n\n\n\n\n\n";
}
int main(int argc, char** argv)
{

	if (argc == 1)
	{
		std::cout << "Pogresna putanja!!!";
		getchar();
		return 0; 
	}
	if (!is_empty("Valuta.txt"))
	processing("Racuni", argv[1]);//begin processing
	std::string response;
	std::string system_on;
	InputChecker check;
	do {
		std::cout << "***     DOBRODOSLI NA SISTEM G6 ANALYSIS!!!     ***" << std::endl << std::endl;
		
		do
		{
			std::cout << std::endl << "Da li zelite da se prijavite? DA(1)/NE(0)" << std::endl;
			std::cin >> response;
		} while (response!="0" && response!= "1");
		if (response == "1")
		{
			Administrator admin;
			Analyst analyst;
			UsersGroup user;
			if (user.login() == LOGOUT)
				break;
			int group = user.getGroup();
			
			if (group == USER_ADMIN) {
				admin.cast(user);
			}
			else analyst.cast(user);
			if (group == USER_ADMIN)
				admin.options();

			if (group == USER_ANALYST)
				analyst.options();
		}

		
		
		do {
			std::cout << std::endl<<"Napustanje sistema? DA(-99)/NE(0)"<<std::endl;
			std::cin >> system_on;
		} while (system_on!=EXIT && system_on!="0");
		ClearScreen();

	} while (system_on != EXIT);
	
}

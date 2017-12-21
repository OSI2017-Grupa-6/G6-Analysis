#include"Processing.h"
#include"Administrator.h"
#include"Analyst.h"
#include"UsersGroup.h"

#include<iostream>
#include<vector>
#define LOGOUT 0
#define EXIT -99

int main(int argc, char**argv)
{
	if (argc == 1)
	{
		std::cout << "Pogresna putanja!!!";
		getchar();
		return 0; //added
	}
	processing("Racuni", argv[1]);//begin processing
	int response;
	int system_on;
	//Administrator a;
	//a.addAccount(1);
	std::cout << "***     DOBRODOSLI NA SISTEM G6 ANALYSIS!!!     ***" << std::endl << std::endl;
	do {
		std::cout <<std::endl<< "Da li zelite da se prijavite? DA(1)/NE(0)" << std::endl;
		std::cin >> response;
		if (response)
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
		std::cout << std::endl<<"Napustanje sistema? DA(-99)/NE(0)"<<std::endl;
		std::cin >> system_on;
	} while (system_on != EXIT);
}

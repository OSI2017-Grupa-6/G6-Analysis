#include"Processing.h"
#include"Administrator.h"
#include"Analyst.h"
#include"UsersGroup.h"

#include<cctype>
#include<iostream>
#include<vector>

#define LOGOUT 0
#define EXIT -99

int main(int argc, char** argv)
{
	Administrator one;
	one.addAccount();
	if (argc == 1)
	{
		std::cout << "Pogresna putanja!!!";
		getchar();
		return 0; 
	}
	if (!is_empty("Valuta.txt"))
	processing("Racuni", argv[1]);//begin processing
	int response;
	int system_on;
	do {
		std::cout << "***     DOBRODOSLI NA SISTEM G6 ANALYSIS!!!     ***" << std::endl << std::endl;
		std::cout << std::endl << "Da li zelite da se prijavite? DA(1)/NE(0)" << std::endl;
		do
		{
		response = input_int(std::cin);
		if (response != 1 && response != 0)
			std::cout << "Ne postojeca opcija, pokusajte ponovo." << std::endl;
		} while (response != 1 && response != 0);
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
		
		do {
			system_on=input_int(std::cin);
			if (system_on != EXIT && system_on != 0)
				std::cout << "Ne postojeca opcija, pokusajte ponovo:" << std::endl;
		} while (system_on != EXIT && system_on != 0);
	
	} while (system_on != EXIT);
}

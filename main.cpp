#include"Processing.h"
#include"Administrator.h"
#include"Analyst.h"
#include"UsersGroup.h"
#include"InputChecker.h"
#include<cctype>
#include<iostream>
#include<vector>

#define LOGOUT 0
#define EXIT -99
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
	int response;
	int system_on;
	InputChecker check;
	do {
		std::cout << "***     DOBRODOSLI NA SISTEM G6 ANALYSIS!!!     ***" << std::endl << std::endl;
		std::cout << std::endl << "Da li zelite da se prijavite? DA(1)/NE(0)" << std::endl;
		do
		{
		response = input_int(std::cin);
		} while (check.inputExiting(1,0,response)==false);
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
		} while (check.inputExiting(EXIT,0, response) == false);
		ClearScreen();

	} while (system_on != EXIT);
	
}

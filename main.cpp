
#include"Processing.h"
#include"Administrator.h"
#include"Analyst.h"
#include"UsersGroup.h"

#include<iostream>
#include<vector>
#define LOGOUT 0
#define EXIT -99
int main()
{
#include"Processing.h"
#include"Administrator.h"
#include"Analyst.h"
#include"UsersGroup.h"

#include<iostream>
#include<vector>
#define LOGOUT 0
#define EXIT -99
	int main()
	{
		//processing("Racuni","C:\\Users\\PWIN\\Desktop\\Programski jezici 1\\Projekti\\Project2\\Project2\\");
		int response;
		int system_on;
		Administrator a; //example of first user
		a.addAccount();
		do {
			std::cout << std::endl << "Do you want to login:" << std::endl;
			std::cin >> response;
			if (response)
			{
				Administrator admin;
				Analyst analyst;
				UsersGroup user;
				user.login();
				int group = user.getGroup();

				if (group == USER_ADMIN) {
					admin.cast(user);
				}
				else analyst.cast(user);
				if (group == USER_ADMIN)
					admin.options();
				std::cout << group;
				if (group == USER_ANALYST)
					analyst.options();
			}
			std::cout << std::endl << "EXIT? (-99)" << std::endl;
			std::cin >> system_on;
		} while (system_on != EXIT);
	}
	//processing("Racuni","C:\\Users\\PWIN\\Desktop\\Programski jezici 1\\Projekti\\Project2\\Project2\\");
	int response;
	int system_on;
	//Administrator a;
	//a.addAccount();
	do {
		std::cout <<std::endl<< "Do you want to login:" << std::endl;
		std::cin >> response;
		if (response)
		{
			Administrator admin;
			Analyst analyst;
			UsersGroup user;
			user.login();
			int group = user.getGroup();
			
			if (group == USER_ADMIN) {
				admin.cast(user);
			}
			else analyst.cast(user);
			if (group == USER_ADMIN)
				admin.options();
			std::cout << group;
			if (group == USER_ANALYST)
				analyst.options();
		}
		std::cout << std::endl<<"EXIT? (-99)"<<std::endl;
		std::cin >> system_on;
	} while (system_on != EXIT);
}
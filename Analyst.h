#pragma once
#include<string>
#include"UsersGroup.h"
#include<filesystem>

class Analyst:public UsersGroup
{
public:
	Analyst(std::string,std::string,std::string,int,std::string);
	Analyst() = default;

	bool look_for_buyer();
	bool look_for_product();
	bool look_for_month();
	
	int options();
private:
	bool searching_for(const char* file, std::string name);
};
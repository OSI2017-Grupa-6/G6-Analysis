#pragma once
#include<string>
#include<iostream>

#include"UsersGroup.h"


class Administrator :public UsersGroup
{
public:
	Administrator() = default;
	Administrator(std::string, std::string, std::string, int, std::string);
	bool addAccount(int first_acc=0);
	bool deleteAccount();
	bool getListOfUsers();
	int options();
protected:
	std::string looking(std::vector<std::string>&, const char* file) const override;
	void looking_for_delete(std::vector<std::string>&, const char* file, int* location,int* size) const;
};


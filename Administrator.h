#pragma once
#include<string>
#include<iostream>

#include"UsersGroup.h"


class Administrator :public UsersGroup
{
public:
	Administrator() = default;
	Administrator(std::string, std::string, std::string, int, std::string);
	bool addAccount();
	int options();
};


#pragma once

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#define USER_ADMIN -1
#define USER_ANALYST -2
#define LOGOUT 0

class UsersGroup
{
public:
	void cast(const UsersGroup& u);
	UsersGroup() = default;
	UsersGroup(std::string, std::string, std::string, int, std::string);
	UsersGroup(UsersGroup&&) = default;
	UsersGroup& operator=(UsersGroup&&) = default;
	virtual bool login();


	int getGroup() { return userGroup; }
protected:
	std::string name, lastName, pin, username;
	int userGroup;
	virtual std::string looking(std::vector<std::string>, const char* file) const;
};


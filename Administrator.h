#pragma once
#include<string>
#include<vector>
#include<iostream>

#include"UsersGroup.h"


class Administrator :public UsersGroup
{
public:
	Administrator() = default;
	Administrator(std::string, std::string, std::string, int, std::string);
	bool addAccount();
	bool deleteAccount();
	bool getListOfUsers();
	bool updateAccount();
	int options();

protected:
	std::string looking(std::vector<std::string>&, const char* file) const override;
	void looking_for_delete(std::vector<std::string>&, const char* file, int* location,int* size) const;
	bool adding_info(const char* file,std::vector<std::string>& vec, std::string& check) const;
	void copy_file(const char* file);
	void delete_user(int location,int size, const char* _file);
};


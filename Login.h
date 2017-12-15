#pragma once

#include<iostream>
#include<fstream>

using namespace std;
class Login
{

	char userName[20], pin[10];

public:
	Login();
	~Login();
	bool login();
};


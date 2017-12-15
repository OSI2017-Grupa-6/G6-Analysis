#pragma once
#include<cstring>
#include<iostream>
#include<fstream>
#include<conio.h>
#include<stdio.h>
using namespace std;

class CreateAccount
{
public:
	 char name[20], lastName[20], pin[10], userGroup[10],userName[20];
	 


public:
	CreateAccount();
	~CreateAccount();
	bool addAccount();

};


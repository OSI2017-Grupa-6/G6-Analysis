#pragma once
#include <Windows.h>
#include<vector>
#include<string>
#include<iostream>
#include<fstream>

#include "Receipt.h"

using std::vector;
using std::string;
vector<Receipt> load(string folder);
int input_int(std::istream&);

 
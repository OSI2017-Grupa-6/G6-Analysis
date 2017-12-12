#pragma once
#include <Windows.h>
#include<vector>
#include<string>
#include<iostream>
#include<fstream>

#include "Receipt.h"

using std::vector;
using std::string;
vector<Receipt> get_all_files_names_within_folder(string folder);
Receipt format(const char*);

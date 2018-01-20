#pragma once
#include"Receipt.h"
#include"Load.h"
#include <string>


void processing(const char*,const char*);
void send_to_files(std::vector<Receipt>&,const char*);
void send_to_files_month(std::vector<Receipt>, const char*);
bool is_empty(const char*);
std::string get_month(std::string);
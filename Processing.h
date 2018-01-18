#pragma once
#include"Receipt.h"
#include"Load.h"

void processing(const char*,const char*);
void send_to_files(std::vector<Receipt>&,const char*path);
bool is_empty(const char*);
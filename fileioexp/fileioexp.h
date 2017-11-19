
#pragma once
#ifndef FILEIOEXP_H
#define FILEIOEXP_H


#include "accounts.h"
#include "checking.h"
#include "savings.h"
#include "master.h"


void printAllAccounts(Checking&, Savings&, std::ifstream&);
std::string getAccountType(std::ifstream&);




#endif
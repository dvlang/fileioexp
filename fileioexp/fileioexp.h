
#pragma once
#ifndef FILEIOEXP_H
#define FILEIOEXP_H


#include "accounts.h"
#include "checking.h"
#include "savings.h"
#include "master.h"


void printAllAccounts(Checking&, Savings&, std::ifstream&);
std::string getAccountType(std::ifstream&);
bool checkDate(std::string , std::string , std::string , std::string);
void updateInterestAllAccounts(Master&, Checking&, Checking&, Savings&, Savings&, std::ifstream&, std::ofstream& , int*, int);
int countAccounts(std::ifstream&);
void getAllAcctNums(Master&, std::ifstream&, int*);



#endif
#pragma once
#ifndef ACCOUNTS_H
#define ACCOUNTS_H
#include <string>
#include <iostream>
#include <fstream>


class Accounts {

public:
	Accounts();
	void printAccount();
	void setAccountNumber(int);
	void setAccountName(std::string);
	void setAccountValue(double);


private:
	int account_Number;
	std::string name_Owner;
	double amount_Avail;

};
#endif
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
	int getAccountNumber();
	std::string getAccountName();
	double getAccountValue();

	/*
	void GetRecordwc(ifstream&);
	bool FindRecordwClass(ifstream&, int, int *recloc, int *recordend);
	bool AddRecordwc(ofstream&);
	*/

private:
	int account_Number;
	std::string name_Owner;
	double amount_Avail;

};
#endif
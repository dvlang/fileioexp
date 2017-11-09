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
	void printAllAccounts(std::ifstream&);
	void setAccountNumber(int);
	void setAccountName(std::string);
	void setAccountValue(double);
	int getAccountNumber();
	std::string getAccountName();
	double getAccountValue();

	bool accountWithdrawl(double);

	
	void GetRecordwc(std::ifstream&);
	
	//bool FindRecordwClass(ifstream&, int, int *recloc, int *recordend);
	bool AddRecordwc(std::ofstream&);

	bool doesAccountExist(std::ifstream &inputfile, const int);

private:
	int account_Number;
	std::string name_Owner;
	double amount_Avail;

};
#endif
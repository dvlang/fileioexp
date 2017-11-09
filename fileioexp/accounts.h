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
	void accountDeposit(double);
	void accountAddInterest();
	
	void GetRecordwc(std::ifstream&);
	
	bool FindRecordwClass(Accounts &accref, std::ifstream &inputfile, int tmpAccountNum);
	bool ModifyRecordwc(Accounts &record, std::ofstream&);
	bool AddRecordwc(std::ofstream&);

	bool doesAccountExist(std::ifstream &inputfile, const int);

private:
	int account_Number;
	std::string name_Owner;
	double amount_Avail;
	int recordlocator;
	int recordEnd;

};
#endif
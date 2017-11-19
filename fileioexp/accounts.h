
#ifndef ACCOUNTS_H
#define ACCOUNTS_H
#include <string>
#include <iostream>
#include <fstream>
#include <time.h>
#include <cstring>
#include <sstream>

const char FILENAME[14] = "accounts.dat";	//this is the name of the account data file

const float INTERESTRATE = 0.01;


class Accounts {

public:
	Accounts();

	void setAccountType(std::string);
	void setAccountNumber(int);
	void setAccountName(std::string);
	void setAccountValue(double);
	void setDateOpened(std::string);
	
	int getAccountNumber();
	std::string getAccountName();
	double getAccountValue();
	std::string getAccountType();
	std::string getDateOpened();

	void accountDeposit(double);
		
	virtual void GetRecordwc(std::ifstream&)=0;//make it abstract
	virtual void printAccount();
	virtual bool FindRecordwClass(Accounts &accref, std::ifstream &inputfile, int tmpAccountNum);
	virtual bool ModifyRecordwc(Accounts &record, std::ofstream&);
	virtual bool AddRecordwc(std::ofstream&);
	virtual bool doesAccountExist(std::ifstream &inputfile, const int);
	virtual bool accountWithdrawl(double);
	virtual void accountAddInterest();

protected:
	int account_Number;
	std::string name_Owner;
	double amount_Avail;
	std::string date_Opened;
	std::string account_Type;
	int recordlocator;
	int recordEnd;

};



#endif
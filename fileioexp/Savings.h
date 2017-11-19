
#ifndef SAVINGS_H
#define SAVINGS_H
#include <string>
#include <iostream>
#include <fstream>
#include <time.h>
#include "accounts.h"

class Savings :public Accounts {

public:
	Savings();
	~Savings();
	void setMatDate(std::string matdate);
	void setCurInt(double curint);
	void setDefInt(double defint);

	std::string getMatDate();
	double getCurInt();
	double getDefInt();

	virtual void GetRecordwc(std::ifstream& inputfile);
	virtual void printAccount();
	virtual bool doesAccountExist(std::ifstream&, const int);
	virtual bool AddRecordwc(std::ofstream&);
	virtual bool FindRecordwClass(Savings&, std::ifstream&, int);
	virtual bool ModifyRecordwc(Savings&, std::ofstream&);
	virtual bool accountWithdrawl(double);
	virtual void accountAddInterest();

private:
	std::string maturity_Date;
	double current_Interest;
	double default_Interest;
};

#endif
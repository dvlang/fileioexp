
#ifndef CHECKING_H
#define CHECKING_H
#include <string>
#include <iostream>
#include <fstream>
#include <time.h>
#include "accounts.h"

class Checking :public Accounts {

public:
	Checking();
	~Checking();
	void setDirectdeposit(bool);
	void setTransFee(double);

	bool getDirectDeposit();
	double getTransFee();

	void assessCheckingTransFee();

	virtual void GetRecordwc(std::ifstream&);
	virtual void printAccount();
	virtual bool doesAccountExist(std::ifstream&, const int);
	virtual bool AddRecordwc(std::ofstream&);
	virtual bool FindRecordwClass(Checking&, std::ifstream&, int);
	virtual bool ModifyRecordwc(Checking&, std::ofstream&);

private:
	bool direct_Deposit;
	double transaction_Fee;

};

#endif

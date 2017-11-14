#pragma once
#ifndef ACCOUNTS_H
#define ACCOUNTS_H
#include <string>
#include <iostream>
#include <fstream>


const char FILENAME[14] = "accounts.dat";	//this is the name of the account data file

const float INTERESTRATE = 0.01;


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
	
	virtual void GetRecordwc(std::ifstream&);
	std::string getAccountType(std::ifstream &inputfile);
	
	bool FindRecordwClass(Accounts &accref, std::ifstream &inputfile, int tmpAccountNum);
	bool ModifyRecordwc(Accounts &record, std::ofstream&);
	bool AddRecordwc(std::ofstream&);

	bool doesAccountExist(std::ifstream &inputfile, const int);

protected:
	int account_Number;
	std::string name_Owner;
	double amount_Avail;
	int recordlocator;
	int recordEnd;

};

//------------------------------CHECKING CLASS------------------------------------------------------
class Checking:public Accounts {

public:
	Checking() :direct_Deposit(false), transaction_Fee(0.0) {}

	virtual void GetRecordwc(std::ifstream& inputfile) {
		
			std::istringstream tmpstring;
			std::string wholeentry;
			std::string accountNumber;
			std::string accountName;
			std::string accountValue;
			std::string accountType;
			std::string dateOpened;
			std::string dd;

			int i, j;
			int accountnum;
			double value;
			bool ddd;

			tmpstring.clear();

			getline(inputfile, wholeentry);

			//BEGIN LINE PARSING
			std::cout << "input line is: " << wholeentry << std::endl;

			//GET ACCOUNT TYPE
			i = 0;
			while (wholeentry.compare(i, 1, ";") != 0) { i++; }
			accountType = wholeentry.substr(0, i);
			tmpstring.str(accountType);

			tmpstring >> accountType;
			std::cout << "gr_ account type is: " << accountType << std::endl;

			//GET ACCOUNT NUMBER

			i += 2;
			j = i;	//j is placeholder to beginning of next entry

			while (wholeentry.compare(i, 1, ";") != 0) { i++; }
			accountNumber = wholeentry.substr(j, i - j);
			tmpstring.str(accountNumber);

			tmpstring >> account_Number;
			account_Number = std::stoi(accountNumber);
			std::cout << "gr_ account number is: " << account_Number << std::endl;

			//GET NAME OF THE OWNER
			i += 2;	//move i index off ";" and space
			j = i;	//j is placeholder to beginning of next entry
			while (wholeentry.compare(i, 1, ";") != 0) { i++; }
			accountName = wholeentry.substr(j, i - j);

			name_Owner = accountName;

			std::cout << "gr_ account name is: " << name_Owner << std::endl;

			//GET AMOUNT AVAILABLE IN ACCOUNT
			i += 2;	//move i index off ";" and space
			j = i;	//j is placeholder to beginning of next entry
			tmpstring.clear();
			tmpstring.precision(10);
			tmpstring.fixed;
			while (wholeentry.compare(i, 1, ";") != 0) { i++; }
			accountValue = wholeentry.substr(j, i - j);

			tmpstring.str(accountValue);
			tmpstring >> value;

			amount_Avail = value;

			std::cout.precision(15);
			std::cout << "gr_ account value is: " << amount_Avail << std::endl;

			//GET DATE ACCOUNT OPENED
			i += 2;	//move i index off ";" and space
			j = i;	//j is placeholder to beginning of next entry
			while (wholeentry.compare(i, 1, ";") != 0) { i++; }
			dateOpened = wholeentry.substr(j, i - j);

			std::cout << "gr_ account opened: " << dateOpened << std::endl;
			
			tmpstring.clear();
			//GET Direct deposit
			i += 2;	//move i index off ";" and space
			j = i;	//j is placeholder to beginning of next entry
			while (wholeentry.compare(i, 1, ";") != 0) { i++; }
			dd = wholeentry.substr(j, i - j);
			
			tmpstring.str(dd);
			tmpstring >> std::boolalpha>> direct_Deposit;

			
			if (direct_Deposit){
				//direct_Deposit = true;
				std::cout << "gr_ account direct_Deposit: true " << std::endl;
			}
			else{ 
				//direct_Deposit = false; 
				std::cout << "gr_ account direct_Deposit: false " << std::endl;
			}
			
			tmpstring.clear();

			//GET TRANSACTION FEE ACCOUNT OPENED
			i += 2;	//move i index off ";" and space
			j = i;	//j is placeholder to beginning of next entry
			while (wholeentry.compare(i, 1, ";") != 0) { i++; }
			accountValue = wholeentry.substr(j, i - j);

			tmpstring.str(accountValue);
			tmpstring >> value;

			transaction_Fee = value;

			std::cout.precision(15);
			std::cout << "gr_ trans fee is: " << transaction_Fee << std::endl;


			// END LINE PARSING	

			return;
		}


private:
	bool direct_Deposit;
	double transaction_Fee;

};
//------------------------------END CHECKING CLASS------------------------------------------------------

//------------------------------SAVINGS CLASS-----------------------------------------------------------
class Savings :public Accounts {

public:
	Savings() :maturity_Date("01/01/1980"), current_Interest(0.01), default_Interest(0.01)
	{
	}

	virtual void GetRecordwc(std::ifstream& inputfile) {

		std::istringstream tmpstring;
		std::string wholeentry;
		std::string accountNumber;
		std::string accountName;
		std::string accountValue;
		std::string accountType;
		std::string dateOpened;
		std::string dd;

		int i, j;
		int accountnum;
		double value;
		bool ddd;

		tmpstring.clear();

		getline(inputfile, wholeentry);

		//BEGIN LINE PARSING
		std::cout << "input line is: " << wholeentry << std::endl;

		//GET ACCOUNT TYPE
		i = 0;
		while (wholeentry.compare(i, 1, ";") != 0) { i++; }
		accountType = wholeentry.substr(0, i);
		tmpstring.str(accountType);

		tmpstring >> accountType;
		std::cout << "gr_ account type is: " << accountType << std::endl;

		//GET ACCOUNT NUMBER

		i += 2;
		j = i;	//j is placeholder to beginning of next entry

		while (wholeentry.compare(i, 1, ";") != 0) { i++; }
		accountNumber = wholeentry.substr(j, i - j);
		tmpstring.str(accountNumber);

		tmpstring >> account_Number;
		account_Number = std::stoi(accountNumber);
		std::cout << "gr_ account number is: " << account_Number << std::endl;

		//GET NAME OF THE OWNER
		i += 2;	//move i index off ";" and space
		j = i;	//j is placeholder to beginning of next entry
		while (wholeentry.compare(i, 1, ";") != 0) { i++; }
		accountName = wholeentry.substr(j, i - j);

		name_Owner = accountName;

		std::cout << "gr_ account name is: " << name_Owner << std::endl;

		//GET AMOUNT AVAILABLE IN ACCOUNT
		i += 2;	//move i index off ";" and space
		j = i;	//j is placeholder to beginning of next entry
		tmpstring.clear();
		tmpstring.precision(10);
		tmpstring.fixed;
		while (wholeentry.compare(i, 1, ";") != 0) { i++; }
		accountValue = wholeentry.substr(j, i - j);

		tmpstring.str(accountValue);
		tmpstring >> value;

		amount_Avail = value;

		std::cout.precision(15);
		std::cout << "gr_ account value is: " << amount_Avail << std::endl;

		//GET DATE ACCOUNT OPENED
		i += 2;	//move i index off ";" and space
		j = i;	//j is placeholder to beginning of next entry
		while (wholeentry.compare(i, 1, ";") != 0) { i++; }
		dateOpened = wholeentry.substr(j, i - j);

		std::cout << "gr_ account opened: " << dateOpened << std::endl;

		tmpstring.clear();
		
		
		//GET MATURITY DATE
		i += 2;	//move i index off ";" and space
		j = i;	//j is placeholder to beginning of next entry
		while (wholeentry.compare(i, 1, ";") != 0) { i++; }
		maturity_Date = wholeentry.substr(j, i - j);

		std::cout << "gr_ MATURITY DATE : " << maturity_Date << std::endl;

		tmpstring.clear();

		//GET CURRENT INTEREST
		i += 2;	//move i index off ";" and space
		j = i;	//j is placeholder to beginning of next entry
		tmpstring.clear();
		tmpstring.precision(10);
		tmpstring.fixed;
		while (wholeentry.compare(i, 1, ";") != 0) { i++; }
		accountValue = wholeentry.substr(j, i - j);

		tmpstring.str(accountValue);
		tmpstring >> value;

		current_Interest = value;

		std::cout.precision(15);
		std::cout << "gr_ current_Interest value is: " << current_Interest << std::endl;
		tmpstring.clear();


		//GET DEFAULT INTEREST
		i += 2;	//move i index off ";" and space
		j = i;	//j is placeholder to beginning of next entry
		tmpstring.clear();
		tmpstring.precision(10);
		tmpstring.fixed;
		while (wholeentry.compare(i, 1, ";") != 0) { i++; }
		accountValue = wholeentry.substr(j, i - j);

		tmpstring.str(accountValue);
		tmpstring >> value;

		default_Interest = value;

		std::cout.precision(15);
		std::cout << "gr_ default_Interest value is: " << default_Interest << std::endl;
		tmpstring.clear();



		// END LINE PARSING	

		return;
	}


private:
	std::string maturity_Date;
	double current_Interest;
	double default_Interest;

};





#endif
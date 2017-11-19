#pragma once
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
	//void printAccount();

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


	//bool accountWithdrawl(double);
	void accountDeposit(double);
	//void accountAddInterest();
	
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

//------------------------------MASTER CLASS------------------------------------------------------
class Master :public Accounts {
	//this class exists just to provide access to base class methods and data objects
public:
	~Master() { std::cout << "destroy MASTER" << std::endl; }

	virtual void GetRecordwc(std::ifstream &inputfile) {
		std::istringstream tmpstring;
		std::string wholeentry;
		std::string accountNumber;
		std::string accountName;
		std::string accountValue;
		std::string accountType;
		std::string dateOpened;

		int i, j;
		int accountnum;
		double value;

		tmpstring.clear();

		getline(inputfile, wholeentry);

		//BEGIN LINE PARSING
		//std::cout << "input line is: " << wholeentry << std::endl;

		i = 0;
		while (wholeentry.compare(i, 1, ";") != 0) { i++; }
		accountType = wholeentry.substr(0, i);
		tmpstring.str(accountType);

		tmpstring >> accountType;
		account_Type = accountType;
		//std::cout << "MASTERgr_ account type is: " << accountType << std::endl;

		//i = 0;
		i += 2;
		j = i;	//j is placeholder to beginning of next entry

				//accountNumber = wholeentry.substr(0, i);
		while (wholeentry.compare(i, 1, ";") != 0) { i++; }
		accountNumber = wholeentry.substr(j, i - j);
		tmpstring.str(accountNumber);

		tmpstring >> account_Number;
		account_Number = std::stoi(accountNumber);
		//std::cout << "MASTERgr_ account number is: " << account_Number << std::endl;


		i += 2;	//move i index off ";" and space
		j = i;	//j is placeholder to beginning of next entry
		while (wholeentry.compare(i, 1, ";") != 0) { i++; }
		accountName = wholeentry.substr(j, i - j);


		name_Owner = accountName;

		//std::cout << "MASTERgr_ account name is: " << name_Owner << std::endl;

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
		//std::cout << "MASTERgr_ account value is: " << amount_Avail << std::endl;


		i += 2;	//move i index off ";" and space
		j = i;	//j is placeholder to beginning of next entry
		while (wholeentry.compare(i, 1, ";") != 0) { i++; }
		dateOpened = wholeentry.substr(j, i - j);


		//date_Opened = dateOpened;

	//	std::cout << "MASTERgr_ account opened: " << dateOpened << std::endl;

		// END LINE PARSING	

		return;
	}
	virtual bool doesAccountExist(std::ifstream &inputfile, const int accnum) {

		bool accountExists;
		std::string tmp = "";
		accountExists = false;


		inputfile.open(FILENAME);
		if (inputfile.fail()) { std::cout << "ERROR: NO SUCH FILE" << std::endl; }	//check for failure when opening (i.e no file)
		getline(inputfile, tmp);	//force a getline to set .eof bit

		if (!inputfile.eof()) {
			inputfile.clear();  //clear flags
			inputfile.close(); // close it
			inputfile.open(FILENAME); //reopen

			while (inputfile.good() && !accountExists) {
				GetRecordwc(inputfile);

				//std::cout << "account number for line is: " << account_Number << std::endl;
				//std::cout << "account passed was: " << accnum << std::endl;
				if (account_Number != accnum) {

					accountExists = false;

				}

				else {
					accountExists = true;

				}

			}
		}
		else
		{
			std::cout << "ERROR_dae: FILE EMPTY!" << std::endl;
		}
		inputfile.clear();
		inputfile.close();

		if (accountExists) {

			return true;

		}
		else {
			return false;

		}

	}
};












#endif
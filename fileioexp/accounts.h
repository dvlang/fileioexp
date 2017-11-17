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

	bool accountWithdrawl(double);
	void accountDeposit(double);
	void accountAddInterest();
	
	
	//bool AddRecordwc(std::ofstream&);
	/*
	virtual void GetRecordwc(std::ifstream&) = 0;
	virtual bool FindRecordwClass(Accounts &accref, std::ifstream &inputfile, int tmpAccountNum)=0;
	virtual bool ModifyRecordwc(Accounts &record, std::ofstream&)=0;
	virtual bool doesAccountExist(std::ifstream &inputfile, const int)=0;
	*/
	virtual void GetRecordwc() const = 0;
	virtual bool FindRecordwClass() const = 0;
	virtual bool ModifyRecordwc() const = 0;
	virtual bool doesAccountExist() const = 0;
	virtual void printAccount() const =0;
	virtual bool AddRecordwc() const =0;

protected:
	int account_Number;
	std::string name_Owner;
	double amount_Avail;
	std::string date_Opened;
	std::string account_Type;
	int recordlocator;
	int recordEnd;

};

//------------------------------CHECKING CLASS------------------------------------------------------
class Master :public Accounts {
	//this class exists just to provide access to base class methods and data objects
public:
	~Master() { std::cout << "destroy MASTER" << std::endl; }

	virtual void GetRecordwc(std::ifstream &inputfile) const {
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
	virtual bool doesAccountExist(std::ifstream &inputfile, const int accnum) const  {

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
	virtual bool FindRecordwClass() const { return false; }
	virtual bool ModifyRecordwc() const { return false; }
	virtual void printAccount() const 
	{

		std::cout << account_Type << " \t" << account_Number << "\t\t" << name_Owner << "\t" << "$" << amount_Avail << "\t" << date_Opened << std::endl;
	}

	virtual bool AddRecordwc() const { return false; }
};


//------------------------------CHECKING CLASS------------------------------------------------------
class Checking:public Accounts {

public:
	Checking() :direct_Deposit(false), transaction_Fee(0.0) {}
	~Checking() { std::cout << "destroy Checking" << std::endl; }
	void setDirectdeposit(bool dd) { direct_Deposit = dd; }
	void setTransFee(double transfee) {transaction_Fee = transfee;}

	bool getDirectDeposit() { return direct_Deposit; }
	double getTransFee() { return transaction_Fee; }


	virtual void GetRecordwc(std::ifstream& inputfile)const {
		std::cout << "func: CHECKING GET RECORD " << std::endl;
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
			//std::cout << "input line is: " << wholeentry << std::endl;

			//GET ACCOUNT TYPE
			i = 0;
			while (wholeentry.compare(i, 1, ";") != 0) { i++; }
			accountType = wholeentry.substr(0, i);
			tmpstring.str(accountType);

			tmpstring >> accountType;
			account_Type = accountType;
			//std::cout << "gr_ account type is: " << accountType << std::endl;
			if (account_Type == "Checking") {
				//GET ACCOUNT NUMBER

				i += 2;
				j = i;	//j is placeholder to beginning of next entry

				while (wholeentry.compare(i, 1, ";") != 0) { i++; }
				accountNumber = wholeentry.substr(j, i - j);
				tmpstring.str(accountNumber);

				tmpstring >> account_Number;
				account_Number = std::stoi(accountNumber);
				//std::cout << "gr_ account number is: " << account_Number << std::endl;

				//GET NAME OF THE OWNER
				i += 2;	//move i index off ";" and space
				j = i;	//j is placeholder to beginning of next entry
				while (wholeentry.compare(i, 1, ";") != 0) { i++; }
				accountName = wholeentry.substr(j, i - j);

				name_Owner = accountName;

				//std::cout << "gr_ account name is: " << name_Owner << std::endl;

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
				//std::cout << "gr_ account value is: " << amount_Avail << std::endl;

				//GET DATE ACCOUNT OPENED
				i += 2;	//move i index off ";" and space
				j = i;	//j is placeholder to beginning of next entry
				while (wholeentry.compare(i, 1, ";") != 0) { i++; }
				dateOpened = wholeentry.substr(j, i - j);

				date_Opened = dateOpened;
				//std::cout << "gr_ account opened: " << date_Opened << std::endl;

				tmpstring.clear();
				//GET Direct deposit
				i += 2;	//move i index off ";" and space
				j = i;	//j is placeholder to beginning of next entry
				while (wholeentry.compare(i, 1, ";") != 0) { i++; }
				dd = wholeentry.substr(j, i - j);

				tmpstring.str(dd);
				tmpstring >> std::boolalpha >> direct_Deposit;


				if (direct_Deposit) {
					//direct_Deposit = true;
					//std::cout << "gr_ account direct_Deposit: true " << std::endl;
				}
				else {
					//direct_Deposit = false; 
					//std::cout << "gr_ account direct_Deposit: false " << std::endl;
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
				//std::cout << "gr_ trans fee is: " << transaction_Fee << std::endl;

			}
			// END LINE PARSING	

			return;
		}

	virtual void printAccount()const
	{
			
		std::cout << account_Type << "\t"<<  account_Number << "\t\t" << name_Owner << "\t" << "$" << amount_Avail << "\t" << date_Opened << "\t\t" << direct_Deposit << "\t" <<transaction_Fee << std::endl;
	}

	virtual bool doesAccountExist(std::ifstream &inputfile, const int accnum)const {

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
	
	virtual bool AddRecordwc(std::ofstream &outputfile)const {
		std::ostringstream tmpstring;
		
		outputfile.open(FILENAME, std::ios_base::app);	//open file in append mode
		if (!outputfile.is_open()) { std::cout << "ERROR: NO SUCH FILE" << std::endl; return false; }	//check for failure when opening
		if (outputfile.good()) {

			tmpstring << std::endl << account_Type << "; "<< account_Number << "; " << name_Owner << "; " << amount_Avail << "; " << date_Opened << "; " << std::boolalpha<<direct_Deposit<< "; " << transaction_Fee << "; ";
			outputfile << tmpstring.str();
		}
		else
		{
			outputfile.clear();
			outputfile.close();
			return false;
		}

		outputfile.clear();
		outputfile.close();
		return true;
	}

	virtual bool FindRecordwClass(Checking &accref, std::ifstream &inputfile, int tmpAccountNum)const
	{
		std::cout << "im here in CHECKING find record" << std::endl;
		bool accountExists;
		std::string tmp = "";
		accountExists = false;
		int lengthNotFound = 0;
		int lengthFound = 0;

		inputfile.clear();  //clear flags
		inputfile.open(FILENAME);
		if (inputfile.fail()) { std::cout << "ERROR: NO SUCH FILE" << std::endl; }	//check for failure when opening (i.e no file)
		getline(inputfile, tmp);	//force a getline to set .eof bit

		if (!inputfile.eof()) {
			inputfile.clear();  //clear flags
			inputfile.close(); // close it
			inputfile.open(FILENAME); //reopen

			while (inputfile.good() && !accountExists) {
				GetRecordwc(inputfile);


				if (account_Number != tmpAccountNum) {

					accountExists = false;
					lengthNotFound = inputfile.tellg();
				}

				else {
					accountExists = true;
					if (inputfile.eof()) {	//if we read past end of file, need to go get the location of last ch
						inputfile.clear();  //clear flags
						inputfile.close();	// close it
						inputfile.open(FILENAME); //reopen
						inputfile.seekg(0, inputfile.end);
						lengthFound = inputfile.tellg();
						lengthFound = lengthFound + 2;

					}
					else {
						lengthFound = inputfile.tellg();
					}
				}

			}
		}
		else
		{
			std::cout << "ERROR_frc: FILE EMPTY!" << std::endl;
		}
		inputfile.clear();
		inputfile.close();

		if (accountExists) {
			if (lengthNotFound > 0) {
				recordlocator = lengthNotFound - 2;
				recordEnd = lengthFound - 2;

			//	std::cout << "found it! record locator is: " << recordlocator << " record End is: " << recordEnd << std::endl;
			//	std::cout << "here is the matching account: " << std::endl;
			//	printAccount();
			}
			else {
				recordlocator = 0;
				recordEnd = lengthFound - 2;

			}

			return true;

		}
		else {
			return false;

		}
	}
		
	virtual bool ModifyRecordwc(Checking &record, std::ofstream &outputfile)const {
		std::ostringstream tmpstring;
		std::string tempstring, tempstring2, tmpfilename;
		std::ifstream in_file;
		int endpos;// = 0;
		int opos = 0;
		int result = 0;

		outputfile.precision(10);
		tmpstring.precision(10);

		FindRecordwClass(record, in_file, record.getAccountNumber());

		in_file.open(FILENAME);			//open the input file
		if (in_file.fail()) {
			std::cout << "ERROR: Can't open Input file!" << std::endl;
			result++;
		}

		outputfile.open("tmp.dat");	//open temp output file in new output mode
		if (outputfile.fail()) {
			std::cout << "ERROR: Can't open temp output file!" << std::endl;
			result++;
		}

		in_file.seekg(0, in_file.end);		//find the end of the old file
		endpos = in_file.tellg();				//store end of old file

		in_file.seekg(0, in_file.beg);		//set input file pointer back to beginning
		opos = outputfile.tellp();

		while (in_file.good()) {			//while ur not at the end of the input file

			if (opos == recordlocator) {

				tmpstring << record.getAccountType() << "; " << record.getAccountNumber() << "; " << record.getAccountName() << "; " << record.getAccountValue() << "; " << record.getDateOpened() << "; " << std::boolalpha << record.getDirectDeposit() << "; " << record.getTransFee() << ";";

				outputfile << tmpstring.str();
				in_file.seekg(recordEnd);
				opos = outputfile.tellp();		//find out where in the output file you are now

			}

			getline(in_file, tempstring2);	//get a line from input file	
			outputfile << tempstring2;		//store the line from input file into old 
			opos = outputfile.tellp();		//find out where in the output file you are now

			if (in_file.good()) {
				outputfile << std::endl;			//  add anothe endl
			}
		}

		in_file.clear();
		in_file.close();
		outputfile.clear();
		outputfile.close();

		remove("old.dat");
		rename(&FILENAME[0], "old.dat");	//keep a temp copy of file for safekeeping
		remove(FILENAME);
		result += rename("tmp.dat", &FILENAME[0]);

		if (result != 0) {
			return false;
		}
		else {
			return true;
		}
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
	~Savings() { std::cout << "destroy Savings" << std::endl; }
	void setMatDate(std::string matdate) { maturity_Date = matdate; }
	void setCurInt(double curint) { current_Interest = curint; }
	void setDefInt(double defint) { default_Interest = defint; }

	std::string getMatDate() { return maturity_Date; }
	double getCurInt() { return current_Interest; }
	double getDefInt() { return default_Interest;}
	
	virtual void GetRecordwc(std::ifstream& inputfile)const {
		std::cout << "func: SAVINGS GET RECORD " << std::endl;
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
		//std::cout << "input line is: " << wholeentry << std::endl;

		//GET ACCOUNT TYPE
		i = 0;
		while (wholeentry.compare(i, 1, ";") != 0) { i++; }
		accountType = wholeentry.substr(0, i);
		tmpstring.str(accountType);

		tmpstring >> accountType;
		account_Type = accountType;
		//std::cout << "SAVINGSgr_ account type is: " << account_Type << std::endl;

		if (account_Type == "Savings") {

			//GET ACCOUNT NUMBER

			i += 2;
			j = i;	//j is placeholder to beginning of next entry

			while (wholeentry.compare(i, 1, ";") != 0) { i++; }
			accountNumber = wholeentry.substr(j, i - j);
			tmpstring.str(accountNumber);

			tmpstring >> account_Number;
			account_Number = std::stoi(accountNumber);
			//std::cout << "SAVINGSgr_ account number is: " << account_Number << std::endl;

			//GET NAME OF THE OWNER
			i += 2;	//move i index off ";" and space
			j = i;	//j is placeholder to beginning of next entry
			while (wholeentry.compare(i, 1, ";") != 0) { i++; }
			accountName = wholeentry.substr(j, i - j);

			name_Owner = accountName;

			//std::cout << "SAVINGSgr_ account name is: " << name_Owner << std::endl;

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
			//std::cout << "SAVINGSgr_ account value is: " << amount_Avail << std::endl;

			//GET DATE ACCOUNT OPENED
			i += 2;	//move i index off ";" and space
			j = i;	//j is placeholder to beginning of next entry
			while (wholeentry.compare(i, 1, ";") != 0) { i++; }
			dateOpened = wholeentry.substr(j, i - j);

			date_Opened = dateOpened;
			//std::cout << "SAVINGSgr_ account opened: " << date_Opened << std::endl;

			tmpstring.clear();


			//GET MATURITY DATE
			i += 2;	//move i index off ";" and space
			j = i;	//j is placeholder to beginning of next entry
			while (wholeentry.compare(i, 1, ";") != 0) { i++; }
			maturity_Date = wholeentry.substr(j, i - j);

			//std::cout << "SAVINGSgr_ MATURITY DATE : " << maturity_Date << std::endl;

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
			//std::cout << "SAVINGSgr_ current_Interest value is: " << current_Interest << std::endl;
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
			//std::cout << "SAVINGSgr_ default_Interest value is: " << default_Interest << std::endl;
			tmpstring.clear();


		}
		// END LINE PARSING	

		return;
	}
	virtual void printAccount()const
	{

		std::cout << account_Type << " \t" << account_Number << "\t\t" << name_Owner << "\t" << "$" << amount_Avail << "\t" << date_Opened << "\t" << maturity_Date << "\t" << current_Interest << "\t" << default_Interest << std::endl;
	}

	virtual bool doesAccountExist(std::ifstream &inputfile, const int accnum)const {

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
					//std::cout << "hi sav acc NOT exists" << std::endl;
				}

				else {
					accountExists = true;
					//std::cout << "hi sav acc exists" << std::endl;
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
	virtual bool AddRecordwc(std::ofstream &outputfile)const {
		std::ostringstream tmpstring;

		outputfile.open(FILENAME, std::ios_base::app);	//open file in append mode
		if (!outputfile.is_open()) { std::cout << "ERROR: NO SUCH FILE" << std::endl; return false; }	//check for failure when opening
		if (outputfile.good()) {

			tmpstring << std::endl << account_Type << "; " << account_Number << "; " << name_Owner << "; " << amount_Avail << "; " << date_Opened << "; " << maturity_Date << "; " << current_Interest << "; " << default_Interest << "; ";
			outputfile << tmpstring.str();
		}
		else
		{
			outputfile.clear();
			outputfile.close();
			return false;
		}

		outputfile.clear();
		outputfile.close();
		return true;
	}

	virtual bool FindRecordwClass(Savings &accref, std::ifstream &inputfile, int tmpAccountNum)const
	{
		std::cout << "im here in savings find record" << std::endl;
		bool accountExists;
		std::string tmp = "";
		accountExists = false;
		int lengthNotFound = 0;
		int lengthFound = 0;

		inputfile.clear();  //clear flags
		inputfile.open(FILENAME);
		if (inputfile.fail()) { std::cout << "ERROR: NO SUCH FILE" << std::endl; }	//check for failure when opening (i.e no file)
		getline(inputfile, tmp);	//force a getline to set .eof bit

		if (!inputfile.eof()) {
			inputfile.clear();  //clear flags
			inputfile.close(); // close it
			inputfile.open(FILENAME); //reopen

			while (inputfile.good() && !accountExists) {
				GetRecordwc(inputfile);


				if (account_Number != tmpAccountNum) {

					accountExists = false;
					lengthNotFound = inputfile.tellg();
				}

				else {
					accountExists = true;
					if (inputfile.eof()) {	//if we read past end of file, need to go get the location of last ch
						inputfile.clear();  //clear flags
						inputfile.close();	// close it
						inputfile.open(FILENAME); //reopen
						inputfile.seekg(0, inputfile.end);
						lengthFound = inputfile.tellg();
						lengthFound = lengthFound + 2;

					}
					else {
						lengthFound = inputfile.tellg();
					}
				}

			}
		}
		else
		{
			std::cout << "ERROR_frc: FILE EMPTY!" << std::endl;
		}
		inputfile.clear();
		inputfile.close();

		if (accountExists) {
			if (lengthNotFound > 0) {
				recordlocator = lengthNotFound - 2;
				recordEnd = lengthFound - 2;

				std::cout << "found it! record locator is: " << recordlocator << " record End is: " << recordEnd << std::endl;
				std::cout << "here is the matching account: " << std::endl;
				printAccount();
			}
			else {
				recordlocator = 0;
				recordEnd = lengthFound - 2;
				std::cout << "RECORD FOUND AT 0 " << std::endl;

			}

			return true;

		}
		else {
			return false;
			std::cout << "RECORD NOT FOUND " << std::endl;

		}
	}

	virtual bool ModifyRecordwc(Savings &record, std::ofstream &outputfile)const {
		std::ostringstream tmpstring;
		std::string tempstring, tempstring2, tmpfilename;
		std::ifstream in_file;
		int endpos;// = 0;
		int opos = 0;
		int result = 0;

		outputfile.precision(10);
		tmpstring.precision(10);

		FindRecordwClass(record, in_file, record.getAccountNumber());

		in_file.open(FILENAME);			//open the input file
		if (in_file.fail()) {
			std::cout << "ERROR: Can't open Input file!" << std::endl;
			result++;
		}

		outputfile.open("tmp.dat");	//open temp output file in new output mode
		if (outputfile.fail()) {
			std::cout << "ERROR: Can't open temp output file!" << std::endl;
			result++;
		}

		in_file.seekg(0, in_file.end);		//find the end of the old file
		endpos = in_file.tellg();				//store end of old file

		in_file.seekg(0, in_file.beg);		//set input file pointer back to beginning
		opos = outputfile.tellp();


		while (in_file.good()) {			//while ur not at the end of the input file


			if (opos == recordlocator) {
		
				tmpstring << record.getAccountType() << "; " << record.getAccountNumber() << "; " << record.getAccountName() << "; " << record.getAccountValue() << "; " << record.getDateOpened() << "; " << record.getMatDate() << "; " << record.getCurInt() << "; " << record.getDefInt() << ";";

				outputfile << tmpstring.str();
				in_file.seekg(recordEnd);
				opos = outputfile.tellp();		//find out where in the output file you are now

			}


			getline(in_file, tempstring2);	//get a line from input file	
			outputfile << tempstring2;		//store the line from input file into old 
			opos = outputfile.tellp();		//find out where in the output file you are now


			if (in_file.good()) {
				outputfile << std::endl;			//  add anothe endl
			}
		}

		in_file.clear();
		in_file.close();
		outputfile.clear();
		outputfile.close();

		remove("old.dat");
		rename(&FILENAME[0], "old.dat");	//keep a temp copy of file for safekeeping
		remove(FILENAME);
		result += rename("tmp.dat", &FILENAME[0]);



		if (result != 0) {
			return false;
		}
		else {
			return true;
		}
	}



private:
	std::string maturity_Date;
	double current_Interest;
	double default_Interest;

};





#endif
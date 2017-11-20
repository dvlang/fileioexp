// fileioexp.cpp : 
//
// Author: Dan Lang 
// Date: 11/18/2017
// Class: cs475
// Assignment: project 2,2.5
//
//  This program simulates a simple bank database transaction program
//

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>

using namespace std;


#include "fileioexp.h"
#include "accounts.h"
#include "checking.h"
#include "savings.h"
#include "master.h"
#include "menu.h"
#include <time.h>


char userselection = 'H';
char userSubselection = 'E';

istringstream tmpstring;
bool accountExists;
double tmpTransAmt;
int tmpTransAccount;

int tmpacctnumber;

bool transactionResult;
std::string tmpaccttype;

string date;
string mo;
string day;
string yr;

bool needtoupdate;
int numofaccts;

int i;


//--------------------BEGIN MAIN--------------------------------------
int main()
{

	//time functions
	time_t timer;
	time(&timer);
	struct tm* brokentime = localtime(&timer);

	tmpstring.precision(10);
	ifstream in_file;
	ofstream out_file;

	Checking checkingAccount;
	Checking curUserCheckingAcct;
	Savings savingsAccount;
	Savings curUserSavAcct;
	Master allAccounts;

	Menu systemMenu;


	//set date string
	date = std::to_string((brokentime->tm_mon) + 1) + "/" + std::to_string(brokentime->tm_mday) + "/" + std::to_string((brokentime->tm_year) + 1900);
	mo = std::to_string((brokentime->tm_mon) + 1);
	day = std::to_string(brokentime->tm_mday);
	yr = std::to_string((brokentime->tm_year) + 1900);
	

	//AUTOMATICALLY ASSESS INTEREST ON FILE IF TODAY IS A NEW DAY.  ASSUME THIS IS RUN EVERY DAY.
	needtoupdate = checkDate(mo, day, yr, date);
	if (needtoupdate) {
		numofaccts = countAccounts(in_file);
		int *acctarray = new int[numofaccts];


		getAllAcctNums(allAccounts, in_file, acctarray);
		
		updateInterestAllAccounts(allAccounts, curUserCheckingAcct, checkingAccount, curUserSavAcct, savingsAccount, in_file, out_file, acctarray, numofaccts);
		std::cout << "Interest Assessed." << std::endl;
	}



	//print out a the welcome header
	systemMenu.printHeader(date);

	while (userselection != 'Q') {

		//MENU / USER INTERFACE
		systemMenu.printMenu();

		userselection = systemMenu.getUserSelection();

		switch (userselection)
		{

		case 'I':	//-------------------USER INSERT OPTION-------------------------

			accountExists = true;

			std::cout << "CREATE NEW ACCOUNT" << std::endl;

			//get user account type here
			tmpaccttype = systemMenu.getAccountType();//user account type 

			if (tmpaccttype == "Checking") {

				while (accountExists) {
					tmpacctnumber = systemMenu.getDesiredAcctNum();

					//check to see if account number already exists, if it does stay here till they give you a good one
					accountExists = checkingAccount.doesAccountExist(in_file, tmpacctnumber);
					if (accountExists) { std::cout << "Account already exists, choose another. " << std::endl; }

				}
				checkingAccount.setAccountType(tmpaccttype);
				checkingAccount.setAccountNumber(tmpacctnumber);
				checkingAccount.setAccountName(systemMenu.getUserName());
				checkingAccount.setAccountValue(systemMenu.getUserAmount());

				std::cout << "Enable Direct Deposit? y/n: ";
				userselection = systemMenu.getUserSelection();
				if (userselection == 'y') {
					checkingAccount.setDirectdeposit(true);
					checkingAccount.setTransFee(0.0);
				}
				else {
					checkingAccount.setDirectdeposit(false);
					checkingAccount.setTransFee(3.5);
				}
				checkingAccount.setDateOpened(date);
				checkingAccount.AddRecordwc(out_file);
			}
			else if (tmpaccttype == "Savings") {

				while (accountExists) {
					tmpacctnumber = systemMenu.getDesiredAcctNum();

					//check to see if account number already exists, if it does stay here till they give you a good one
					accountExists = checkingAccount.doesAccountExist(in_file, tmpacctnumber);

				}
				savingsAccount.setAccountType(tmpaccttype);
				savingsAccount.setAccountNumber(tmpacctnumber);
				savingsAccount.setAccountName(systemMenu.getUserName());
				savingsAccount.setAccountValue(systemMenu.getUserAmount());

				std::cout << "Enter Maturity Date? (MM/DD/YYYY)";
				savingsAccount.setMatDate(systemMenu.getUserName());//not techically a username, but it returns a non-zero string so i'll resuse it
				std::cout << "Enter Current Interest Rate ";
				savingsAccount.setCurInt(systemMenu.getUserAmount()); //again, not technically following name inferred function, but it will work
				std::cout << "Enter Default Interest Rate ";
				savingsAccount.setDefInt(systemMenu.getUserAmount()); //again, not technically following name inferred function, but it will work
				savingsAccount.setDateOpened(date);

				savingsAccount.AddRecordwc(out_file);
			}

			else {
				std::cout << "invalid acct type requested" << std::endl;
			}

			break;

		case 'M':	//-------------------USER MODIFY OPTION-------------------------


			accountExists = false;
			cout << "MODIFY AN ACCOUNT" << endl;

			while (!accountExists) {
				tmpacctnumber = systemMenu.getDesiredAcctNum();

				//check to see if account number already exists, if it does stay here till they give you a good one
				accountExists = allAccounts.doesAccountExist(in_file, tmpacctnumber);

				if (!accountExists) { std::cout << "Account doesn't exists, choose another. " << std::endl; }
				else { tmpaccttype = allAccounts.getAccountType(); }

			}

			if (tmpaccttype == "Checking") {

				accountExists = curUserCheckingAcct.doesAccountExist(in_file, tmpacctnumber); //dont really care abut rtrn value, just using to populate the class
				curUserCheckingAcct.printAccount();

				systemMenu.printModifyBaseAccountMenu();
				userSubselection = systemMenu.getUserSelection();

				switch (userSubselection)
				{
				case 'C':	//-------------------USER CHANGE NAME OPTION-------------------------

					cout << "CHANGE NAME: " << endl;
					curUserCheckingAcct.setAccountName(systemMenu.getUserName());

					break;
				case 'W':	//-------------------USER WITHDRAWL OPTION-------------------------

					cout << "WITHDRAWL: " << endl;
					tmpTransAmt = systemMenu.getUserAmount();
					transactionResult = curUserCheckingAcct.accountWithdrawl(tmpTransAmt);

					if (!transactionResult) {
						cout << "ERROR: Insufficient funds!- Exiting" << endl;
					}
					curUserCheckingAcct.printAccount();

					break;

				case 'D':	//-------------------USER DEPOSIT OPTION-------------------------
					cout << "DEPOSIT: " << endl;

					tmpTransAmt = systemMenu.getUserAmount();
					curUserCheckingAcct.accountDeposit(tmpTransAmt);
					curUserCheckingAcct.printAccount();

					break;

				case 'P':	//-------------------USER ADD INTEREST OPTION-------------------------
					//--my assumption is that some batch file would executre the 'P' function on all the accounts, I did not implement automatic functionality
					curUserCheckingAcct.accountAddInterest();
					curUserCheckingAcct.printAccount();
					break;

				case 'E':	//-------------------USER EXIT OPTION-------------------------
					cout << "-Exit" << endl; userselection = 'H';
					break;

				default:
					cout << "ERROR: INVALID Selection!" << endl;
					break;

				}
				if (userSubselection == 'C' || userSubselection == 'D' || userSubselection == 'W') {

					bool saveok;

					curUserCheckingAcct.assessCheckingTransFee();
					saveok = checkingAccount.ModifyRecordwc(curUserCheckingAcct, out_file);

					if (!saveok) { cout << "the file was NOT saved ok" << endl; }

				}
				else if (userSubselection == 'P') {	//i don't penalize the user with a transaction fee when the interest is calculated

					bool saveok;

					saveok = checkingAccount.ModifyRecordwc(curUserCheckingAcct, out_file);

					if (!saveok) { cout << "the file was NOT saved ok" << endl; }
				}

			}//end if tmpacctype=checking

			else if (tmpaccttype == "Savings") {

				accountExists = curUserSavAcct.doesAccountExist(in_file, tmpacctnumber); //dont really care abut rtrn value, just using to populate the class
				curUserSavAcct.printAccount();

				systemMenu.printModifyBaseAccountMenu();
				userSubselection = systemMenu.getUserSelection();

				switch (userSubselection)
				{
				case 'C':	//-------------------USER CHANGE NAME OPTION-------------------------

					cout << "CHANGE NAME: " << endl;
					curUserSavAcct.setAccountName(systemMenu.getUserName());

					break;
				case 'W':	//-------------------USER WITHDRAWL OPTION-------------------------

					cout << "WITHDRAWL: " << endl;

					if (curUserSavAcct.MatDateMet()) {

						tmpTransAmt = systemMenu.getUserAmount();
						transactionResult = curUserSavAcct.accountWithdrawl(tmpTransAmt);
					}
					if (!transactionResult || !(curUserSavAcct.MatDateMet())) {
						cout << " ERROR: Withdrawl Denied- Exiting" << endl;
					}

					break;

				case 'D':	//-------------------USER DEPOSIT OPTION-------------------------
					cout << "DEPOSIT: " << endl;

					tmpTransAmt = systemMenu.getUserAmount();
					curUserSavAcct.accountDeposit(tmpTransAmt);
					curUserSavAcct.printAccount();
					break;

				case 'P':	//-------------------USER ADD INTEREST OPTION-------------------------
							//--my assumption is that some batch file would executre the 'P' function on all the accounts, I did not implement automatic functionality
					curUserSavAcct.accountAddInterest();
					curUserSavAcct.printAccount();

					break;

				case 'E':	//-------------------USER EXIT OPTION-------------------------
					cout << "-Exit" << endl; userselection = 'H';
					break;

				default:
					cout << "ERROR: INVALID Selection!" << endl;
					break;

				}
				if (userSubselection == 'C' || userSubselection == 'D' || userSubselection == 'W' || userSubselection == 'P') {

					bool saveok;
					saveok = savingsAccount.ModifyRecordwc(curUserSavAcct, out_file);
					if (!saveok) { cout << "the file was NOT saved ok" << endl; }
				}
			}

			break;

		case 'V':	//-------------------USER VIEW ALL OPTION-------------------------

			systemMenu.printViewAllMenu();

			printAllAccounts(checkingAccount, savingsAccount, in_file);

			break;
			//-------------------USER QUIT OPTION-------------------------
		case 'Q':  cout << "user selected Q" << endl; break;

			//-------------------DEFAULT OPTION-------------------------
		default: cout << "ERROR: INVALID Selection!" << endl;
		}

	}


	return 0;
}//--------------------END MAIN--------------------------------------




//--------------------FUNCTIONS STILL IN FILEIOEXP-----------------------------------
//-----------------------------------------------------------------------------------


//--------------------FUNCTION: PRINTALLACCOUNTS-------------------------------------
//--THIS FUNCTION WILL DETERMINE TYPE AND CALL THE APPROPRIATE CLASS FUNCTIONS
//These are left here because they are really independent of checking and savigns class functions.
//could have considered adding to the "master" class to cover the printing function of all records.
void printAllAccounts(Checking &checkingAcct, Savings &savAccount, std::ifstream &inputfile) {
	std::string tmp = "";
	std::string accounttype;


	inputfile.open(FILENAME);
	if (inputfile.fail()) { std::cout << "ERROR: NO SUCH FILE" << std::endl; }	//check for failure when opening
	getline(inputfile, tmp);	//force a getline to set .eof bit

	if (!inputfile.eof()) {
		inputfile.clear();  //clear flags
		inputfile.close(); // close it

		inputfile.open(FILENAME);
		while (inputfile.good()) {

			accounttype = getAccountType(inputfile);


			if (accounttype == "Checking") {
				//This needs to get converted to a call to the appropriate class function based on account type
				checkingAcct.GetRecordwc(inputfile);
				checkingAcct.printAccount();
				//id assess fee here, would need to add ofstream
			}
			else if (accounttype == "Savings") {
				//This needs to get converted to a call to the appropriate class function based on account type
				savAccount.GetRecordwc(inputfile);
				savAccount.printAccount();

			}
			else { std::cout << "ERROR: invalid account type found!" << std::endl; }


		}
	}
	else
	{
		std::cout << "ERROR_paa: FILE EMPTY!" << std::endl;
	}
	inputfile.clear();
	inputfile.close();
}
//--------------------end FUNCTION: PRINTALLACCOUNTS-------------------------------------

//--------------------FUNCTION: getAccountType-------------------------------------
std::string getAccountType(std::ifstream &inputfile) {
	std::istringstream tmpstring;
	std::string wholeentry;
	std::string accountType;
	int currentpos;

	int i, j;
	tmpstring.clear();

	currentpos = inputfile.tellg();  //get the current position in the file

	getline(inputfile, wholeentry);

	i = 0;
	while (wholeentry.compare(i, 1, ";") != 0) { i++; }
	accountType = wholeentry.substr(0, i);

	inputfile.seekg(currentpos);  //set the file pointer back to where we were

	return accountType;
}


//--------------------FUNCTION: PRINTALLACCOUNTS-------------------------------------
//--THIS FUNCTION WILL DETERMINE TYPE AND CALL THE APPROPRIATE CLASS FUNCTIONS
//These are left here because they are really independent of checking and savigns class functions.
//could have considered adding to the "master" class to cover the printing function of all records.
bool checkDate(std::string month, std::string day, std::string year, std::string date) {
	std::string tmp = "";
	std::ostringstream tmpstring;
	std::string accounttype;
	std::string parmonth;
	std::string parday;
	std::string paryear;

	ifstream in_file;
	ofstream out_file;

	cout << "todays date is: " << month << day << year << endl;


	in_file.open("date.dat");


	getline(in_file, tmp);


	in_file.clear();
	in_file.close();

	out_file.open("date.dat");
	tmpstring << date;

	out_file << tmpstring.str();
	out_file.clear();
	out_file.close();


	cout << "file date is: " << tmp << endl;
	//parse the maturity date from the data record
	int i, j;
	i = 0;
	while (tmp.compare(i, 1, "/") != 0) { i++; }
	parmonth = tmp.substr(0, i);

	i += 1;	//move i index off ";" and space
	j = i;	//j is placeholder to beginning of next entry
	while (tmp.compare(i, 1, "/") != 0) { i++; }
	parday = tmp.substr(j, i - j);

	i += 1;	//move i index off ";" and space
	j = i;	//j is placeholder to beginning of next entry
	while (i < tmp.size()) { i++; }
	paryear = tmp.substr(j, i - j);

	if (paryear <= year && parmonth <= month && parday <= day) { return true; }
	else {
		return false;
	}




}


//--------------------end FUNCTION: PRINTALLACCOUNTS-------------------------------------


void updateInterestAllAccounts(Master &allAccounts, Checking &curusercheckingAcct, Checking &checkingAcct, Savings &curusersavAccount, Savings &savAccount, std::ifstream &inputfile, std::ofstream &outfile, int *arryptr, int numrecords) {
	bool accountExists;
	std::string tmpaccttype;

	for (int i = 0; i < numrecords; i++) {
		accountExists = allAccounts.doesAccountExist(inputfile, arryptr[i]);

		tmpaccttype = allAccounts.getAccountType();

		if (tmpaccttype == "Checking") {
			//This needs to get converted to a call to the appropriate class function based on account type
			accountExists = curusercheckingAcct.doesAccountExist(inputfile, arryptr[i]); //dont really care abut rtrn value, just using to populate the class
			curusercheckingAcct.accountAddInterest();
			checkingAcct.ModifyRecordwc(curusercheckingAcct, outfile);

		}
		else if (tmpaccttype == "Savings") {
			//This needs to get converted to a call to the appropriate class function based on account type
			accountExists = curusersavAccount.doesAccountExist(inputfile, arryptr[i]); //dont really care abut rtrn value, just using to populate the class
			curusersavAccount.accountAddInterest();
			savAccount.ModifyRecordwc(curusersavAccount, outfile);


		}
	}

}


//--------------------FUNCTION: countAccounts-------------------------------------
//--count the number of accounts

int countAccounts(std::ifstream &inputfile) {
	std::string tmp = "";
	std::string accounttype;
	int numofaccts = 0;

	inputfile.open(FILENAME);
	if (inputfile.fail()) { std::cout << "ERROR: NO SUCH FILE" << std::endl; }	//check for failure when opening
	getline(inputfile, tmp);	//force a getline to set .eof bit

	if (!inputfile.eof()) {
		inputfile.clear();  //clear flags
		inputfile.close(); // close it

		inputfile.open(FILENAME);
		while (inputfile.good()) {

			getline(inputfile, tmp);


			numofaccts++;


		}
	}
	else
	{
		std::cout << "ERROR_paa: FILE EMPTY!" << std::endl;
	}
	inputfile.clear();
	inputfile.close();
	return numofaccts;
}


void getAllAcctNums(Master &allAccounts, std::ifstream &inputfile, int *arryptr) {
	std::string tmp = "";
	std::string accounttype;
	int acctnum;
	int i = 0;

	inputfile.open(FILENAME);
	if (inputfile.fail()) { std::cout << "ERROR: NO SUCH FILE" << std::endl; }	//check for failure when opening
	getline(inputfile, tmp);	//force a getline to set .eof bit

	if (!inputfile.eof()) {
		inputfile.clear();  //clear flags
		inputfile.close(); // close it

		inputfile.open(FILENAME);
		while (inputfile.good()) {

			allAccounts.GetRecordwc(inputfile);
			acctnum = allAccounts.getAccountNumber();

			arryptr[i] = allAccounts.getAccountNumber();
			i++;

		}
	}
	else
	{
		std::cout << "ERROR_paa: FILE EMPTY!" << std::endl;
	}
	inputfile.clear();
	inputfile.close();
}


// fileioexp.cpp : 
//
// Author: Dan Lang 
// Date: 10/12/2017
// Class: cs475
// Assignment: project 1
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
#include "menu.h"
#include <time.h>


char userselection = 'H';
char userSubselection = 'E';
string firstname;
string lastname;
string tmp = "";
istringstream tmpstring;
bool accountExists;
double tmpTransAmt;
int tmpTransAccount;
int recordlocator;
int recordEnd;
bool accountnumgood;
int tmpaccountlength;
bool lengthgood;
int size;
int tmpacctnumber;
double tmpacctval;
bool transactionResult;
std::string tmpaccttype;

string date;


//--------------------BEGIN MAIN--------------------------------------
int main()
{

	//time functions
	time_t timer;
	time(&timer);
	struct tm* brokentime = localtime(&timer);


	//accountStruct AccountRecord;
	//accountStruct tmpAccount;
	tmpstring.precision(10);
	ifstream in_file;
	ofstream out_file;

	//Accounts userAccount;
	//Accounts tmpUserAccount;
	Checking checkingAccount;
	Savings savingsAccount;

	Menu systemMenu;

	
	//set date string
	date = std::to_string(brokentime->tm_mon) + "/" + std::to_string(brokentime->tm_mday) + "/" + std::to_string((brokentime->tm_year) + 1900);


	//print out a the welcome header
	systemMenu.printHeader(date);

	while (userselection != 'Q') {

		//MENU / USER INTERFACE
		systemMenu.printMenu();

		userselection= systemMenu.getUserSelection();

		switch (userselection)
		{


		case 'I':	//-------------------USER INSERT OPTION-------------------------
			recordlocator = 0;
			accountExists = true;
			accountnumgood = false;
			lengthgood = false;
			

			std::cout << "CREATE NEW ACCOUNT" << std::endl;

			//get user account type here
			tmpaccttype=systemMenu.getAccountType();//user account type 

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


				savingsAccount.AddRecordwc(out_file);
			}
			//tmpUserAccount.AddRecordwc(out_file);
			else {
				std::cout << "invalid acct type requested" << std::endl;
			}

			break;

		case 'M':	//-------------------USER MODIFY OPTION-------------------------
			/*tmpstring.clear();
			recordlocator = 0;
			accountExists = false;
			accountnumgood = false;
			tmpaccountlength = 0;

			cout << "MODIFY AN ACCOUNT" << endl;
			

				while (!accountExists) {
					tmpacctnumber = systemMenu.getDesiredAcctNum();

					//check to see if account number already exists, if it does stay here till they give you a good one
					accountExists = tmpUserAccount.doesAccountExist(in_file, tmpacctnumber);

				}

				if (accountExists) {

					systemMenu.printViewAllMenu();
					tmpUserAccount.printAccount();

					systemMenu.printModifyBaseAccountMenu();
					userSubselection = systemMenu.getUserSelection();
					

					switch (userSubselection)
					{
					case 'C':	//-------------------USER CHANGE NAME OPTION-------------------------
						
						cout << "CHANGE NAME: " << endl;
						
							tmpUserAccount.setAccountName(systemMenu.getUserName());

						break;
					case 'W':	//-------------------USER WITHDRAWL OPTION-------------------------

						cout << "WITHDRAWL: " << endl;
												
						tmpTransAmt = systemMenu.getUserAmount();
						
						transactionResult=tmpUserAccount.accountWithdrawl(tmpTransAmt);
						
						if (!transactionResult) {
							cout << "ERROR: Insufficient funds!- Exiting" << endl;
						}
						tmpUserAccount.printAccount();

						break;

					case 'D':	//-------------------USER DEPOSIT OPTION-------------------------
						cout << "DEPOSIT: " << endl;
					
						tmpTransAmt = systemMenu.getUserAmount();
						
						tmpUserAccount.accountDeposit(tmpTransAmt);

						tmpUserAccount.printAccount();


						break;

					case 'P':	//-------------------USER ADD INTEREST OPTION-------------------------

						tmpUserAccount.accountAddInterest();
						tmpUserAccount.printAccount();
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
						saveok= userAccount.ModifyRecordwc(tmpUserAccount, out_file);
						if (!saveok) {cout << "the file was NOT saved ok" << endl;}


					}
				}
			
			else {
				cout << "ERROR:Invalid Account Number Entered!" << endl << endl;
			}
			*/
			break;

		case 'V':	//-------------------USER VIEW ALL OPTION-------------------------
			
			systemMenu.printViewAllMenu();
			//tmpUserAccount.printAllAccounts(in_file);  //does this break requirement for all users to get pulled into their own account object???????????????
			
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
//--THIS FUNCTION WILL DETERMINE TYPE AN CALL THE APPROPRIATE CLASS FUNCTIONS
void printAllAccounts(Checking &checkingAcct, Savings &savAccount, std::ifstream &inputfile) {
	std::string tmp = "";
	std::string accounttype;

	//std::cout << "hi, im in my new print all function" << std::endl;

	inputfile.open(FILENAME);
	if (inputfile.fail()) { std::cout << "ERROR: NO SUCH FILE" << std::endl; }	//check for failure when opening
	getline(inputfile, tmp);	//force a getline to set .eof bit

	if (!inputfile.eof()) {
		inputfile.clear();  //clear flags
		inputfile.close(); // close it

		inputfile.open(FILENAME);
		while (inputfile.good()) {

			accounttype = getAccountType(inputfile);
		//	std::cout << "paa_ account type is: " << accounttype << std::endl;

			if (accounttype == "Checking") {
				//This needs to get converted to a call to the appropriate class function based on account type
				checkingAcct.GetRecordwc(inputfile);
				checkingAcct.printAccount();
			}
			else if(accounttype=="Savings"){
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
	//std::cout << "ga_input line is: " << wholeentry << std::endl;

	i = 0;
	while (wholeentry.compare(i, 1, ";") != 0) { i++; }
	accountType = wholeentry.substr(0, i);

	//std::cout << "ga_ account type is: " << accountType << std::endl;

	inputfile.seekg(currentpos);  //set the file pointer back to where we were

	return accountType;
}
//--------------------end  FUNCTION: getAccountType-------------------------------------
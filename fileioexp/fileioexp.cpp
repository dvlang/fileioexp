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

	Accounts userAccount;
	Accounts tmpUserAccount;
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

			while (accountExists) {
				tmpacctnumber = systemMenu.getDesiredAcctNum();

				//check to see if account number already exists, if it does stay here till they give you a good one
				accountExists = tmpUserAccount.doesAccountExist(in_file, tmpacctnumber);  
				
			}
			tmpUserAccount.setAccountNumber(tmpacctnumber);
			
			tmpUserAccount.setAccountName(systemMenu.getUserName());
									
			tmpUserAccount.setAccountValue(systemMenu.getUserAmount());

						
			//input data good, commit record
			tmpUserAccount.AddRecordwc(out_file);


			break;

		case 'M':	//-------------------USER MODIFY OPTION-------------------------
			tmpstring.clear();
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

						//userAccount.setAccountValue(userAccount.getAccountValue() *(1.0 + INTERESTRATE));
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
			//}
			else {
				cout << "ERROR:Invalid Account Number Entered!" << endl << endl;
			}

			break;

		case 'V':	//-------------------USER VIEW ALL OPTION-------------------------
			
			systemMenu.printViewAllMenu();
			
			tmpUserAccount.printAllAccounts(in_file);  //does this break requirement for all users to get pulled into their own account object???????????????
			

			break;
			//-------------------USER QUIT OPTION-------------------------
		case 'Q':  cout << "user selected Q" << endl; break;

			//-------------------DEFAULT OPTION-------------------------
		default: cout << "ERROR: INVALID Selection!" << endl;
		}

	}


	return 0;
}//--------------------END MAIN--------------------------------------



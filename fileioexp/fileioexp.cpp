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

//--------------------BEGIN MAIN--------------------------------------
int main()
{
	accountStruct AccountRecord;
	accountStruct tmpAccount;
	tmpstring.precision(10);
	ifstream in_file;
	ofstream out_file;

	Accounts userAccount;
	Accounts tmpUserAccount;
	
/*int tmpAcctnum;
	string tmpAcctname;
	double tmpAcctval;

	for (int i = 0; i <=1; i++) {
		cout << "give me an account number" << endl;
		getline(cin, tmp);
		tmpstring.clear();
		tmpstring.str(tmp);
		tmpstring >> tmpAcctnum;

		manyUserAccounts[i].setAccountNumber(tmpAcctnum);
		cout << "give me an account name" << endl;

		getline(cin, tmp);
		tmpstring.clear();
		tmpstring.str(tmp);
		tmpstring >> tmpAcctname;

		manyUserAccounts[i].setAccountName(tmpAcctname);
		cout << "give me an account value "<< endl;

		getline(cin, tmp);
		tmpstring.clear();
		tmpstring.str(tmp);
		tmpstring >> tmpAcctval;
		manyUserAccounts[i].setAccountValue(tmpAcctval);
		
		cout << "I entered this: " << endl;
		manyUserAccounts[i].printAccount();

	}
	cout <<endl<< "Reprint all: " << endl;
	for (int i = 0; i <=1; i++) {
		manyUserAccounts[i].printAccount();
	}

	cout << "I should have printed many accounts before this..." << endl;
	*/

	cout << "WELCOME TO THE ACCOUNTS MANAGER" << endl << endl;

	while (userselection != 'Q') {

		//MENU / USER INTERFACE
		cout << endl;
		cout << "************************************************" << endl;
		cout << "Please select from one of the following options:" << endl << endl;
		cout << "Press ""I"" to insert a new account record" << endl;
		cout << "Press ""M"" to modify an existing record" << endl;
		cout << "Press ""V"" to view all account records" << endl;
		cout << "Press ""Q"" to quit" << endl;
		cout << "************************************************" << endl;
		cout << "Entry -> ";


		getline(cin, tmp);
		userselection = tmp[0];


		switch (userselection)
		{


		case 'I':	//-------------------USER INSERT OPTION-------------------------
			recordlocator = 0;
			accountExists = false;
			accountnumgood = false;
			lengthgood = false;

			tmpstring.clear();

			//Get desired account number
			cout << "CREATE NEW ACCOUNT" << endl;
			cout << "Desired account number (6digits): " << endl;
			getline(cin, tmp);
			tmpstring.str(tmp);

			//check to make sure the account number is valid length, if it is then make sure a ACCOUNTLENGTH number
			accountnumgood = CheckLength(tmpstring, ACCOUNTLENGTH);
			if (accountnumgood) { accountnumgood = IsNumber(tmp, ACCOUNTLENGTH); }

			while (!accountnumgood) {
				tmpstring.clear();
				cout << "ERROR: Bad Length or Value, Enter NEW Desired account number (6digits): " << endl;
				getline(cin, tmp);
				tmpstring.str(tmp);

				//check to make sure the account number is valid length, if it is then make sure a ACCOUNTLENGTH number
				accountnumgood = CheckLength(tmpstring, ACCOUNTLENGTH);
				if (accountnumgood) { accountnumgood = IsNumber(tmp, ACCOUNTLENGTH); }
			}

			//tmpstring >> tmpAccount.account_Number;
			int tmpacctnumber;
			double tmpacctval;
			tmpstring >> tmpacctnumber;
			tmpUserAccount.setAccountNumber(tmpacctnumber);

			cout <<"here's the value I took in: "<< tmpUserAccount.getAccountNumber() << endl;


			//check to see if account number already exists, if it does stay here till they give you a good one
			//accountExists = FindRecord(AccountRecord, in_file, tmpAccount.account_Number, &recordlocator, &recordEnd);
			accountExists = FindRecordwClass(userAccount, in_file, tmpUserAccount.getAccountNumber(), &recordlocator, &recordEnd);

			while (accountExists || !accountnumgood) {
				tmpstring.clear();
				if (accountExists) { cout << "ERROR: Account Exists, Enter NEW Desired account number (6digits): " << endl; }
				if (!accountnumgood) { cout << "ERROR: Bad Length or Value, Enter NEW Desired account number (6digits): " << endl; }
				getline(cin, tmp);
				tmpstring.str(tmp);
				//check to make sure the account number is valid length, if it is then make sure a ACCOUNTLENGTH number
				accountnumgood = CheckLength(tmpstring, ACCOUNTLENGTH);
				if (accountnumgood) { accountnumgood = IsNumber(tmp, ACCOUNTLENGTH); }

				//if its a good account number, then create an account
				if (accountnumgood) {
					//tmpstring >> tmpAccount.account_Number;
					tmpstring >> tmpacctnumber;
					tmpUserAccount.setAccountNumber(tmpacctnumber);
					//accountExists = FindRecord(AccountRecord, in_file, tmpAccount.account_Number, &recordlocator, &recordEnd);
					accountExists = FindRecordwClass(userAccount, in_file, tmpUserAccount.getAccountNumber(), &recordlocator, &recordEnd);
				}
				else {
					accountExists = false;
				}

			}

			//Get user acccount name
			cout << "Desired Account Holder Name: " << endl;
			getline(cin, tmp);
			tmpstring.str(tmp);

			//check to see if they field was empty, if it was, stay here till they give you a good one
			lengthgood = CheckEmpty(tmpstring);

			//make sure the user didnt enter an empty value
			while (!lengthgood) {
				cout << "ERROR: Account Holder Name Can't Be Empty: " << endl;
				getline(cin, tmp);
				tmpstring.str(tmp);
				lengthgood = CheckEmpty(tmpstring);
			}
			tmpAccount.name_Owner = tmp;
			tmpUserAccount.setAccountName(tmp);

			//check to see if they field was empty, if it was, set account value to 0
			cout << "Desired Initial Value (00.00 format): " << endl;
			getline(cin, tmp);
			tmpstring.clear();
			tmpstring.str(tmp);

			//make sure the user didnt enter an empty value
			lengthgood = CheckEmpty(tmpstring);
			if (lengthgood) {
				//tmpstring >> tmpAccount.amount_Avail;
				tmpstring >> tmpacctval;
				cout << "the tmp string is" << tmpacctval;
				tmpUserAccount.setAccountValue(tmpacctval);
			}
			else {
				tmpAccount.amount_Avail = 0.00;
				tmpUserAccount.setAccountValue(0.00);
			}
			cout << "print tmpUserAccount before committing" << endl;
			tmpUserAccount.printAccount();
			//input data good, commit record
			//AddRecord(tmpAccount, out_file);
			AddRecordwc(tmpUserAccount, out_file);

			break;

		case 'M':	//-------------------USER MODIFY OPTION-------------------------
			tmpstring.clear();
			recordlocator = 0;
			accountExists = false;
			accountnumgood = false;
			tmpaccountlength = 0;

			cout << "MODIFY AN ACCOUNT" << endl;
			cout << "Account Number to Modify" << endl;
			getline(cin, tmp);
			tmpstring.str(tmp);

			accountnumgood = CheckLength(tmpstring, ACCOUNTLENGTH);
			tmpstring >> tmpTransAccount;
			tmpUserAccount.setAccountNumber(tmpTransAccount);

			if (accountnumgood) {
				accountExists = FindRecordwClass(userAccount, in_file, tmpUserAccount.getAccountNumber(), &recordlocator, &recordEnd);


				if (accountExists) {
					cout << endl << "--------------------Account Information-----------------------" << endl;
					cout << "Account Number" << "\t\t" << "Account Name" << "\t" << "Account Value " << endl;
					cout << "--------------" << "\t\t" << "------------" << "\t" << "-------------" << endl;
					//cout << userAccount.getAccountNumber()<< "\t\t\t" << userAccount.getAccountName() << "\t" << userAccount.getAccountValue() << endl;
					userAccount.printAccount();
				}
				else
				{
					cout << "ERROR: Account Not Found!!!" << endl << endl;
				}
				if (accountExists) {

					cout << endl << "SELECT ACTION" << endl;
					cout << "Press C to Change Name on account record" << endl;
					cout << "Press W to perform a withdrawl" << endl;
					cout << "Press D to make a deposit" << endl;
					cout << "Press P to factor in interest" << endl;
					cout << "Press E to Exit" << endl;
					getline(cin, tmp);
					userSubselection = tmp[0];

					switch (userSubselection)
					{
					case 'C':	//-------------------USER CHANGE NAME OPTION-------------------------
						cout << "CHANGE NAME: " << endl;
						cout << "What is new Name: " << endl;
						getline(cin, tmp);
						tmpstring.str(tmp);

						//check to see if they field was empty, if it was, stay here till they give you a good one
						lengthgood = CheckEmpty(tmpstring);

						if (!lengthgood) {
							cout << "ERROR: Account Holder Name Can't Be Empty- Exiting" << endl << endl;
						}
						else {
							userAccount.setAccountName(tmp);
						}

						break;
					case 'W':	//-------------------USER WITHDRAWL OPTION-------------------------
						cout << "WITHDRAWL: " << endl;
						cout << "How Much: " << endl;
						getline(cin, tmp);
						tmpstring.clear();
						tmpstring.str(tmp);
						tmpstring >> tmpTransAmt;


						if (!tmpstring.fail()) {	//convertion to int didnt fail
							if (userAccount.getAccountValue() >= tmpTransAmt) {
								//AccountRecord.amount_Avail = AccountRecord.amount_Avail - tmpTransAmt;
								userAccount.setAccountValue(userAccount.getAccountValue() - tmpTransAmt);
							}
							else {
								cout << "ERROR: Insufficient funds!- Exiting" << endl;
							}

						}
						else
						{
							cout << "ERROR: Withdrawl amount not a number" << endl;
						}

						break;

					case 'D':	//-------------------USER DEPOSIT OPTION-------------------------
						cout << "DEPOSIT: " << endl;
						cout << "How Much (00.00 format):  " << endl;
						getline(cin, tmp);
						tmpstring.clear();
						tmpstring.str(tmp);

						lengthgood = CheckEmpty(tmpstring);

						tmpstring >> tmpTransAmt;

						if (!tmpstring.fail()) {	//convertion to int didnt fail
							//AccountRecord.amount_Avail = AccountRecord.amount_Avail + tmpTransAmt;
							userAccount.setAccountValue(userAccount.getAccountValue() + tmpTransAmt);
						}
						else {
							cout << "ERROR: Deposit amount not a number" << endl;
						}
						break;

					case 'P':	//-------------------USER ADD INTEREST OPTION-------------------------
						cout << "INTEREST: " << endl;
						//AccountRecord.amount_Avail = (AccountRecord.amount_Avail*(1.0 + INTERESTRATE));
						userAccount.setAccountValue(userAccount.getAccountValue() *(1.0 + INTERESTRATE));
						break;

					case 'E':	//-------------------USER EXIT OPTION-------------------------
						cout << "-Exit" << endl; userselection = 'H';
						break;

					default:
						cout << "ERROR: INVALID Selection!" << endl;
						break;

					}
					if (userSubselection == 'C' || userSubselection == 'D' || userSubselection == 'W' || userSubselection == 'P') {

						//ModifyRecord(AccountRecord, out_file, &recordlocator, &recordEnd);
						ModifyRecordwc(userAccount, out_file, &recordlocator, &recordEnd);
					}
				}
			}
			else {
				cout << "ERROR:Invalid Account Number Entered!" << endl << endl;
			}

			break;

		case 'V':	//-------------------USER VIEW ALL OPTION-------------------------
			cout << endl << "--------------------Accounts on File-----------------------" << endl;
			cout << "Account Number" << "\t\t" << "Account Name" << "\t" << "Account Value " << endl;
			cout << "--------------" << "\t\t" << "------------" << "\t" << "-------------" << endl;

			in_file.open(FILENAME);
			if (in_file.fail()) { cout << "ERROR: NO SUCH FILE" << endl; }	//check for failure when opening
			getline(in_file, tmp);	//force a getline to set .eof bit

			if (!in_file.eof()) {
				in_file.clear();  //clear flags
				in_file.close(); // close it

				in_file.open(FILENAME);
				while (in_file.good()) {
					// GetRecord(AccountRecord, in_file); //pass strcture by reference, GetRecord expects and open file so open file beforehand
					GetRecordwc(userAccount, in_file); //pass strcture by reference, GetRecord expects and open file so open file beforehand
					//cout << AccountRecord.account_Number << "\t\t\t" << AccountRecord.name_Owner << "\t" << "$" << AccountRecord.amount_Avail << endl;
					//cout << userAccount.getAccountNumber() << "\t\t\t" << userAccount.getAccountName() << "\t" << userAccount.getAccountValue() << endl;
					userAccount.printAccount();
				}
			}
			else
			{
				cout << "ERROR: FILE EMPTY!" << endl;
			}
			in_file.clear();
			in_file.close();
			break;
			//-------------------USER QUIT OPTION-------------------------
		case 'Q':  cout << "user selected Q" << endl; break;

			//-------------------DEFAULT OPTION-------------------------
		default: cout << "ERROR: INVALID Selection!" << endl;
		}

	}


	return 0;
}//--------------------END MAIN--------------------------------------


//--------------------BEGIN Functions--------------------------------------

//********FUNCTION: GetRecord  BEGIN******************************
/*
GetRecord will get the next line from a passied filestream object, and parse it to a structure passed by reference
*/
void GetRecord(accountStruct &record, ifstream &inputfile) {
	istringstream tmpstring;
	string wholeentry;
	string accountNumber;
	string accountName;
	string accountValue;

	int i, j;


	tmpstring.clear();

	getline(inputfile, wholeentry);

	//BEGIN LINE PARSING
	i = 0;
	while (wholeentry.compare(i, 1, ";") != 0) { i++; }
	accountNumber = wholeentry.substr(0, i);
	tmpstring.str(accountNumber);
	tmpstring >> record.account_Number;



	i += 2;	//move i index off ";" and space
	j = i;	//j is placeholder to beginning of next entry
	while (wholeentry.compare(i, 1, ";") != 0) { i++; }
	accountName = wholeentry.substr(j, i - j);
	record.name_Owner = accountName;

	i += 2;	//move i index off ";" and space
	j = i;	//j is placeholder to beginning of next entry
	tmpstring.clear();
	tmpstring.precision(10);
	tmpstring.fixed;
	while (wholeentry.compare(i, 1, ";") != 0) { i++; }
	accountValue = wholeentry.substr(j, i - j);



	tmpstring.str(accountValue);
	tmpstring >> record.amount_Avail;
	cout.precision(15);


	// END LINE PARSING	

	return;
}
//********FUNCTION: GetRecord  END******************************

//********FUNCTION: GetRecordwc  BEGIN******************************
/*
GetRecord will get the next line from a passied filestream object, and parse it to a structure passed by reference
*/
void GetRecordwc(Accounts &accref, ifstream &inputfile) {
	istringstream tmpstring;
	string wholeentry;
	string accountNumber;
	string accountName;
	string accountValue;

	int i, j;
	int accountnum;
	double value;


	tmpstring.clear();

	getline(inputfile, wholeentry);

	//BEGIN LINE PARSING
	i = 0;
	while (wholeentry.compare(i, 1, ";") != 0) { i++; }
	accountNumber = wholeentry.substr(0, i);
	tmpstring.str(accountNumber);
	//tmpstring >> record.account_Number;
	tmpstring >> accountnum;
	accref.setAccountNumber(accountnum);



	i += 2;	//move i index off ";" and space
	j = i;	//j is placeholder to beginning of next entry
	while (wholeentry.compare(i, 1, ";") != 0) { i++; }
	accountName = wholeentry.substr(j, i - j);
	//record.name_Owner = accountName;
	accref.setAccountName(accountName);

	i += 2;	//move i index off ";" and space
	j = i;	//j is placeholder to beginning of next entry
	tmpstring.clear();
	tmpstring.precision(10);
	tmpstring.fixed;
	while (wholeentry.compare(i, 1, ";") != 0) { i++; }
	accountValue = wholeentry.substr(j, i - j);

	
	tmpstring.str(accountValue);
	tmpstring >> value;
	accref.setAccountValue(value);
	cout.precision(15);

	//cout << "im in my getRecord funciton" << endl;
	//accref.printAccount();
	// END LINE PARSING	

	return;
}
//********FUNCTION: GetRecordwc  END******************************

//********FUNCTION: AddRecord  BEGIN******************************
//This function adds a record based on info in a passed struct
bool AddRecord(struct accountStruct &record, ofstream &outputfile) {
	ostringstream tmpstring;

	outputfile.open(FILENAME, std::ios_base::app);	//open file in append mode
	if (!outputfile.is_open()) { cout << "ERROR: NO SUCH FILE" << endl; return false; }	//check for failure when opening
	if (outputfile.good()) {
		tmpstring << endl << record.account_Number << "; " << record.name_Owner << "; " << record.amount_Avail << ";";
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
//********FUNCTION: AddRecord  END******************************

//********FUNCTION: AddRecordwc  BEGIN******************************
//This function adds a record based on info in a passed struct
bool AddRecordwc(Accounts &accrec, ofstream &outputfile) {
	ostringstream tmpstring;

	cout << "Im in AddRecordwc function " << endl;
	accrec.printAccount();

	outputfile.open(FILENAME, std::ios_base::app);	//open file in append mode
	if (!outputfile.is_open()) { cout << "ERROR: NO SUCH FILE" << endl; return false; }	//check for failure when opening
	if (outputfile.good()) {
		tmpstring << endl << accrec.getAccountNumber() << "; " << accrec.getAccountName() << "; " << accrec.getAccountValue() << ";";
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
//********FUNCTION: AddRecordwc  END******************************


//********FUNCTION: FindRecord  BEGIN******************************
//This function looks to find a particular record, if it does, it populates the passed struct and reports length and end
bool FindRecord(accountStruct &record, ifstream &inputfile, int tmpAccountNum, int *recloc, int *recordend) {
	bool accountExists;
	string tmp = "";
	accountExists = false;
	int lengthNotFound = 0;
	int lengthFound = 0;

	inputfile.open(FILENAME);
	if (inputfile.fail()) { cout << "ERROR: NO SUCH FILE" << endl; }	//check for failure when opening (i.e no file)
	getline(inputfile, tmp);	//force a getline to set .eof bit

	if (!inputfile.eof()) {
		inputfile.clear();  //clear flags
		inputfile.close(); // close it
		inputfile.open(FILENAME); //reopen

		while (inputfile.good() && !accountExists) {
			GetRecord(record, inputfile); //pass strcture by reference
			

			if (record.account_Number != tmpAccountNum) {

				accountExists = false;
				lengthNotFound = inputfile.tellg();
			}

			else {
				accountExists = true;
				if (inputfile.eof()) {		//if we read past end of file, need to go get the location of last ch
					inputfile.clear();  //clear flags
					inputfile.close(); // close it
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
		cout << "ERROR: FILE EMPTY!" << endl;
	}
	inputfile.clear();
	inputfile.close();

	if (accountExists) {
		if (lengthNotFound > 0) {
			*recloc = lengthNotFound - 2;
			*recordend = lengthFound - 2;
		}
		else {
			*recloc = 0;
			*recordend = lengthFound - 2;

		}

		return true;

	}
	else {
		return false;

	}


}
//********FUNCTION: findRecord  END******************************

//********FUNCTION: FindRecordwClass  BEGIN******************************

bool FindRecordwClass(Accounts &accref, ifstream &inputfile, int tmpAccountNum, int *recloc, int *recordend)
{
	cout << "im in my find record w class function" << endl;

	

	bool accountExists;
	string tmp = "";
	accountExists = false;
	int lengthNotFound = 0;
	int lengthFound = 0;

	inputfile.open(FILENAME);
	if (inputfile.fail()) { cout << "ERROR: NO SUCH FILE" << endl; }	//check for failure when opening (i.e no file)
	getline(inputfile, tmp);	//force a getline to set .eof bit

	if (!inputfile.eof()) {
		inputfile.clear();  //clear flags
		inputfile.close(); // close it
		inputfile.open(FILENAME); //reopen

		while (inputfile.good() && !accountExists) {
			GetRecordwc(accref, inputfile); //pass strcture by reference


			if ((accref.getAccountNumber()) != tmpAccountNum) {

				accountExists = false;
				lengthNotFound = inputfile.tellg();
			}

			else {
				accountExists = true;
				if (inputfile.eof()) {		//if we read past end of file, need to go get the location of last ch
					inputfile.clear();  //clear flags
					inputfile.close(); // close it
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
		cout << "ERROR: FILE EMPTY!" << endl;
	}
	inputfile.clear();
	inputfile.close();

	if (accountExists) {
		if (lengthNotFound > 0) {
			*recloc = lengthNotFound - 2;
			*recordend = lengthFound - 2;
		}
		else {
			*recloc = 0;
			*recordend = lengthFound - 2;

		}

		return true;

	}
	else {
		return false;

	}




}

//********FUNCTION: findRecordwClass  END******************************


//********FUNCTION: ModifyRecord  BEGIN******************************
//This function modifies the file to edit a particular record
bool ModifyRecord(struct accountStruct &record, ofstream &outputfile, int *recloc, int *recordend) {
	ostringstream tmpstring;
	string tempstring, tempstring2, tmpfilename;
	ifstream in_file;
	int endpos;// = 0;
	int opos = 0;
	int result = 0;

	outputfile.precision(10);
	tmpstring.precision(10);

	in_file.open(FILENAME);			//open the input file
	if (in_file.fail()) {
		cout << "ERROR: Can't open Input file!" << endl;
		result++;
	}

	outputfile.open("tmp.dat");	//open temp output file in new output mode
	if (outputfile.fail()) {
		cout << "ERROR: Can't open temp output file!" << endl;
		result++;
	}

	in_file.seekg(0, in_file.end);		//find the end of the old file
	endpos = in_file.tellg();				//store end of old file

	in_file.seekg(0, in_file.beg);		//set input file pointer back to beginning
	opos = outputfile.tellp();


	while (in_file.good()) {			//while ur not at the end of the input file

		if (opos == *recloc) {

			//cout << "TEST COUT " << record.account_Number << "; " << record.name_Owner << "; " << record.amount_Avail << endl;
			tmpstring << record.account_Number << "; " << record.name_Owner << "; " << record.amount_Avail << ";";// << endl;
			outputfile << tmpstring.str();
			in_file.seekg(*recordend);
			opos = outputfile.tellp();		//find out where in the output file you are now

		}


		getline(in_file, tempstring2);	//get a line from input file	
		outputfile << tempstring2;		//store the line from input file into old 
		opos = outputfile.tellp();		//find out where in the output file you are now


		if (in_file.good()) {
			outputfile << endl;			//  add anothe endl
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
//********FUNCTION: ModifyRecord  END******************************

//********FUNCTION: ModifyRecordwc  BEGIN******************************
//This function modifies the file to edit a particular record
bool ModifyRecordwc(Accounts &record, ofstream &outputfile, int *recloc, int *recordend) {
	ostringstream tmpstring;
	string tempstring, tempstring2, tmpfilename;
	ifstream in_file;
	int endpos;// = 0;
	int opos = 0;
	int result = 0;

	outputfile.precision(10);
	tmpstring.precision(10);

	in_file.open(FILENAME);			//open the input file
	if (in_file.fail()) {
		cout << "ERROR: Can't open Input file!" << endl;
		result++;
	}

	outputfile.open("tmp.dat");	//open temp output file in new output mode
	if (outputfile.fail()) {
		cout << "ERROR: Can't open temp output file!" << endl;
		result++;
	}

	in_file.seekg(0, in_file.end);		//find the end of the old file
	endpos = in_file.tellg();				//store end of old file

	in_file.seekg(0, in_file.beg);		//set input file pointer back to beginning
	opos = outputfile.tellp();


	while (in_file.good()) {			//while ur not at the end of the input file

		if (opos == *recloc) {

			//cout << "TEST COUT " << record.account_Number << "; " << record.name_Owner << "; " << record.amount_Avail << endl;
			tmpstring << record.getAccountNumber() << "; " << record.getAccountName() << "; " << record.getAccountValue() << ";";// << endl;
			outputfile << tmpstring.str();
			in_file.seekg(*recordend);
			opos = outputfile.tellp();		//find out where in the output file you are now

		}


		getline(in_file, tempstring2);	//get a line from input file	
		outputfile << tempstring2;		//store the line from input file into old 
		opos = outputfile.tellp();		//find out where in the output file you are now


		if (in_file.good()) {
			outputfile << endl;			//  add anothe endl
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
//********FUNCTION: ModifyRecordwc  END******************************



//********FUNCTION: CheckLength  BEGIN******************************
//This function tests to see if the TMPSTRING is LENGTH char string
bool CheckLength(istringstream &tmpstring, int length) {
	int tmpaccountlength = 0;

	tmpstring.seekg(0, tmpstring.end);

	tmpaccountlength = tmpstring.tellg();
	tmpstring.seekg(0, tmpstring.beg);
	//	cout << "length= " << tmpaccountlength << endl;

	if (tmpaccountlength == length) {
		return true;
	}
	else {
		return false;
	}

}
//********FUNCTION: CheckLength  END******************************

//********FUNCTION: CheckEmpty  BEGIN******************************
//This function tests to see if the string is empty
bool CheckEmpty(istringstream &tmpstring) {
	int tmpaccountlength = 0;

	tmpstring.seekg(0, tmpstring.end);

	tmpaccountlength = tmpstring.tellg();
	tmpstring.seekg(0, tmpstring.beg);
	//	cout << "length= " << tmpaccountlength << endl;

	if (tmpaccountlength != 0) {
		return true;
	}
	else {
		return false;
	}

}
//********FUNCTION: CheckEmpty  END******************************



//********FUNCTION: IsNumber  BEGIN******************************
//This function tests to see if the TMPSTRING is LENGTH digit number
bool IsNumber(const string& tmpstring, int length) {

	int i;
	int result = 0;

	for (i = 0; i < length; i++) {

		if (isdigit(tmpstring[i])) {
			result++;
		}

	}


	if (result == length) {
		return true;
	}
	else {
		return false;
	}


}
//********FUNCTION: IsNumber  END******************************

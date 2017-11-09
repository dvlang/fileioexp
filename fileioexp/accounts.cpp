#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>

#include "accounts.h"




Accounts::Accounts() { account_Number = 0; name_Owner = "null"; amount_Avail = 1010; }

void Accounts::printAccount()
{
	//std::cout << "Account Number: " << account_Number << " Name: " << name_Owner << " Amount Available: " << amount_Avail << std::endl;
	std::cout << account_Number << "\t\t\t" << name_Owner << "\t" << "$" << amount_Avail << std::endl;
}

void Accounts::setAccountNumber(int accnum) { account_Number = accnum; }
void Accounts::setAccountName(std::string accname) { name_Owner = accname; }
void Accounts::setAccountValue(double accval) { amount_Avail = accval; }

int Accounts::getAccountNumber() { return account_Number; }
std::string Accounts::getAccountName() { return name_Owner; }
double Accounts::getAccountValue() { return amount_Avail; }





//GetRecord will get the next line from a passied filestream object, and parse it to a structure passed by reference

void Accounts::GetRecordwc(std::ifstream &inputfile) {
	std::istringstream tmpstring;
	std::string wholeentry;
	std::string accountNumber;
	std::string accountName;
	std::string accountValue;

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

	tmpstring >> account_Number;
	
	//tmpstring >> accountnum;
	//accref.setAccountNumber(accountnum);



	i += 2;	//move i index off ";" and space
	j = i;	//j is placeholder to beginning of next entry
	while (wholeentry.compare(i, 1, ";") != 0) { i++; }
	accountName = wholeentry.substr(j, i - j);
	//accref.setAccountName(accountName);

	name_Owner = accountName;
	

	i += 2;	//move i index off ";" and space
	j = i;	//j is placeholder to beginning of next entry
	tmpstring.clear();
	tmpstring.precision(10);
	tmpstring.fixed;
	while (wholeentry.compare(i, 1, ";") != 0) { i++; }
	accountValue = wholeentry.substr(j, i - j);


	tmpstring.str(accountValue);
	tmpstring >> value;
	//accref.setAccountValue(value);
	amount_Avail = value;

	std::cout.precision(15);


	// END LINE PARSING	

	return;
}


//This function adds a record based on info in a passed struct
bool Accounts::AddRecordwc(std::ofstream &outputfile) {
	std::ostringstream tmpstring;

	std::cout << "Im in AddRecordwc function " << std::endl;
	//accrec.printAccount();

	outputfile.open("accounts.dat", std::ios_base::app);	//open file in append mode
	if (!outputfile.is_open()) { std::cout << "ERROR: NO SUCH FILE" << std::endl; return false; }	//check for failure when opening
	if (outputfile.good()) {
		//tmpstring << std::endl << accrec.getAccountNumber() << "; " << accrec.getAccountName() << "; " << accrec.getAccountValue() << ";";
		tmpstring << std::endl << account_Number << "; " << name_Owner << "; " << amount_Avail <<"; ";
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

/*
bool Accounts::FindRecordwClass( ifstream &inputfile, int tmpAccountNum, int *recloc, int *recordend)
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

*/


bool Accounts::doesAccountExist(std::ifstream &inputfile, const int accnum) {

	bool accountExists;
	std::string tmp = "";
	accountExists = false;


	inputfile.open("accounts.dat");
	if (inputfile.fail()) { std::cout << "ERROR: NO SUCH FILE" << std::endl; }	//check for failure when opening (i.e no file)
	getline(inputfile, tmp);	//force a getline to set .eof bit

	if (!inputfile.eof()) {
		inputfile.clear();  //clear flags
		inputfile.close(); // close it
		inputfile.open("accounts.dat"); //reopen

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
		std::cout << "ERROR: FILE EMPTY!" << std::endl;
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

void Accounts::printAllAccounts(std::ifstream &inputfile){
	std::string tmp = "";

	std::cout << "hi, im in my new print all function" << std::endl;

	inputfile.open("accounts.dat");
	if (inputfile.fail()) { std::cout << "ERROR: NO SUCH FILE" << std::endl; }	//check for failure when opening
	getline(inputfile, tmp);	//force a getline to set .eof bit

	if (!inputfile.eof()) {
		inputfile.clear();  //clear flags
		inputfile.close(); // close it

		inputfile.open("accounts.dat");
		while (inputfile.good()) {

			GetRecordwc(inputfile); 

			printAccount();
		}
	}
	else
	{
		std::cout << "ERROR: FILE EMPTY!" << std::endl;
	}
	inputfile.clear();
	inputfile.close();
}

bool Accounts::accountWithdrawl(double transamt) {
	if (amount_Avail >= transamt) {

		amount_Avail = amount_Avail - transamt;
		return true;
	}
	else {
		return false;
	}
}
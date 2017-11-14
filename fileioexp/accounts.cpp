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


//------------------------IM GOING TO DEPRECIATE THIS USAGE-------------------------------------
std::string Accounts::getAccountType(std::ifstream &inputfile) {
	std::istringstream tmpstring;
	std::string wholeentry;
	std::string accountType;
	int currentpos;

	int i, j;
	tmpstring.clear();

	currentpos = inputfile.tellg();  //get the current position in the file

	getline(inputfile, wholeentry);
	std::cout << "ga_input line is: " << wholeentry << std::endl;

	i = 0;
	while (wholeentry.compare(i, 1, ";") != 0) { i++; }
	accountType = wholeentry.substr(0, i);
	//tmpstring.str(accountType);

	//tmpstring >> accountType;
	std::cout << "ga_ account type is: " << accountType << std::endl;

	inputfile.seekg(currentpos);  //set the file pointer back to where we were

	return accountType;
}
//------------------------------END getaccounttype---------------------------------------------

//GetRecord will get the next line from a passied filestream object, and parse it to a structure passed by reference

void Accounts::GetRecordwc(std::ifstream &inputfile) {
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
	std::cout << "input line is: " << wholeentry << std::endl;

	i = 0;
	while (wholeentry.compare(i, 1, ";") != 0) { i++; }
	accountType = wholeentry.substr(0, i);
	tmpstring.str(accountType);

	tmpstring >> accountType;
	std::cout << "gr_ account type is: " << accountType << std::endl;

	//i = 0;
	i += 2;
	j = i;	//j is placeholder to beginning of next entry
	
	//accountNumber = wholeentry.substr(0, i);
	while (wholeentry.compare(i, 1, ";") != 0) { i++; }
	accountNumber = wholeentry.substr(j, i - j);
	tmpstring.str(accountNumber);
	
	tmpstring >> account_Number;
	account_Number = std::stoi(accountNumber);
	std::cout << "gr_ account number is: " << account_Number << std::endl;


	i += 2;	//move i index off ";" and space
	j = i;	//j is placeholder to beginning of next entry
	while (wholeentry.compare(i, 1, ";") != 0) { i++; }
	accountName = wholeentry.substr(j, i - j);
	

	name_Owner = accountName;

	std::cout << "gr_ account name is: " << name_Owner << std::endl;

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


	i += 2;	//move i index off ";" and space
	j = i;	//j is placeholder to beginning of next entry
	while (wholeentry.compare(i, 1, ";") != 0) { i++; }
	dateOpened = wholeentry.substr(j, i - j);


	//date_Opened = dateOpened;

	std::cout << "gr_ account opened: " << dateOpened << std::endl;

	// END LINE PARSING	

	return;
}


//This function adds a record based on info in a passed struct
bool Accounts::AddRecordwc(std::ofstream &outputfile) {
	std::ostringstream tmpstring;

	//std::cout << "Im in AddRecordwc function " << std::endl;
	//accrec.printAccount();

	outputfile.open(FILENAME, std::ios_base::app);	//open file in append mode
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


bool Accounts::doesAccountExist(std::ifstream &inputfile, const int accnum) {

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

//-------------------IM GOING TO DEPRECIATE THIS FUNCTION IN ACCOUNT-------------------
void Accounts::printAllAccounts(std::ifstream &inputfile){
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

			accounttype= getAccountType(inputfile);
			GetRecordwc(inputfile); 

			printAccount();
		}
	}
	else
	{
		std::cout << "ERROR_paa: FILE EMPTY!" << std::endl;
	}
	inputfile.clear();
	inputfile.close();
}
//-------------------end printAllAccounts-------------------

bool Accounts::accountWithdrawl(double transamt) {
	if (amount_Avail >= transamt) {

		amount_Avail = amount_Avail - transamt;
		return true;
	}
	else {
		return false;
	}
}

void Accounts::accountDeposit(double transamt) {
	amount_Avail = amount_Avail + transamt;
}

void Accounts::accountAddInterest(){
	amount_Avail = amount_Avail*(1.0 + INTERESTRATE);  //was INTERSTRATE
}


//*----------------FUNCTION: FindRecordwClass  BEGIN--------------------------------

bool Accounts::FindRecordwClass(Accounts &accref, std::ifstream &inputfile, int tmpAccountNum)
{
	//std::cout << "im in my find record w class function" << std::endl;
	//std::cout << "I am looking for this record: " << tmpAccountNum<< std::endl;
	
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

			//std::cout << "found it! record locator is: " << recordlocator << " record End is: " << recordEnd << std::endl;
			//std::cout << "here is the matching account: " << std::endl;
			printAccount();
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

//----------------FUNCTION: findRecordwClass  END----------------------------------------


//----------------FUNCTION: ModifyRecordwc  BEGIN----------------------------------------
//This function modifies the file to edit a particular record
bool Accounts::ModifyRecordwc(Accounts &record, std::ofstream &outputfile) {
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

			
			tmpstring << record.getAccountNumber() << "; " << record.getAccountName() << "; " << record.getAccountValue() << ";";

			

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

	/*
	remove("old.dat");
	rename("accounts.dat", "old.dat");	//keep a temp copy of file for safekeeping
	remove("accounts.dat");
	result += rename("tmp.dat", "accounts.dat");
	*/
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
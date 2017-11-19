#include "stdafx.h"
#include "checking.h"
#include "accounts.h"

#include <string>
#include <iostream>
#include <fstream>
#include <time.h>
#include <iomanip>
#include <cstring>
#include <sstream>

//------------------------------CHECKING CLASS------------------------------------------------------
Checking::Checking() :direct_Deposit(false), transaction_Fee(0.0) {}
Checking::~Checking() { std::cout << "destroy Checking" << std::endl; }
void Checking::setDirectdeposit(bool dd) { direct_Deposit = dd; }
void Checking::setTransFee(double transfee) { transaction_Fee = transfee; }

bool Checking::getDirectDeposit() { return direct_Deposit; }
double Checking::getTransFee() { return transaction_Fee; }

void Checking::assessCheckingTransFee() {

	amount_Avail = amount_Avail - transaction_Fee;
}

void Checking::GetRecordwc(std::ifstream& inputfile) {

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


		//GET ACCOUNT TYPE
		i = 0;
		while (wholeentry.compare(i, 1, ";") != 0) { i++; }
		accountType = wholeentry.substr(0, i);
		tmpstring.str(accountType);

		tmpstring >> accountType;
		account_Type = accountType;

		//GET ACCOUNT NUMBER

		i += 2;
		j = i;	//j is placeholder to beginning of next entry

		while (wholeentry.compare(i, 1, ";") != 0) { i++; }
		accountNumber = wholeentry.substr(j, i - j);
		tmpstring.str(accountNumber);

		tmpstring >> account_Number;
		account_Number = std::stoi(accountNumber);

		//GET NAME OF THE OWNER
		i += 2;	//move i index off ";" and space
		j = i;	//j is placeholder to beginning of next entry
		while (wholeentry.compare(i, 1, ";") != 0) { i++; }
		accountName = wholeentry.substr(j, i - j);

		name_Owner = accountName;

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

		//GET DATE ACCOUNT OPENED
		i += 2;	//move i index off ";" and space
		j = i;	//j is placeholder to beginning of next entry
		while (wholeentry.compare(i, 1, ";") != 0) { i++; }
		dateOpened = wholeentry.substr(j, i - j);

		date_Opened = dateOpened;

		if (account_Type == "Checking") {
			tmpstring.clear();
			//GET Direct deposit
			i += 2;	//move i index off ";" and space
			j = i;	//j is placeholder to beginning of next entry
			while (wholeentry.compare(i, 1, ";") != 0) { i++; }
			dd = wholeentry.substr(j, i - j);

			tmpstring.str(dd);
			tmpstring >> std::boolalpha >> direct_Deposit;

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

		}
		// END LINE PARSING	

		return;
	}

void Checking::printAccount()
	{

		std::cout << account_Type << "\t" << account_Number << "\t\t" << std::setw(15)<<std::left<< name_Owner << "\t" << "$" << std::setw(10) << std::left<<amount_Avail << "\t" << std::setw(10) << std::left<<date_Opened << "\t" << std::setw(10) << std::left<<std::boolalpha << direct_Deposit << "\t" << "$" << transaction_Fee << std::endl;
	}

bool Checking::doesAccountExist(std::ifstream &inputfile, const int accnum) {

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

bool Checking::AddRecordwc(std::ofstream &outputfile) {
		std::ostringstream tmpstring;

		outputfile.open(FILENAME, std::ios_base::app);	//open file in append mode
		if (!outputfile.is_open()) { std::cout << "ERROR: NO SUCH FILE" << std::endl; return false; }	//check for failure when opening
		if (outputfile.good()) {

			tmpstring << std::endl << account_Type << "; " << account_Number << "; " << name_Owner << "; " << amount_Avail << "; " << date_Opened << "; " << std::boolalpha << direct_Deposit << "; " << transaction_Fee << "; ";
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

bool Checking::FindRecordwClass(Checking &accref, std::ifstream &inputfile, int tmpAccountNum)
	{


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

bool Checking::ModifyRecordwc(Checking &record, std::ofstream &outputfile) {
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



//------------------------------END CHECKING CLASS------------------------------------------------------
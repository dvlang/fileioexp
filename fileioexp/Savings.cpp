#include "stdafx.h"
#include "savings.h"
#include "accounts.h"

#include <string>
#include <iostream>
#include <fstream>
#include <time.h>
#include <cstring>
#include <sstream>

//------------------------------SAVINGS CLASS-----------------------------------------------------------

	Savings::Savings() :maturity_Date("01/01/1980"), current_Interest(0.01), default_Interest(0.01)
	{
	}
	Savings::~Savings() { std::cout << "destroy Savings" << std::endl; }
	void Savings::setMatDate(std::string matdate) { maturity_Date = matdate; }
	void Savings::setCurInt(double curint) { current_Interest = curint; }
	void Savings::setDefInt(double defint) { default_Interest = defint; }

	std::string Savings::getMatDate() { return maturity_Date; }
	double Savings::getCurInt() { return current_Interest; }
	double Savings::getDefInt() { return default_Interest; }


	void Savings::GetRecordwc(std::ifstream& inputfile) {

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
		if (account_Type == "Savings") {

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
	void Savings::printAccount()
	{

		std::cout << account_Type << " \t" << account_Number << "\t\t" << name_Owner << "\t" << "$" << amount_Avail << "\t" << date_Opened << "\t" << maturity_Date << "\t" << current_Interest << "\t" << default_Interest << std::endl;
	}

	bool Savings::doesAccountExist(std::ifstream &inputfile, const int accnum) {

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
	bool Savings::AddRecordwc(std::ofstream &outputfile) {
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

	bool Savings::FindRecordwClass(Savings &accref, std::ifstream &inputfile, int tmpAccountNum)
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
				//printAccount();
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

	bool Savings::ModifyRecordwc(Savings &record, std::ofstream &outputfile) {
		std::ostringstream tmpstring;
		std::string tempstring, tempstring2, tmpfilename;
		std::ifstream in_file;
		int endpos;// = 0;
		int opos = 0;
		int result = 0;

		outputfile.precision(10);
		tmpstring.precision(10);
		//std::cout << "modifyrecwc(SAV) was called to save this data: " << std::endl;
		//	record.printAccount();
		FindRecordwClass(record, in_file, record.getAccountNumber());
		//	std::cout << "ERETURN FROM FIND RECORD" << std::endl;
		//	std::cout << "found it! record locator is: " << recordlocator << " record End is: " << recordEnd << std::endl;
		//	std::cout << "here is the matching account: " << std::endl;
		//	record.printAccount();
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

	bool Savings::accountWithdrawl(double transamt) {
		bool dategood;
		

		dategood=MatDateMet();

		if (amount_Avail >= transamt && dategood) {

			amount_Avail = amount_Avail - transamt;
			return true;
		}
		else {
			if (amount_Avail < transamt) { std::cout << "Insufficient Funds " << std::endl; }
			return false;
		}

	}


	void Savings::accountAddInterest() {
		bool dategood;
		dategood = MatDateMet();

		if (dategood) {
			amount_Avail = amount_Avail*(1.0 + (current_Interest/100));
		}
		else {
			amount_Avail = amount_Avail*(1.0 + (default_Interest/100));  
		}

		
	}

	bool Savings::MatDateMet() {
		std::string date;
		std::string day;
		std::string month;
		std::string year;
		std::string parmonth;
		std::string parday;
		std::string paryear;
		std::string matdate;
		matdate = maturity_Date;
		bool dategood;

		//get current date
		//time functions
		time_t timer;
		time(&timer);
		struct tm* brokentime = localtime(&timer);

		date = std::to_string(brokentime->tm_mon) + "/" + std::to_string(brokentime->tm_mday) + "/" + std::to_string((brokentime->tm_year) + 1900);
		day = std::to_string(brokentime->tm_mday);
		month = std::to_string(brokentime->tm_mon);
		year = std::to_string((brokentime->tm_year) + 1900);

		//parse the maturity date from the data record
		int i, j;
		i = 0;
		while (matdate.compare(i, 1, "/") != 0) { i++; }
		parmonth = matdate.substr(0, i);
		//std::cout << "MatMo: " << parmonth << std::endl;

		i += 1;	//move i index off ";" and space
		j = i;	//j is placeholder to beginning of next entry
		while (matdate.compare(i, 1, "/") != 0) { i++; }
		parday = matdate.substr(j, i - j);
		//std::cout << "MatDay: " << parday << std::endl;

		i += 1;	//move i index off ";" and space
		j = i;	//j is placeholder to beginning of next entry
		while (i<matdate.size()) { i++; }
		paryear = matdate.substr(j, i - j);
		//std::cout << "MatYear: " << paryear << std::endl;


		//dategood = false;
		if (paryear <= year && parmonth <= month && parday <= day) { return true; }
		else { 
			std::cout << "ERROR: Maturity Date Not met! " << std::endl; 
			return false;
		}
	}


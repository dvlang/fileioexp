// fileioexp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>

using namespace std;


#include "fileioexp.h"

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

/*
struct accountStruct
{
	int account_Number;
	string name_Owner;
	double amount_Avail;
};*/

//--------------------BEGIN Function Prototype-----------------------------
//void ViewAllRecords(accountStruct &record, ifstream&);
//--------------------END Function Prototype-----------------------------

//--------------------BEGIN MAIN--------------------------------------
int main()
{
	accountStruct AccountRecord;
	accountStruct tmpAccount;

	ifstream in_file;
	ofstream out_file;
	ifstream io_file;
	


	cout << "WELCOME TO THE ACCOUNTS MANAGER" << endl << endl;

	while (userselection != 'Q') {
		//in_file.clear();
		//MENU / USER INTERFACE
		cout << "************************************************" << endl;
		cout << "Please select from one of the following options:" << endl<<endl;
		cout << "Press ""I"" to insert a new account record" << endl;
		cout << "Press ""M"" to modify an existing record" << endl;
		cout << "Press ""V"" to view all account records" << endl;
		cout << "Press ""H"" to return to this menu" << endl;
		cout << "Press ""Q"" to quit" << endl;
		cout << "************************************************" << endl;
		cout << "Entry -> ";

		//cin >> userselection;
		getline(cin, tmp);
		userselection = tmp[0];


		switch (userselection)
		{
		case 'I':  
			tmpstring.clear();
			cout << "CREATE NEW ACCOUNT" << endl;
			cout << "Desired account number (6digits): "<<endl;
			getline(cin, tmp);
			tmpstring.str(tmp);
			tmpstring >> tmpAccount.account_Number;

			cout << "Desired Account Holder Name: "<<endl;
			getline(cin, tmp);
			tmpAccount.name_Owner = tmp;
			
			cout << "Desired Initial Value: "<<endl;
			getline(cin, tmp);
			tmpstring.clear();
			tmpstring.str(tmp);
			tmpstring >> tmpAccount.amount_Avail;

			AddRecord(tmpAccount, out_file);
			
			break;
		
		case 'M':  
			tmpstring.clear();
			recordlocator = 0;
			accountExists = false;

			cout << "MODIFY AN ACCOUNT" << endl;
			cout << "Account Number to Modify" << endl; 
			getline(cin, tmp);
			tmpstring.str(tmp);
			tmpstring >> tmpTransAccount;

			accountExists = FindRecord(AccountRecord, in_file, tmpTransAccount, &recordlocator, &recordEnd);

			if (accountExists) {
				cout << "Account Number: " << "\t" << "Account Name: " << "\t" << "Account Value: " << "\t" << "Record Locator: " << endl;
				cout << AccountRecord.account_Number << "\t\t\t" << AccountRecord.name_Owner << "\t" << AccountRecord.amount_Avail<<"\t\t" << recordlocator<< endl;
			}
			else
			{
				cout << "Account Not Found!!!" << endl << endl;
			}
			if (accountExists) {

				cout << endl << "SELECT ACTION" << endl;
				cout << "Press C to Change Name on account record" << endl;
				cout << "Press W to perform a withdrawl" << endl;
				cout << "Press D to make a deposit" << endl;
				cout << "Press E to Exit" << endl;
				getline(cin, tmp);
				userSubselection = tmp[0];

				switch (userSubselection)
				{
				case 'C':
					cout << "CHANGE NAME: " << endl;
					cout << "What is new Name: " << endl;
					getline(cin, tmp);
					AccountRecord.name_Owner = tmp;

					break;
				case 'W':
					cout << "WITHDRAWL: " << endl;
					cout << "How Much: " << endl;
					getline(cin, tmp);
					tmpstring.clear();
					tmpstring.str(tmp);
					tmpstring >> tmpTransAmt;
					cout << "tmpTransAmt = " << tmpTransAmt << endl;
					if (AccountRecord.amount_Avail >= tmpTransAmt) {
						AccountRecord.amount_Avail = AccountRecord.amount_Avail - tmpTransAmt;
					}
					else {
						cout << "Insufficient funds!" << endl;
					}

					break;
				case 'D':
					cout << "DEPOSIT: " << endl;
					cout << "How Much: " << endl;
					getline(cin, tmp);
					tmpstring.clear();
					tmpstring.str(tmp);
					tmpstring >> tmpTransAmt;

					AccountRecord.amount_Avail = AccountRecord.amount_Avail + tmpTransAmt;

					break;
				case 'E': cout << "-Exit" << endl; userselection = 'H';
					break;
				default: cout << "INVALID Selection!" << endl;
					break;

				}
				if (userSubselection == 'C' || userSubselection == 'D' || userSubselection == 'W' ) {
				
				cout << "New values to commit: " << endl;
				cout << "Account Number: " << "\t" << "Account Name: " << "\t" << "Account Value: " << endl;
				cout << AccountRecord.account_Number << "\t\t\t" << AccountRecord.name_Owner << "\t" << AccountRecord.amount_Avail << endl;
				ModifyRecord(AccountRecord, out_file, &recordlocator, &recordEnd);
				}
			}

			break;

		case 'V':  
			cout << "VIEW ALL ACCOUNT RECORDS" << endl; 
			cout << "Account Number: " << "\t" << "Account Name: " << "\t" << "Account Value: " << endl;
			in_file.open("input.dat");
			if (in_file.fail()) { cout << "ERROR: NO SUCH FILE" << endl; }	//check for failure when opening
			getline(in_file, tmp);	//force a getline to set .eof bit

			if (!in_file.eof()) {
				in_file.clear();  //clear flags
				in_file.close(); // close it
				in_file.open("input.dat"); //reopen
				while (in_file.good()) {	
					GetRecord(AccountRecord, in_file); //pass strcture by reference
					cout << AccountRecord.account_Number << "\t\t\t" << AccountRecord.name_Owner << "\t" << "$"<<AccountRecord.amount_Avail << endl;
				}
			}
			else
			{
				cout << "ERROR: FILE EMPTY!" << endl;
			}
			in_file.clear();
			in_file.close();
			break;  
		case 'Q':  cout << "user selected Q" << endl; break;
		case 'H':  cout << "user selected H" << endl; break;
		default: cout << "INVALID Selection!" << endl;
		}

	}


	return 0;
}//--------------------END MAIN--------------------------------------


//--------------------BEGIN Functions--------------------------------------

//********FUNCTION: GetRecord  BEGIN******************************
/*
GetRecord will get the next line from a passied filestream object, and parse it to a structure passed by reference
*/
void GetRecord( accountStruct &record, ifstream &inputfile) {
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
		//	Person1.name_Owner = accountname;
		record.name_Owner = accountName;

		i += 2;	//move i index off ";" and space
		j = i;	//j is placeholder to beginning of next entry
		tmpstring.clear();
		tmpstring.precision(10);
		tmpstring.fixed;
		while (wholeentry.compare(i, 1, ";") != 0) { i++; }
		accountValue = wholeentry.substr(j, i - j);

	//	cout<< "GetRecord: accountValue " << accountValue<<endl;

		tmpstring.str(accountValue);
		tmpstring >> record.amount_Avail;
		//std::string::size_type sz;

		//record.amount_Avail = std::stod(accountValue,&sz);
		cout.precision(15);
		//cout << "GetRecord: record.amount_Avail " << record.amount_Avail << endl;

		// END LINE PARSING	

	return;
}
//********FUNCTION: GetRecord  END******************************

//********FUNCTION: AddRecord  BEGIN******************************
bool AddRecord(struct accountStruct &record, ofstream &outputfile) {
	ostringstream tmpstring;

	outputfile.open("input.dat", std::ios_base::app);	//open file in append mode
	if (!outputfile.is_open()) { cout << "ERROR: NO SUCH FILE" << endl; return false; }	//check for failure when opening
	if (outputfile.good()) {
		tmpstring << endl<< record.account_Number << "; " << record.name_Owner << "; " << record.amount_Avail << ";";
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

//********FUNCTION: findRecord  BEGIN******************************
bool FindRecord(accountStruct &record, ifstream &inputfile, int tmpAccountNum, int *recloc, int *recordend) {
	bool accountExists;
	string tmp = "";
	accountExists = false;
	int lengthNotFound = 0;
	int lengthFound = 0;

	inputfile.open("input.dat");
	if (inputfile.fail()) { cout << "ERROR: NO SUCH FILE" << endl; }	//check for failure when opening (i.e no file)
	getline(inputfile, tmp);	//force a getline to set .eof bit

	if (!inputfile.eof()) {
		inputfile.clear();  //clear flags
		inputfile.close(); // close it
		
		inputfile.open("input.dat"); //reopen
		
		while (inputfile.good() && !accountExists) {
			GetRecord(record, inputfile); //pass strcture by reference
			if (record.account_Number != tmpAccountNum) {

				accountExists = false;
				lengthNotFound = inputfile.tellg();
				cout << "last location not in file: " << lengthNotFound << endl;
			}

			else {
				lengthFound = inputfile.tellg();
				cout << "location in file: " << lengthFound << endl;
				accountExists = true;
			}
		}
	}
	else
	{
		cout << "ERROR: FILE EMPTY!" << endl;
	}
	inputfile.clear();
	inputfile.close();

	if (accountExists){
		if (lengthNotFound > 0) {
		*recloc = lengthNotFound-2; 
		*recordend = lengthFound-2;
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

//********FUNCTION: ModifyRecord  BEGIN******************************
bool ModifyRecord(struct accountStruct &record, ofstream &outputfile, int *recloc, int *recordend) {
	ostringstream tmpstring;
	string tempstring, tempstring2;
	ifstream in_file;
	int endpos, opos = 0;

	outputfile.precision(10);
	tmpstring.precision(10);

	in_file.open("input.dat");			//open the input file
	outputfile.open("input_new.dat");	//open temp output file in new output mode

	in_file.seekg(0, in_file.end);		//find the end of the old file
	endpos = in_file.tellg();				//store end of old file

	in_file.seekg(0,in_file.beg);		//set input file pointer back to beginning
	opos = outputfile.tellp();
	cout << "opos at begin: " << opos << endl;

	while (in_file.good()) {			//while ur not at the end of the input file

		if (opos == *recloc)
		{

			cout << "TEST COUT " << record.account_Number << "; " << record.name_Owner << "; " << record.amount_Avail << endl;
			tmpstring << record.account_Number << "; " << record.name_Owner << "; " << record.amount_Avail << ";";// << endl;
			outputfile << tmpstring.str();
			in_file.seekg(*recordend);
			opos = outputfile.tellp();		//find out where in the output file you are now
			cout << "endpos: " << endpos << endl;
			cout << "opos: " << opos << endl;
			cout << "recloc: " << *recloc << endl;
			cout << "recend: " << *recordend << endl;
		}


		getline(in_file, tempstring2);	//get a line from input file	
		outputfile << tempstring2;		//store the line from input file into old 
		opos = outputfile.tellp();		//find out where in the output file you are now


		if(in_file.good()){
			outputfile << endl;			// and dont add anothe endl
		}

		cout << "endpos: "<< endpos << endl;
		cout << "opos: " <<opos << endl;
		cout << "recloc: " <<*recloc << endl;
		cout << "recend: " <<*recordend << endl;
/*
		if (opos == *recloc) {
			tmpstring << record.account_Number << "; " << record.name_Owner << "; " << record.amount_Avail << ";" << endl;
			outputfile << tmpstring.str();
		}
		in_file.seekg(*recordend);
*/	
	}

	/*

	//outputfile.open("input_new.dat", ios::in | ios::out);	//open file in editable mode
	outputfile.open("input_new.dat");	//open file in new output mode
	//if (!outputfile.is_open()) { cout << "ERROR: NO SUCH FILE" << endl; return false; }	//check for failure when opening
	if (outputfile.good()) {
	//	if (true) {
		tmpstring << record.account_Number << "; " << record.name_Owner << "; " << record.amount_Avail << ";" << endl;

		//outputfile.seekp(*recloc);
		outputfile << tmpstring.str();
		//remove("testfiletodelete.dat");
	
	}
	else
	{
		outputfile.clear();
		outputfile.close();
		return false;
	}

	*/
	in_file.clear();
	in_file.close();
	outputfile.clear();
	outputfile.close();
	int result;
	remove("input.dat");

	result = rename("input_new.dat", "input.dat");
	if (result == 0)
		puts("File successfully renamed");
	else
		perror("Error renaming file");
	return 0;

	remove("input.dat");

	return true;
}
//********FUNCTION: ModifyRecord  END******************************

//--------------------END Functions----------------------------------------



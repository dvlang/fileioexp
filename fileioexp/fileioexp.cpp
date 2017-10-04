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
	//in_file.open("input.dat");
	//if (in_file.fail()) { cout << "ERROR: NO SUCH FILE" << endl; return 0; }	//check for failure when opening


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
			cout << "MODIFY AN ACCOUNT" << endl;
			cout << "Account Number to Modify" << endl; 
			getline(cin, tmp);
			tmpstring.str(tmp);
			tmpstring >> tmpAccount.account_Number;
			tmpAccount.name_Owner = "";
			tmpAccount.amount_Avail=00.00;
			

			in_file.open("input.dat");
			if (in_file.fail()) { cout << "ERROR: NO SUCH FILE" << endl; }	//check for failure when opening
			getline(in_file, tmp);	//force a getline to set .eof bit

			if (!in_file.eof()) {
				in_file.clear();  //clear flags
				in_file.close(); // close it
				in_file.open("input.dat"); //reopen
				while (in_file.good()) {
					GetRecord(AccountRecord, in_file); //pass strcture by reference
					if (AccountRecord.account_Number == tmpAccount.account_Number) {
						cout << "Account Valid!" << endl;
					//	tmpAccount.name_Owner = AccountRecord.name_Owner;
					//	tmpAccount.amount_Avail = AccountRecord.amount_Avail;

						cout << "SELECT ACTION" << endl;
						cout << "Press C to Change Name on account record" << endl;
						cout << "Press W to perform a widthdrawl" << endl;
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
							break;
						case 'W':
							cout << "WIDTHDRAWL: " << endl;
							cout << "How Much: " << endl;
							getline(cin, tmp);
							break;
						case 'D':
							cout << "DEPOSIT: " << endl;
							cout << "How Much: " << endl;
							getline(cin, tmp);
							break;
						case 'E': userselection = 'H';
							break;
						default: cout << "INVALID Selection!" << endl;
							break;

						}
						
					}
					else {
						cout << "account doesnt exist";
					}
				}
			}
			else
			{
				cout << "ERROR: FILE EMPTY!" << endl;
			}
			in_file.clear();
			in_file.close();
			
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
					cout << AccountRecord.account_Number << "\t\t\t" << AccountRecord.name_Owner << "\t" << AccountRecord.amount_Avail << endl;
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


	//VIEW ALL FUNCTION


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
		while (wholeentry.compare(i, 1, ";") != 0) { i++; }
		accountValue = wholeentry.substr(j, i - j);
		tmpstring.str(accountValue);
		tmpstring >> record.amount_Avail;
		// END LINE PARSING	

	return;
}

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



//--------------------END Functions----------------------------------------


/*

//OLD VIEW ALL FUNCTION

while (!in_file.eof()) {
tmpstring.clear();

getline(in_file, wholeentry);

//BEGIN LINE PARSING
int i = 0;
while (wholeentry.compare(i, 1, ";") != 0) { i++; }
accountNumber = wholeentry.substr(0, i);
tmpstring.str(accountNumber);
tmpstring >> Person1.account_Number;

i += 2;	//move i index off ";" and space
int j = i;	//j is placeholder to beginning of next entry
while (wholeentry.compare(i, 1, ";") != 0) { i++; }
accountname = wholeentry.substr(j, i - j);
Person1.name_Owner = accountname;

i += 2;	//move i index off ";" and space
j = i;	//j is placeholder to beginning of next entry
tmpstring.clear();
while (wholeentry.compare(i, 1, ";") != 0) { i++; }
accountValue = wholeentry.substr(j, i - j);
tmpstring.str(accountValue);
tmpstring >> Person1.amount_Avail;
// END LINE PARSING

cout << "Account Number: " << Person1.account_Number << endl;
cout << "Account Name: " << Person1.name_Owner << endl;
cout << "Account Total: " << Person1.amount_Avail << endl;
}
*/


//END VIEW ALL FUNCTION
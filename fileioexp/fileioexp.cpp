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

	ifstream in_file;
	in_file.open("input.dat");

	if (in_file.fail()) { cout << "ERROR: NO SUCH FILE" << endl; return 0; }	//check for failure when opening


	cout << "WELCOME TO THE ACCOUNTS MANAGER" << endl << endl;

	while (userselection != 'Q') {
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

		cin >> userselection;


		switch (userselection)
		{
		case 'I':  cout << "user selected I" << endl; break;
		case 'M':  cout << "user selected M" << endl; break;
		case 'V':  
			cout << "VIEW ALL ACCOUNT RECORDS" << endl; 
			cout << "Account Number: " << "\t" << "Account Name: " << "\t" << "Account Value: " << endl;
			while (!in_file.eof()) {
				GetRecord(AccountRecord, in_file); //pass strcture by reference
				cout << AccountRecord.account_Number << "\t\t\t" << AccountRecord.name_Owner << "\t" << AccountRecord.amount_Avail << endl;
			}

			break;  
		case 'Q':  cout << "user selected Q" << endl; break;
		case 'H':  cout << "user selected H" << endl; break;
		default: cout << "INVALID Selection!" << endl;
		}

	}



		in_file.close();




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

//	cout << "Account Number: " << "\t" << "Account Name: " << "\t" << "Account Value: " << endl;
	//VIEW ALL FUNCTION

	//while (!inputfile.eof()) {
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
		//tmpstring >> Person1.amount_Avail;
		tmpstring >> record.amount_Avail;
		// END LINE PARSING	


		//cout << accountNumber << "\t\t\t" << accountName << "\t" << accountValue << endl;
	//} //endwhile


	return;
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
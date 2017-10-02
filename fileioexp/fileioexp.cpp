// fileioexp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
using namespace std;

char semicolin;
int age;
char name;
char userselection = 'H';
string wholeentry;
string accountNumber;
string accountFirstname;
string accountLastname;
string accountname;
string accountValue;

istringstream tmpstring,tmpstring2;

struct accountStruct
{
	int account_Number;
	string name_Owner;
	double amount_Avail;
};

int main()
{
	accountStruct Person1;

	cout << "WELCOME TO THE ACCOUNTS MANAGER" << endl<<endl;
	cout << "Please select from one of the following options:" << endl;
	cout << "Press ""I"" to insert a new account record" << endl;
	cout << "Press ""M"" to modify an existing record" << endl;
	cout << "Press ""V"" to view all account records" << endl;
	cout << "Press ""H"" to return to this menu" << endl;
	cout << "Press ""Q"" to quit" << endl;
	cout << "Entry -> ";

	cin >> userselection;

	switch (userselection)
	{
		case 'I':  cout << "user selected I" << endl; break;
		case 'M':  cout << "user selected M" << endl; break;
		case 'V':  cout << "user selected V" << endl; break;
		case 'Q':  cout << "user selected Q" << endl; break;
		case 'H':  cout << "user selected H" << endl; break;
		default: cout << "INVALID Selection!"<< endl;
	}


	
	ifstream in_file;
	in_file.open("input.dat");

	if (in_file.fail()) { cout << "ERROR: NO SUCH FILE" << endl; return 0; }	//check for failure when opening

	while (!in_file.eof()) {
		tmpstring.clear();
	//	tmpstring2.clear();

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

		in_file.close();



	return 0;
}
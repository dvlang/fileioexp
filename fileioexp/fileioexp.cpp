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
//char *tokenPtr;
string wholeentry;
string accountNumber;
string accountFirstname;
string accountLastname;
string accountname;
string accountValue;

istringstream tmpstring;

struct accountStruct
{
	int account_Number;
	string name_Owner;
	string name_OwnerFirst;
	string name_OwnerLast;
	double amount_Avail;
};

int main()
{
	accountStruct Person1;

	cout << "FILE IO TESTING" << endl;

	ifstream in_file;
	in_file.open("input.dat");

	if (in_file.fail()) { cout << "ERROR: NO SUCH FILE" << endl; return 0; }	//check for failure when opening

	/*while (getline(in_file, wholeentry))
	{

	}*/
	getline(in_file, wholeentry);

	int i = 0;
	while (!isspace(wholeentry[i])) { i++; }
	accountNumber = wholeentry.substr(0, i-1);

	cout << "i = " << i << endl;

	int j = i+1;
	i++;
	int y;
	for (y = 0; y < 2; y++) {
		while (!isspace(wholeentry[i])) { i++; }
	}
	accountname = wholeentry.substr(j, i-2);
	cout << "i = " << i << endl;
	
	j = j+i;
	
	while (!isspace(wholeentry[i])) { i++; }
	accountValue = wholeentry.substr(j, i - 2);
	
	//tmpstring.str(wholeentry);
	//tmpstring >> Person1.account_Number >> semicolin >> Person1.name_OwnerFirst >> semicolin >> Person1.name_OwnerLast >> semicolin>> Person1.amount_Avail;

	

	

	cout << "Account Number: " << accountNumber << endl;
	cout << "Account Name: " << accountname << endl;
	cout << "Account Value: " << accountValue << endl;
	//cout << "Account Number: "<< Person1.account_Number << endl;
	//cout << "Account Name: " << Person1.name_OwnerFirst << " " << Person1.name_OwnerLast << endl;
	//cout << "Account Total: " << Person1.amount_Avail << endl;
		in_file.close();

	return 0;
}
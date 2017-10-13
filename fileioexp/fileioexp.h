#pragma once
//--------------------BEGIN Function Prototype-----------------------------
//void ViewAllRecords(ifstream&);
void GetRecord(struct accountStruct &record, ifstream&);
bool FindRecord(struct accountStruct &record, ifstream&, int, int *recloc, int *recordend);
bool AddRecord(struct accountStruct &record, ofstream&);
bool CheckLength(istringstream&, int);
bool CheckEmpty(istringstream&);
bool IsNumber(const string&);
bool ModifyRecord(struct accountStruct &record, ofstream&, int *recloc, int *recordend);
bool IsNumber(const string&, int);
//--------------------END Function Prototype-------------------------------

struct accountStruct
{
	int account_Number;
	string name_Owner;
	double amount_Avail;
};

const char FILENAME[14] = "accounts.dat";	//this is the name of the account data file

const int ACCOUNTLENGTH = 6;	//this is the length required for an account number
const float INTERESTRATE = 0.01;
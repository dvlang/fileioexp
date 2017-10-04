#pragma once
//--------------------BEGIN Function Prototype-----------------------------
//void ViewAllRecords(ifstream&);
void GetRecord(struct accountStruct &record, ifstream&);
bool FindRecord(struct accountStruct &record, ifstream&, int, int *recloc);
bool AddRecord(struct accountStruct &record, ofstream&);
bool ModifyRecord(struct accountStruct &record, ofstream&, int *recloc);
//--------------------END Function Prototype-------------------------------

struct accountStruct
{
	int account_Number;
	string name_Owner;
	double amount_Avail;
};
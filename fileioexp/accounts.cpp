#include "stdafx.h"
#include <iostream>

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
#include "stdafx.h"
#include <iostream>

#include "accounts.h"



Accounts::Accounts() { account_Number = 0; name_Owner = "null"; amount_Avail = 1010; }

void Accounts::printAccount()
{
	std::cout << "Account Number: " << account_Number << " Name: " << name_Owner << " Amount Available: " << amount_Avail << std::endl;
}

void Accounts::setAccountNumber(int accnum) { account_Number = accnum; }
void Accounts::setAccountName(std::string accname) { name_Owner = accname; }
void Accounts::setAccountValue(double accval) { amount_Avail = accval; }


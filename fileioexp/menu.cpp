#include "stdafx.h"
#include <iostream>

#include <fstream>
#include <string>
#include <cstring>
#include <sstream>

#include "menu.h"
//#include "fileioexp.h"



Menu::Menu() {  }

void Menu::printHeader(std::string date)
{
	std::cout << "*********************************************** " << std::endl << std::endl;
	std::cout << "        WELCOME TO THE ACCOUNTS MANAGER" << std::endl << std::endl;
	std::cout << "************** Date: " << date << "***************** " << std::endl;
}

void Menu::printMenu()
{
	std::cout << std::endl;
	std::cout << "************************************************" << std::endl;
	std::cout << "Please select from one of the following options:" << std::endl << std::endl;
	std::cout << "Press ""I"" to insert a new account record" << std::endl;
	std::cout << "Press ""M"" to modify an existing record" << std::endl;
	std::cout << "Press ""V"" to view all account records" << std::endl;
	std::cout << "Press ""Q"" to quit" << std::endl;
	std::cout << "************************************************" << std::endl;
}


void Menu::printViewAllMenu() {
	std::cout << std::endl << "--------------------Accounts on File-----------------------" << std::endl;
	std::cout << "Account Type" << "\t\t" << "Account Number" << "\t\t" << "Account Name" << "\t" << "Account Value " << std::endl;
	std::cout << "--------------" << "\t\t" << "--------------" << "\t\t" << "------------" << "\t" << "-------------" << std::endl;
}

void Menu::printModifyBaseAccountMenu() {
	std::cout << std::endl << "SELECT ACTION" << std::endl;
	std::cout << "Press C to Change Name on account record" << std::endl;
	std::cout << "Press W to perform a withdrawl" << std::endl;
	std::cout << "Press D to make a deposit" << std::endl;
	std::cout << "Press P to factor in interest" << std::endl;
	std::cout << "Press E to Exit" << std::endl;
}


char Menu::getUserSelection()
{
	std::cout << "Entry -> ";
	getline(std::cin, tmp);
	userselection = tmp[0];
	return userselection;
}

int Menu::getDesiredAcctNum()
{
	
	accountnumgood = false;
	
	tmpstring.clear();

	//Get desired account number

	std::cout << "Desired account number (6digits): " << std::endl;
	getline(std::cin, tmp);
	tmpstring.str(tmp);

	//check to make sure the account number is valid length, if it is then make sure a ACCOUNTLENGTH number
	accountnumgood = CheckLength(tmpstring, ACCOUNTLENGTH);
	if (accountnumgood) { accountnumgood = IsNumber(tmp, ACCOUNTLENGTH); }

	while (!accountnumgood) {
		tmpstring.clear();
		std::cout << "ERROR23: Bad Length or Value, Enter NEW Desired account number (6digits): " << std::endl;
		getline(std::cin, tmp);
		tmpstring.str(tmp);

		//check to make sure the account number is valid length, if it is then make sure a ACCOUNTLENGTH number
		accountnumgood = CheckLength(tmpstring, ACCOUNTLENGTH);
		if (accountnumgood) { accountnumgood = IsNumber(tmp, ACCOUNTLENGTH); }
	}
	
	tmpstring >> tmpacctnumber;
	
	
	return tmpacctnumber;

}

std::string Menu::getUserName() {
	bool lengthgood;

	//Get user acccount name
	std::cout << "Desired Account Holder Name: " << std::endl;
	getline(std::cin, tmp);
	tmpstring.str(tmp);

	//check to see if they field was empty, if it was, stay here till they give you a good one
	lengthgood = CheckEmpty(tmpstring);

	//make sure the user didnt enter an empty value
	while (!lengthgood) {
		std::cout << "ERROR: Account Holder Name Can't Be Empty, Re-try: " << std::endl;
		getline(std::cin, tmp);
		tmpstring.str(tmp);
		lengthgood = CheckEmpty(tmpstring);
	}

	return tmp;
}

int Menu::getUserAcct() {
	return 1;
}

double Menu::getUserAmount() {
	bool lengthgood = false;
	bool valgood=false;
	double tmpacctval=0.0;
	std::string tmpval;
	
	while (!lengthgood || !valgood) {
		//check to see if they field was empty, if it was, set account value to 0
		std::cout << "Desired Value (00.00 format): " << std::endl;
		getline(std::cin, tmp);
		tmpstring.clear();
		tmpstring.str(tmp);

		//make sure the user didnt enter an empty value
		lengthgood = CheckEmpty(tmpstring);

		tmpstring >> tmpval;
		valgood = IsNumber(tmpval, 1);
		
	}

		tmpacctval = std::stod(tmpval);

		return tmpacctval;
	
	
}



//********FUNCTION: CheckLength  BEGIN******************************
//This function tests to see if the TMPSTRING is LENGTH char string
bool Menu::CheckLength(std::istringstream &tmpstring, int length) {
	int tmpaccountlength = 0;

	tmpstring.seekg(0, tmpstring.end);

	tmpaccountlength = tmpstring.tellg();
	tmpstring.seekg(0, tmpstring.beg);

	if (tmpaccountlength == length) {
		return true;
	}
	else {
		return false;
	}

}
//********FUNCTION: CheckLength  END******************************

//********FUNCTION: CheckEmpty  BEGIN******************************
//This function tests to see if the string is empty
bool Menu::CheckEmpty(std::istringstream &tmpstring) {
	int tmpaccountlength = 0;

	tmpstring.seekg(0, tmpstring.end);

	tmpaccountlength = tmpstring.tellg();
	tmpstring.seekg(0, tmpstring.beg);

	if (tmpaccountlength != 0) {
		return true;
	}
	else {
		return false;
	}

}
//********FUNCTION: CheckEmpty  END******************************



//********FUNCTION: IsNumber  BEGIN******************************
//This function tests to see if the TMPSTRING is LENGTH digit number
bool Menu::IsNumber(const std::string& tmpstring, int length) {

	int i;
	int result = 0;

	for (i = 0; i < length; i++) {

		if (isdigit(tmpstring[i])) {
			result++;

		}

	}


	if (result == length) {
		return true;
	}
	else {

		return false;
	}


}
//********FUNCTION: IsNumber  END******************************
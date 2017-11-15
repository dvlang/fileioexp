#pragma once
#ifndef MENU_H
#define MENU_H
#include <string>
#include <iostream>
#include <fstream>


const int ACCOUNTLENGTH = 6;	//this is the length required for an account number

class Menu {

public:
	Menu();
	void printHeader(std::string date);

	void printMenu();
	void printViewAllMenu();
	void printModifyBaseAccountMenu();
	char getUserSelection();
	int getDesiredAcctNum();

	std::string getUserName();
	int getUserAcct();
	double getUserAmount();
	std::string getAccountType();

private:
	char userselection;
	std::string tmp;
	bool accountnumgood;
	std::istringstream tmpstring;
	int tmpacctnumber;

	bool IsNumber(const std::string&, int);
	bool CheckLength(std::istringstream&, int);
	bool CheckEmpty(std::istringstream&);

};
#endif



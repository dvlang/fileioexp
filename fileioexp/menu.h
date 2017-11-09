#pragma once
#ifndef MENU_H
#define MENU_H
#include <string>
#include <iostream>
#include <fstream>


class Menu {

public:
	Menu();
	void printHeader(std::string date);

	void printMenu();
	void printViewAllMenu();
	void printModifyMenu();
	char getUserSelection();
	int getDesiredAcctNum();

	std::string getUserName();
	int getUserAcct();
	double getUserAmount();

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



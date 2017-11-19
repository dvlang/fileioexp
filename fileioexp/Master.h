
#ifndef MASTER_H
#define MASTER_H
#include <string>
#include <iostream>
#include <fstream>
#include <time.h>
#include "accounts.h"

class Master :public Accounts {

public:
	Master();
	~Master();


	virtual void GetRecordwc(std::ifstream&);
	virtual bool doesAccountExist(std::ifstream&, const int );

};

#endif

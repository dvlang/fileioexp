// fileioexp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#include <iostream>

using namespace std;


class DansClass {
public:
	int age;
	string name;
	void coolSaying() {
		std::cout << "cool saying 1!" << std::endl;
		aged();

	}

private:
	void aged() {
		//    cout<< "the persons age is: " << age<<endl;
	}
};

struct Time {

	int hour;
	int minute;
	int second;

};



int main()
{
	DansClass dansObject;
	DansClass dansObject2;
	Time dansObject3;

	dansObject.coolSaying();
	dansObject.age = 27;
	dansObject.name = "Dan";
	cout << "the persons age is: " << dansObject.age << endl;
//	cout << "the persons name is: " << dansObject.name << endl;

	dansObject2.coolSaying();
	dansObject2.age = 37.9;
	dansObject2.name = "klo";
	cout << "the persons age is: " << dansObject2.age << endl;
//	cout << "the persons name is: " << dansObject2.name << endl;

	dansObject3.hour = 23;
	dansObject3.minute = 14;
	dansObject3.second = 26;

	cout << "the hour name is: " << dansObject3.hour << endl;
	cout << "the minute name is: " << dansObject3.minute << endl;
	cout << "the second name is: " << dansObject3.second << endl;

	//dansObject.coolSaying2();


	return 0;
}
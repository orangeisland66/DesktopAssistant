#pragma once
#include"header.h"
#include"MenuManager.h"
using namespace std;
class Account
{
public:
	Account(int year,int month,int day,double money, bool IO);
	void print(ofstream &cout)const;
	void print()const;
	friend ostream& operator<<(ostream& cout, const Account& ac);
	friend ofstream& operator<<(ofstream& ofs, const Account& ac);
	friend bool operator<(const Account& ac1, const Account& ac2);
	bool getInorOut()const;
	double getmoney()const;
private:
	int year, month, day; 
	double money;
	bool InorOut;
};
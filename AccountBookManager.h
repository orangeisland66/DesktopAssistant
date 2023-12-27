#pragma once
#include"Account.h"

using namespace std;


class AccountBookManager
{
public:
	AccountBookManager();
	void write();
	void show();
	void searchByDate();
	void accountRegister(string& s,double& money,int& choice);
	void operator()();
	void Manager();
	void transform(string& YMD, int* Y_M_D);
	void delete_();
	void doubleJudge();
	bool isEmpty();
	//void MyPrint(const Account&);

private:
	multiset<Account,MyCompare<Account>>accountArray;
	double inSum;
	double outSum;
};
void myPrintIn(const Account& ac);
void myPrintOut(const Account& ac);

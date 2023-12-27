#pragma once
#include"header.h"
#include"MenuManager.h"
using namespace std;

class MyPasswordRecorderArrayPrint
{
public:
	void operator()(const pair<string, string>& p);
};
class PasswordRecorderManager
{
public:
	PasswordRecorderManager();
	void operator()();
	void operator()(const pair<string, string>& p);
	void init();
	void reset();
	vector<pair<int, pair<string, string>>> find();
	void delete_();
	void show();
	bool checkPassword();
	void write();
	void search();
	void comfirmToDelete(vector<pair<int, pair<string, string>>>& Password_to_Delete,int &num);
private:
	string to_Visit_Password;
	bool is_Init;
	vector<pair<string, string>>PasswordRecorderArray;
};
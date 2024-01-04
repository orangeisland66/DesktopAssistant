#pragma once
#include<iostream>
#include<string>
using namespace std;

template<typename T>
void MyPrint(const T& to_print)
{
	cout << to_print;
}

template<typename T>
class MyCompare
{
public:
	bool operator()(const T& t1, const T& t2)const
	{
		return t1 < t2;
	}
};

template<typename T>
T cinCheck(int mode,int range=0,string s=" ")
{
	if (mode == 1||mode==3)
	{
		int choice = 0;

		while (cin >> choice)
		{
			if (choice <= 0 || choice > range)
			{
				cin.clear();
				while (cin.get() != '\n')continue;
				cout << "请输入1~" << range << "之间的整数！" << endl;
				continue;
			}
			break;
		}
		if (cin.fail() && mode == 1)
		{
			cin.clear();
			while (cin.get() != '\n')continue;
			cout << "输入格式错误，正在返回上一界面！\n";
			Sleep(1000);
		}
		else if (cin.fail() && mode == 3)
		{
			cin.clear();
			while (cin.get() != '\n')continue;
			cout << "请输入1~" << range << "之间的整数！" << endl;
		}
		else
		{
			cin.clear();
			while (cin.get() != '\n')choice=0;
			if (choice == 0)cout << "请输入1~" << range << "之间的整数！" << endl;
		}
		return choice;
	}
	if (mode == 2)
	{
		double money = 0;
		cin >> money;
		if (cin.fail())
		{
			cin.clear();
			while (cin.get() != '\n')continue;
			cout << "输入格式错误，正在返回上一界面！\n";
			Sleep(1000);
		}
		return money;
	}
	if (mode == 4)
	{
		int num = 0;
		for (auto& e : s)
		{
			if (e == '/')num++;
			else if (e < '0' || e>'9')return false;
		}
		if (num == 2)
			return true;
		return false;
	}
	if (mode == 5)
	{
		int num = 0;
		for (auto& e : s)
		{
			if (e == ' ')num++;
		}
		if (num == 3)return true;
		return false;
	}
	return 0;
}

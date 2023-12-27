#pragma once
#include<iostream>
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

#pragma once
#include"header.h"
using namespace std;
class Deadline
{
public:
	Deadline(string subjectname, int dayRemained);
	friend bool operator<(const Deadline& ddl1, const Deadline& ddl12);
	void deadlineOutput(int cnt)const;

private:
	
	string subjectName;
	int dayRemained;
};


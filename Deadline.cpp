#include "Deadline.h"

Deadline::Deadline(string subjectName, int dayRemained):subjectName(subjectName),dayRemained(dayRemained){}


void Deadline::deadlineOutput(int cnt)const
{
	stringstream ss;
	string days;
	ss << dayRemained;
	ss >> days;
	string dayOutput = "             »¹Ê£" + days + "Ìì";
	outtextxy(360, 350 + 35 * cnt, subjectName.c_str());
	outtextxy(470, 350 + 35 * cnt, dayOutput.c_str());
}

bool operator<(const Deadline& ddl1, const Deadline& ddl2)
{
	return ddl1.dayRemained < ddl2.dayRemained;
}

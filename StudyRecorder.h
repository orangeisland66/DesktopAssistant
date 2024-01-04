#pragma once
#include"header.h"
#include"MenuManager.h"

class StudyRecorder
{
public:
	StudyRecorder(int year, int month, int day, string place, string content);
	friend ostream& operator<<(ostream&, const StudyRecorder& rc);
	friend ofstream& operator<<(ofstream& ofs, const StudyRecorder& rc);
private:
	int year, month, day;
	string place, content;
};
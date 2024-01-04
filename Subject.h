#pragma once
#include"header.h"
#include"PushButton.h"

class Subject
{
public:
	Subject(string subjectName, string teacher, string string_weekday, string sections,bool have_dll=false,int year=0,int month=0,int day=0,bool have_reminder=false);
	friend bool  operator<(const Subject& ac1, const Subject& ac2);
	int setButtonHeight();
	int setButtonWidth();
	int setButton_x();
	int setButton_y();
	bool set_have_reminder(bool);
	void setHourAndMinute();
	void setweekday();
	bool set_ddl(int year,int month,int day);
	bool delete_ddl();
	friend ofstream& operator<<(ofstream&, const Subject&);
	void outtextInfo();
	void outtext_ddl(int height);
	bool is_ddl();
	bool is_reminder();
	int getStartHour();
	int getStartMinute();
	int getWeekday();
	int getYear();
	int getMonth();
	int getDay();
	string getSubjectName();
	PushButton getButn()const;
private:
	string subjectName;
	string teacher;
	string string_weekday;
	string time;
	string sections;
	int startHour, startMinute, endHour, endMinute;
	string startHourAndMinute, endHourAndMinute;
	int int_weekday;
	int startSection, endSection;
	int year, month, day;
	bool have_ddl, have_reminder;
	PushButton butn;
};


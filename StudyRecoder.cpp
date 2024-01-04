#include"StudyRecorder.h"

StudyRecorder::StudyRecorder(int year,int month,int day,string place,string content):
	year(year),month(month),day(day),place(place),content(content){}

ostream& operator<<(ostream& cout, const StudyRecorder& rc)
{
	cout << "学习时间：" << rc.year << "年" << rc.month << "月" << rc.day << "日" << endl;
	cout << "学习地点：" << rc.place << endl;
	cout << "学习内容：" << rc.content << endl << endl;
	return cout;
}

ofstream& operator<<(ofstream& ofs, const StudyRecorder& rc)
{
	ofs<< rc.year <<" "<< rc.month <<" "<< rc.day <<" "<< rc.place <<" "<< rc.content << endl;
	return ofs;
}
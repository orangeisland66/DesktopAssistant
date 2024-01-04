#include"StudyRecorder.h"

StudyRecorder::StudyRecorder(int year,int month,int day,string place,string content):
	year(year),month(month),day(day),place(place),content(content){}

ostream& operator<<(ostream& cout, const StudyRecorder& rc)
{
	cout << "ѧϰʱ�䣺" << rc.year << "��" << rc.month << "��" << rc.day << "��" << endl;
	cout << "ѧϰ�ص㣺" << rc.place << endl;
	cout << "ѧϰ���ݣ�" << rc.content << endl << endl;
	return cout;
}

ofstream& operator<<(ofstream& ofs, const StudyRecorder& rc)
{
	ofs<< rc.year <<" "<< rc.month <<" "<< rc.day <<" "<< rc.place <<" "<< rc.content << endl;
	return ofs;
}
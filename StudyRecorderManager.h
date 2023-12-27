#pragma once
#include"StudyRecorder.h"
class StudyRecorderManager
{
public:
	StudyRecorderManager();
	void write();
	void delete_();
	void show();
	void operator()();
	
private:
	vector<StudyRecorder>StudyRecorderArray;
};
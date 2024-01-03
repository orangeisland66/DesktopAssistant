#pragma once
#include"header.h"
#include"DailyRecorder.h"


class DailyRecorderManager
{
public:
	DailyRecorderManager();
	void operator()();
	void fileInit();
	void setPos(vector<PushButton>& v);
	int delete_(int i);
	int showRecorder(int i);
	void show_btns(vector<PushButton>& v);
	void drawBackground();
	int menueventLoop(vector<PushButton>& v);
	int pictureChoosePage(); 
	int recordersSelectAndRecordersDeletePage(int mode); 
	int explanationPage();
	bool isEsc();
	void showEsc();
	int editPage(int i);
	void draw(char title[],char content[]);
	int edit(int mode, char* title, char* content,int i);
	void edit_btnsSetPos();
	~DailyRecorderManager();


private:
	vector<PushButton>menu_btns;
	pair<vector<DailyRecorder>, vector<PushButton>>recorderArray;
	pair<vector<pair<string, IMAGE*>>, vector<PushButton>>imageArray;
	vector<PushButton>edit_btns;
	IMAGE* background;
	ExMessage msg;
	bool isWrite[2] = { false };
};

